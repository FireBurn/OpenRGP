#pragma once
#include <QMainWindow>
#include <memory>
#include <thread>
#include <atomic>
#include <vector>
#include "openrgp/analysis.h"
class QLabel;
class QTabWidget;
class QTableWidget;
class QTableView;
class WaveModel;
class QTextEdit;
class QPushButton;
class QComboBox;
class QSpinBox;
class OccupancyView;
class TimelineView;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent=nullptr);
    ~MainWindow() override;
    void waitForDecode();   // blocks until the background thread-trace decode has been applied
    void openFile(const QString& path);
    int tabCount() const;
    void setTab(int i);
private slots:
    void onOpen();
    void onExport(const QString& what);
    void refreshAnalysis();
private:
    void showSummary(const openrgp::Profile& p);
    void showSpm(const openrgp::Profile& p);
    void showTokens(const openrgp::Profile& p);
    void showDispatches();
    void showEvents();
    void decodeFinished(std::unique_ptr<openrgp::CaptureDecode> cap, std::vector<openrgp::DispatchRow> rows, QString error);
    QTabWidget* m_tabs = nullptr;
    QLabel* m_summary = nullptr;
    QTableWidget* m_spm = nullptr;
    QTableWidget* m_dispatches = nullptr;
    QTableView* m_waves = nullptr;
    WaveModel* m_waveModel = nullptr;
    QTableWidget* m_events = nullptr;
    OccupancyView* m_occupancy = nullptr;
    TimelineView* m_timeline = nullptr;
    QComboBox* m_seBox = nullptr;
    QSpinBox* m_binBox = nullptr;
    QLabel* m_gapLabel = nullptr;
    QTextEdit* m_tokens = nullptr;
    QPushButton* m_open = nullptr;
    QString m_path;
    std::thread m_worker;
    std::atomic<int> m_generation{0};
    bool m_decoding = false;
    std::unique_ptr<openrgp::CaptureDecode> m_cap;
    std::vector<openrgp::DispatchRow> m_rows;
};
