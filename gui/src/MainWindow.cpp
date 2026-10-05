#include "MainWindow.h"
#include "openrgp/rgp_file.h"
#include "openrgp/sqtt_trace.h"
#include <QTabWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QStatusBar>
#include <QComboBox>
#include <QSpinBox>
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QSaveFile>
#include <QCheckBox>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

using namespace openrgp;

static uint32_t majorOf(SqttVersion v){ return (v>=SqttVersion::V3_2)?3:2; }

// Resident waves over time for one shader engine, with idle gaps highlighted.
class OccupancyView : public QWidget {
public:
    explicit OccupancyView(QWidget* p = nullptr) : QWidget(p) { setMinimumHeight(240); }
    void set(std::vector<openrgp::OccupancyBin> b, std::vector<openrgp::Gap> g, double cap) { m_bins = std::move(b); m_gaps = std::move(g); m_cap = cap; update(); }
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this); p.fillRect(rect(), palette().base());
        if (m_bins.empty()) { p.drawText(rect(), Qt::AlignCenter, "No wave activity"); return; }
        const int l = 54, r = 10, t = 10, b = 24;
        QRect plot(l, t, width() - l - r, height() - t - b);
        int64_t t0 = m_bins.front().begin, t1 = m_bins.back().end;
        double top = std::max(m_cap, 1.0);
        for (auto& g : m_gaps) {
            int x0 = plot.left() + (int)((double)(g.begin - t0) / (t1 - t0) * plot.width()), x1 = plot.left() + (int)((double)(g.end - t0) / (t1 - t0) * plot.width());
            p.fillRect(QRect(x0, plot.top(), std::max(1, x1 - x0), plot.height()), QColor(220, 80, 80, 70));
        }
        p.setPen(QPen(palette().mid().color(), 1));
        for (int i = 0; i <= 4; i++) {
            int y = plot.bottom() - plot.height() * i / 4;
            p.drawLine(plot.left(), y, plot.right(), y);
            p.drawText(QRect(0, y - 8, l - 4, 16), Qt::AlignRight | Qt::AlignVCenter, QString::number(top * i / 4, 'f', 0));
        }
        QPolygonF poly; poly << QPointF(plot.left(), plot.bottom());
        for (auto& bin : m_bins) {
            double x = plot.left() + (double)(bin.begin + (bin.end - bin.begin) / 2 - t0) / (t1 - t0) * plot.width();
            poly << QPointF(x, plot.bottom() - bin.avg_waves / top * plot.height());
        }
        poly << QPointF(plot.right(), plot.bottom());
        p.setPen(QPen(QColor(40, 120, 200), 1.5)); p.setBrush(QColor(40, 120, 200, 90)); p.drawPolygon(poly);
        p.setPen(palette().text().color());
        p.drawText(QRect(plot.left(), plot.bottom() + 4, plot.width(), 18), Qt::AlignLeft, QString("%1 cycles").arg((long long)t0));
        p.drawText(QRect(plot.left(), plot.bottom() + 4, plot.width(), 18), Qt::AlignRight, QString("%1 cycles   (red = engine idle)").arg((long long)t1));
    }
private:
    std::vector<openrgp::OccupancyBin> m_bins; std::vector<openrgp::Gap> m_gaps; double m_cap = 0;
};

// Wave lifetimes laid out one lane per (CU, SIMD, slot-group), coloured by dispatch. Wheel zooms, drag pans.
class TimelineView : public QWidget {
public:
    explicit TimelineView(QWidget* p = nullptr) : QWidget(p) { setMinimumHeight(260); setMouseTracking(true); }
    void set(const openrgp::SqttDecode* d) {
        m_d = d; m_lanes.clear();
        if (d) {
            std::map<int, int> lane;
            for (auto& w : d->waves) { int key = (w.cu << 8) | (w.simd << 5) | w.slot; if (!lane.count(key)) lane[key] = (int)lane.size(); }
            int n = 0; for (auto& kv : lane) kv.second = n++;
            for (auto& w : d->waves) m_lanes.push_back(lane[(w.cu << 8) | (w.simd << 5) | w.slot]);
            m_nlanes = n;
            m_t0 = d->first_time; m_t1 = std::max(d->last_time, d->first_time + 1);
            m_view0 = m_t0; m_view1 = m_t1;
        }
        update();
    }
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this); p.fillRect(rect(), palette().base());
        if (!m_d || m_d->waves.empty()) { p.drawText(rect(), Qt::AlignCenter, "No waves"); return; }
        const int l = 4, t = 4, b = 22;
        QRect plot(l, t, width() - 8, height() - t - b);
        double span = (double)(m_view1 - m_view0);
        double lane_h = std::max(1.0, (double)plot.height() / std::max(m_nlanes, 1));
        for (size_t i = 0; i < m_d->waves.size(); i++) {
            auto& w = m_d->waves[i];
            if (w.end < m_view0 || w.begin > m_view1) continue;
            double x0 = plot.left() + (w.begin - m_view0) / span * plot.width(), x1 = plot.left() + (w.end - m_view0) / span * plot.width();
            QColor c = QColor::fromHsv((w.dispatch * 47) % 360 + (w.dispatch < 0 ? 0 : 0), w.dispatch < 0 ? 0 : 170, 210);
            if (w.traced) c = c.darker(130);
            p.fillRect(QRectF(x0, plot.top() + m_lanes[i] * lane_h, std::max(1.0, x1 - x0), std::max(1.0, lane_h - (lane_h > 3 ? 1 : 0))), c);
        }
        p.setPen(palette().text().color());
        p.drawText(QRect(plot.left(), plot.bottom() + 4, plot.width(), 18), Qt::AlignLeft, QString("%1").arg((long long)m_view0));
        p.drawText(QRect(plot.left(), plot.bottom() + 4, plot.width(), 18), Qt::AlignHCenter, "wheel: zoom   drag: pan   double-click: reset   (colour = dispatch, dark = instruction-traced)");
        p.drawText(QRect(plot.left(), plot.bottom() + 4, plot.width(), 18), Qt::AlignRight, QString("%1").arg((long long)m_view1));
    }
    void wheelEvent(QWheelEvent* e) override {
        if (!m_d) return;
        double fx = std::clamp(e->position().x() / std::max(1, width()), 0.0, 1.0), span = (double)(m_view1 - m_view0);
        double f = e->angleDelta().y() > 0 ? 0.7 : 1.0 / 0.7, ns = std::clamp(span * f, 50.0, (double)(m_t1 - m_t0));
        double c = m_view0 + fx * span; m_view0 = (int64_t)(c - fx * ns); m_view1 = (int64_t)(m_view0 + ns);
        clampView(); update();
    }
    void mousePressEvent(QMouseEvent* e) override { m_drag = e->position().x(); }
    void mouseMoveEvent(QMouseEvent* e) override {
        if (!(e->buttons() & Qt::LeftButton) || !m_d) return;
        double dx = e->position().x() - m_drag; m_drag = e->position().x();
        int64_t sh = (int64_t)(-dx / std::max(1, width()) * (double)(m_view1 - m_view0)); m_view0 += sh; m_view1 += sh; clampView(); update();
    }
    void mouseDoubleClickEvent(QMouseEvent*) override { m_view0 = m_t0; m_view1 = m_t1; update(); }
private:
    void clampView() {
        int64_t span = m_view1 - m_view0;
        if (m_view0 < m_t0) { m_view0 = m_t0; m_view1 = m_t0 + span; }
        if (m_view1 > m_t1) { m_view1 = m_t1; m_view0 = m_t1 - span; }
    }
    const openrgp::SqttDecode* m_d = nullptr; std::vector<int> m_lanes; int m_nlanes = 0;
    int64_t m_t0 = 0, m_t1 = 1, m_view0 = 0, m_view1 = 1; double m_drag = 0;
};


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent){
    setWindowTitle("OpenRGP - open-source Radeon GPU Profiler");
    resize(1000, 700);

    auto* central = new QWidget(this);
    auto* lay = new QVBoxLayout(central);

    auto* bar = new QVBoxLayout();
    m_open = new QPushButton("Open .rgp profile…", this);
    bar->addWidget(m_open);
    lay->addLayout(bar);

    m_tabs = new QTabWidget(this);
    m_summary = new QLabel("No profile loaded.\n\nClick “Open .rgp profile…” to load a capture\nproduced by Mesa radv (MESA_VK_TRACE=rgp).", this);
    m_summary->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    m_summary->setTextFormat(Qt::PlainText);
    m_summary->setStyleSheet("font-family: monospace; padding: 8px;");

    m_spm = new QTableWidget(this);
    m_spm->setColumnCount(5);
    m_spm->setHorizontalHeaderLabels({"Group","Counter","Samples","Average","Min / Max"});
    m_spm->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    m_tokens = new QTextEdit(this);
    m_tokens->setReadOnly(true);

    m_dispatches = new QTableWidget(this);
    m_dispatches->setColumnCount(7);
    m_dispatches->setHorizontalHeaderLabels({"#", "Start", "Cycles", "Waves", "Traced", "Kernel", "Signature"});
    m_dispatches->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    m_dispatches->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_dispatches->setSortingEnabled(true);

    m_waves = new QTableWidget(this);
    m_waves->setColumnCount(11);
    m_waves->setHorizontalHeaderLabels({"SE", "CU", "SIMD", "Slot", "Begin", "End", "Cycles", "Dispatch", "Traced", "Insts", "Exec / Wait / Stall"});
    m_waves->horizontalHeader()->setSectionResizeMode(10, QHeaderView::Stretch);
    m_waves->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_waves->setSortingEnabled(true);

    auto* analysis = new QWidget(this);
    auto* av = new QVBoxLayout(analysis);
    auto* ctl = new QHBoxLayout();
    m_seBox = new QComboBox(this);
    m_binBox = new QSpinBox(this); m_binBox->setRange(100, 100000000); m_binBox->setValue(2000); m_binBox->setSuffix(" cycles/bin");
    ctl->addWidget(new QLabel("Shader engine:", this)); ctl->addWidget(m_seBox); ctl->addWidget(new QLabel("Bin:", this)); ctl->addWidget(m_binBox); ctl->addStretch(1);
    m_gapLabel = new QLabel(this);
    m_occupancy = new OccupancyView(this);
    m_timeline = new TimelineView(this);
    av->addLayout(ctl); av->addWidget(m_gapLabel); av->addWidget(m_occupancy, 1);
    auto* tl = new QWidget(this); auto* tv = new QVBoxLayout(tl); tv->addWidget(m_timeline, 1);
    connect(m_seBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::refreshAnalysis);
    connect(m_binBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::refreshAnalysis);

    m_tabs->addTab(m_summary, "Summary");
    m_tabs->addTab(m_dispatches, "Dispatches");
    m_tabs->addTab(analysis, "Occupancy");
    m_tabs->addTab(tl, "Timeline");
    m_tabs->addTab(m_waves, "Waves");
    m_tabs->addTab(m_spm, "SPM Counters");
    m_tabs->addTab(m_tokens, "Tokens");
    lay->addWidget(m_tabs);
    setCentralWidget(central);

    auto* fileMenu = menuBar()->addMenu("&File");
    auto* openAct = fileMenu->addAction("&Open…");
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::onOpen);
    auto* exportMenu = fileMenu->addMenu("&Export");
    for (auto [label, key] : std::vector<std::pair<QString, QString>>{{"Waves (CSV)…", "waves"}, {"Instructions of traced waves (CSV)…", "insts"}, {"Dispatches (CSV)…", "dispatches"},
                                                                       {"Occupancy (CSV)…", "occupancy"}, {"SPM counters (CSV)…", "spm"}, {"Everything (JSON)…", "json"}})
        connect(exportMenu->addAction(label), &QAction::triggered, this, [this, key] { onExport(key); });
    connect(m_open, &QPushButton::clicked, this, &MainWindow::onOpen);

    statusBar()->showMessage("OpenRGP 0.1.0");
}

void MainWindow::onOpen(){
    QString f = QFileDialog::getOpenFileName(this, "Open RGP profile", QString(), "Profiles (*.rgp *.rdc);;All files (*)");
    if(!f.isEmpty()) openFile(f);
}

void MainWindow::openFile(const QString& path){
    Profile p; std::string err;
    if(!RgpFile::load(path.toStdString(), p, &err)){
        QMessageBox::critical(this, "Open failed", QString::fromStdString(err));
        return;
    }
    showSummary(p);
    showSpm(p);
    showTokens(p);
    m_path = path;
    QApplication::setOverrideCursor(Qt::WaitCursor);
    statusBar()->showMessage("Decoding thread trace…"); QApplication::processEvents();
    m_cap = std::make_unique<CaptureDecode>(); m_rows.clear();
    std::string derr;
    if (decode_capture(path.toStdString(), *m_cap, &derr)) {
        std::string aerr;
        analyze_dispatches(path.toStdString(), guess_mcpu(m_cap->p), m_cap->se_index.front(), m_rows, &aerr);
    } else { m_cap.reset(); statusBar()->showMessage(QString::fromStdString("No decodable thread trace: " + derr), 8000); }
    m_seBox->blockSignals(true); m_seBox->clear();
    if (m_cap) for (int i : m_cap->se_index) m_seBox->addItem(QString("SE %1").arg(i));
    m_seBox->blockSignals(false);
    showDispatches(); showWaves(); refreshAnalysis();
    QApplication::restoreOverrideCursor();
    setWindowTitle("OpenRGP - " + path);
    statusBar()->showMessage("Loaded " + path, 5000);
}

void MainWindow::showSummary(const Profile& p){
    auto s = summarize(p);
    std::ostringstream o;
    o << "File:        " << p.path << "\n";
    if(p.container == "AMD_RDF") o << "Format:      AMD_RDF (" << p.rdf_chunks.size() << " chunks)\n";
    else o << "Format:      B00P v" << p.header.version_major << "." << p.header.version_minor << "\n";
    o << "Captured:    " << s.capture_time << "\n\n";
    o << "GPU:         " << s.gpu_name << "\n";
    o << "  topology:  " << s.shader_engines << " SE x " << s.cu_per_se << " CU x "
      << s.simd_per_cu << " SIMD, " << s.waves_per_simd << " wf/SIMD\n";
    o << "  registers: " << s.vgprs_per_simd << " VGPR/SIMD, " << s.sgprs_per_simd << " SGPR/SIMD\n";
    o << "  clocks:    SCLK " << s.sclk_hz/1000000 << " MHz, MCLK " << s.mclk_hz/1000000 << " MHz\n";
    if(p.asic){
        o << "  device:    id=0x" << std::hex << p.asic->device_id << " rev=0x"
          << p.asic->device_revision_id << std::dec << "  vram="
          << (p.asic->vram_size/1024/1024) << " MB\n";
        o << "  caches:    L1=" << p.asic->l1_cache_size << "  L2=" << p.asic->l2_cache_size
          << "  LDS=" << p.asic->lds_size << "\n";
    }
    o << "\nCPU:         " << s.cpu_name << " (" << s.vendor << ")\n";
    if(p.cpu) o << "  cores:     " << p.cpu->num_logical_cores << " logical / "
                << p.cpu->num_physical_cores << " physical, " << p.cpu->clock_speed << " MHz, "
                << p.cpu->system_ram_size << " MB RAM\n";
    o << "\nAPI:         " << s.api << "\n";
    o << "Traces:      " << s.num_se_traces << " SE, " << s.total_sqtt_bytes << " bytes SQTT\n";
    o << "Code objs:   " << s.num_code_objects << "   loader events: " << s.num_loader_events
      << "   PSO: " << s.num_pso << "   queue events: " << s.num_queue_events << "\n";
    o << "Derived SPM: " << (s.has_derived_spm?"yes":"no")
      << (s.has_derived_spm?" ("+std::to_string(s.spm_counter_count)+" counters)":"") << "\n";
    m_summary->setText(QString::fromStdString(o.str()));
}

void MainWindow::showSpm(const Profile& p){
    m_spm->setRowCount(0);
    if(!p.derived_spm) return;
    auto& s = *p.derived_spm;
    // map counter id -> group name
    std::map<uint32_t,std::string> cid2group;
    for(auto& g : s.groups) for(uint32_t cid : g.counter_ids) cid2group[cid]=g.name;
    int r = 0;
    for(size_t cid=0; cid<s.counters.size(); cid++){
        auto& c = s.counters[cid];
        double sum=0,mn=1e30,mx=-1e30; size_t n=c.values.size();
        for(double v:c.values){ sum+=v; if(v<mn)mn=v; if(v>mx)mx=v; }
        double avg = n? sum/n : 0;
        auto add=[&](const QString& a,const QString& b,const QString& cc,const QString& d,const QString& e){
            m_spm->insertRow(r);
            m_spm->setItem(r,0,new QTableWidgetItem(a));
            m_spm->setItem(r,1,new QTableWidgetItem(b));
            m_spm->setItem(r,2,new QTableWidgetItem(cc));
            m_spm->setItem(r,3,new QTableWidgetItem(d));
            m_spm->setItem(r,4,new QTableWidgetItem(e));
            r++;
        };
        add(QString::fromStdString(cid2group.count((uint32_t)cid)?cid2group[(uint32_t)cid]:""),
            QString::fromStdString(c.name),
            QString::number(n),
            QString::number(avg,'f',3),
            QString::number(mn,'f',1)+" / "+QString::number(mx,'f',1));
    }
    m_spm->resizeColumnsToContents();
}

void MainWindow::showTokens(const Profile& p){
    std::ostringstream o;
    std::map<uint32_t,int> total; long long markers=0, toks=0;
    for(size_t i=0;i<p.sqtt_data_ptr.size();i++){
        if(!p.sqtt_data_ptr[i]) continue;
        auto& d=p.sqtt_descs[i];
        auto tk = tokenize(p.sqtt_data_ptr[i], p.sqtt_data[i].size, i, majorOf(d.sqtt_version),0,(uint32_t)d.sqtt_version);
        for(auto&t:tk){ total[t.type]++; if(t.is_marker())markers++; }
        toks += tk.size();
        o << "SE" << i << ": " << tk.size() << " tokens\n";
    }
    o << "\ntotal: " << toks << " tokens, " << markers << " markers\nby type:\n";
    for(auto&kv:total) o << "  type " << kv.first << ": " << kv.second << "\n";
    o << "\n(note: full event/wavefront/marker decoding is in progress - see TODO.md)";
    m_tokens->setPlainText(QString::fromStdString(o.str()));
}

int MainWindow::tabCount() const { return m_tabs->count(); }
void MainWindow::setTab(int i){ m_tabs->setCurrentIndex(i); }

void MainWindow::showDispatches(){
    m_dispatches->setSortingEnabled(false); m_dispatches->setRowCount(0);
    int r = 0;
    for (auto& d : m_rows) {
        m_dispatches->insertRow(r);
        auto num = [](double v) { auto* it = new QTableWidgetItem; it->setData(Qt::DisplayRole, v); return it; };
        m_dispatches->setItem(r, 0, num(d.index)); m_dispatches->setItem(r, 1, num((double)d.begin)); m_dispatches->setItem(r, 2, num((double)(d.end - d.begin)));
        m_dispatches->setItem(r, 3, num((double)d.waves)); m_dispatches->setItem(r, 4, num((double)d.traced));
        m_dispatches->setItem(r, 5, new QTableWidgetItem(QString::fromStdString(d.label.empty() ? "(no traced wave)" : d.label)));
        m_dispatches->setItem(r, 6, new QTableWidgetItem(QString::fromStdString(d.sig)));
        r++;
    }
    m_dispatches->resizeColumnsToContents(); m_dispatches->setSortingEnabled(true);
}

void MainWindow::showWaves(){
    m_waves->setSortingEnabled(false); m_waves->setRowCount(0);
    if (!m_cap) { m_waves->setSortingEnabled(true); return; }
    constexpr size_t kMax = 50000;   // the full list is available through File > Export
    int r = 0;
    for (size_t k = 0; k < m_cap->se.size() && (size_t)r < kMax; k++)
        for (auto& w : m_cap->se[k].waves) {
            if ((size_t)r >= kMax) break;
            m_waves->insertRow(r);
            auto num = [](double v) { auto* it = new QTableWidgetItem; it->setData(Qt::DisplayRole, v); return it; };
            m_waves->setItem(r, 0, num(m_cap->se_index[k])); m_waves->setItem(r, 1, num(w.cu)); m_waves->setItem(r, 2, num(w.simd)); m_waves->setItem(r, 3, num(w.slot));
            m_waves->setItem(r, 4, num((double)w.begin)); m_waves->setItem(r, 5, num((double)w.end)); m_waves->setItem(r, 6, num((double)(w.end - w.begin)));
            m_waves->setItem(r, 7, num(w.dispatch)); m_waves->setItem(r, 8, new QTableWidgetItem(w.traced ? "yes" : ""));
            m_waves->setItem(r, 9, num((double)w.insts.size()));
            m_waves->setItem(r, 10, new QTableWidgetItem(w.traced ? QString("%1 / %2 / %3").arg(w.exec).arg(w.wait).arg(w.stall) : QString()));
            r++;
        }
    m_waves->resizeColumnsToContents(); m_waves->setSortingEnabled(true);
}

void MainWindow::refreshAnalysis(){
    int i = m_seBox->currentIndex();
    if (!m_cap || i < 0 || i >= (int)m_cap->se.size()) { m_occupancy->set({}, {}, 0); m_timeline->set(nullptr); m_gapLabel->clear(); return; }
    auto& d = m_cap->se[i];
    auto s = summarize(m_cap->p);
    double cap = (double)s.cu_per_se * s.simd_per_cu * s.waves_per_simd;
    auto gaps = idle_gaps(d, 1000);
    int64_t idle = 0; for (auto& g : gaps) idle += g.end - g.begin;
    int64_t span = std::max<int64_t>(1, d.last_time - d.first_time);
    m_gapLabel->setText(QString("%1 idle gaps of at least 1000 cycles, %2 cycles idle (%3 %)  -  hardware limit %4 resident waves per shader engine")
                        .arg(gaps.size()).arg((long long)idle).arg(100.0 * idle / span, 0, 'f', 1).arg(cap, 0, 'f', 0));
    m_occupancy->set(occupancy(d, m_binBox->value()), gaps, cap);
    m_timeline->set(&d);
}

void MainWindow::onExport(const QString& what){
    if (what != "spm" && !m_cap) { QMessageBox::information(this, "Export", "No decodable thread trace is loaded."); return; }
    QString f = QFileDialog::getSaveFileName(this, "Export " + what, QString(), what == "json" ? "JSON (*.json)" : "CSV (*.csv)");
    if (f.isEmpty()) return;
    std::ofstream os(f.toStdString());
    if (!os) { QMessageBox::critical(this, "Export failed", "Cannot write " + f); return; }
    int se = std::max(0, m_seBox->currentIndex());
    if (what == "waves") export_waves_csv(*m_cap, os);
    else if (what == "insts") export_insts_csv(*m_cap, os);
    else if (what == "dispatches") export_dispatches_csv(m_rows, os);
    else if (what == "occupancy") export_occupancy_csv(m_cap->se[se], m_binBox->value(), os);
    else if (what == "spm") { Profile p; std::string err; if (!RgpFile::load(m_path.toStdString(), p, &err) || !p.derived_spm) { QMessageBox::information(this, "Export", "This capture has no SPM counters."); return; } export_spm_csv(p, os); }
    else export_json(*m_cap, m_rows, os);
    statusBar()->showMessage("Exported " + f, 5000);
}
#include "MainWindow.moc"
