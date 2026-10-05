#pragma once
#include <QMainWindow>
#include <memory>
#include <vector>
#include "openrgp/analysis.h"
class QLabel;
class QTabWidget;
class QTableWidget;
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
    void showWaves();
    QTabWidget* m_tabs = nullptr;
    QLabel* m_summary = nullptr;
    QTableWidget* m_spm = nullptr;
    QTableWidget* m_dispatches = nullptr;
    QTableWidget* m_waves = nullptr;
    OccupancyView* m_occupancy = nullptr;
    TimelineView* m_timeline = nullptr;
    QComboBox* m_seBox = nullptr;
    QSpinBox* m_binBox = nullptr;
    QLabel* m_gapLabel = nullptr;
    QTextEdit* m_tokens = nullptr;
    QPushButton* m_open = nullptr;
    QString m_path;
    std::unique_ptr<openrgp::CaptureDecode> m_cap;
    std::vector<openrgp::DispatchRow> m_rows;
};
