#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSpinBox>
#include <QGraphicsItem>
#include <QMessageBox>

#include "msettings.h"
#include "mgraphicsscene.h"
#include "mresize.h"

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QString fileName = "");
    ~MainWindow();

public slots:

    void slotZoomIn();
    void slotZoomOut();

    void slotShowOptions();

    void slotOpenFile();
    void slotSaveAsFile();
    void slotRotateLeft();
    void slotRotateRight();
    void slotEditCurFile(QString name);
    void createStatusBar();
    void slotShowResize();

private:
    MGraphicsScene *m_scene;
    QActionGroup *m_actionGroup;
    QSpinBox *m_spinBoxRotate;
    MSettings *m_settingsForm;
    settings_app m_settingsData;
    QLabel *labelStatusBar;

    void createToolBarEdit();

};

#endif // MAINWINDOW_H
