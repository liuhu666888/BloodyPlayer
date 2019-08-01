#pragma once

// Qt
#include <QMainWindow>

// STL
#include <string>
#include <vector>


class Controller;
class TrackWidget;
class WaitWindow;
class QHideEvent;
class QSystemTrayIcon;
class TrackProgressWindow;
class QMouseEvent;
class QCPItemText;

namespace Ui
{
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:

    void signalShowMessageBox(bool errorBox, std::string text);
    void signalSetTrack(size_t iTrackIndex, bool bClear = false);
    void signalSetNumber(size_t iNumber);
    void signalAddNewTrack(std::wstring trackName, std::wstring trackInfo, std::string trackTime);

    // WaitWindow
    void signalShowWaitWindow();
    void signalHideWaitWindow();
    void signalSetProgress(int value);

    // Graph
    void signalClearGraph();
    void signalSetXMaxToGraph(unsigned int iMaxX);
    void signalAddDataToGraph(char* pData, unsigned int iSizeInBytes);
    void signalSetCurrentPos(int x, std::string time);

public:

    explicit MainWindow(QWidget *parent = nullptr);



    void showMessageBox(bool errorBox, std::string text);

    void addNewTrack(std::wstring trackName, std::wstring trackInfo, std::string trackTime);
    void removePlayingOnTrack(size_t iTrackIndex);
    void setPlayingOnTrack(size_t iTrackIndex, bool bClear = false);
    void uncheckRandomTrackButton();
    void uncheckRepeatTrackButton();

    // Graph
    void clearGraph();
    void setXMaxToGraph(unsigned int iMaxX);
    void addDataToGraph(char* pData, unsigned int iSizeInBytes);
    void setCurrentPos(int x, std::string time);

    // Focus
    void setFocusOnTrack(size_t index);

    // WaitWindow
    void showWaitWindow();
    void hideWaitWindow();
    void setProgress(int value);

    void markAnError();
    bool isSystemReady();



    ~MainWindow();

public slots:

    // Context menu on TrackWidget
    // This is also called from keyPressEvent().
    void slotMoveUp();
    void slotMoveDown();
    void deleteSelectedTrack();

    void slotTrackSelected(size_t iTrackIndex);
    void slotClickedOnTrack(size_t trackIndex);
    void slotDrop(QStringList paths);

    // Tray icon
    void slotShowWindow();

protected:

    void keyPressEvent(QKeyEvent* ev);
    void hideEvent(QHideEvent* ev);

private slots:

    void slotShowMessageBox(bool errorBox, std::string text);
    void slotSetNumber(size_t iNumber);
    void slotAddNewTrack(std::wstring trackName, std::wstring trackInfo, std::string trackTime);
    void slotSetTrack(size_t iTrackIndex, bool bClear = false);

    // WaitWindow
    void slotShowWaitWindow();
    void slotHideWaitWindow();
    void slotSetProgress(int value);

    // Graph
    void slotClearGraph();
    void slotSetXMaxToGraph(unsigned int iMaxX);
    void slotAddDataToGraph(char* pData, unsigned int iSizeInBytes);
    void slotSetCurrentPos(int x, std::string time);
    void slotClickOnGraph(QMouseEvent* ev);

    // Buttons
    void on_pushButton_Play_clicked();
    void on_pushButton_pause_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_next_clicked();
    void on_pushButton_prev_clicked();

    // Buttons under the volume slider
    void on_pushButton_repeat_clicked();
    void on_pushButton_clearPlaylist_clicked();

    // Volume slider
    void on_horizontalSlider_valueChanged(int value);

    // Menu
    void on_actionOpen_triggered();
    void on_actionOpen_Directory_triggered();
    void on_actionAbout_triggered();

    void on_pushButton_Random_clicked();

private:

    Ui::MainWindow*  ui;
    Controller*      pController;
    WaitWindow*      pWaitWindow;
    QSystemTrayIcon* pTrayIcon;
    QCPItemText*     pGraphTextTrackTime;

    std::vector<TrackWidget*> tracks;

    int iSelectedTrackIndex;

    unsigned int iCurrentXPosOnGraph;
    double minPosOnGraphForText;
    double maxPosOnGraphForText;

    bool bSystemReady;
};
