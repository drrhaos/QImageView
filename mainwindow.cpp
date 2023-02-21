#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent, QString fileName) :
    QMainWindow(parent)
{
    setupUi(this);


    m_settingsForm = new MSettings;
    m_settingsData = m_settingsForm->loadSettings();

    m_scene = new MGraphicsScene();
    m_scene->setBackgroundBrush(QBrush(m_settingsData.colorBackgroundView));
    graphicsView->setScene(m_scene);

    createToolBarEdit();
    createStatusBar();



    connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(slotSaveAsFile()));
    connect(actionClose, SIGNAL(triggered()), m_scene, SLOT(slotClearScene()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

    connect(actionOptions, SIGNAL(triggered()), this, SLOT(slotShowOptions()));

    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(slotZoomIn()));
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(slotZoomOut()));

    connect(actionRotateRight, SIGNAL(triggered()), this, SLOT(slotRotateRight()));
    connect(actionRotateLeft, SIGNAL(triggered()), this, SLOT(slotRotateLeft()));

    connect(actionNext, SIGNAL(triggered()), m_scene, SLOT(slotNextFile()));
    connect(actionPrev, SIGNAL(triggered()), m_scene, SLOT(slotPrevFile()));
    connect(actionResize, SIGNAL(triggered()), this, SLOT(slotShowResize()));

    connect(m_scene, SIGNAL(changeCurrentFile(QString )), this, SLOT(slotEditCurFile(QString)));

    connect(actionSelection, SIGNAL(toggled(bool )), m_scene , SLOT(slotSetSelection(bool )));

    connect(m_scene, SIGNAL(moveView(int, int)), graphicsView, SLOT(scrollContents(int, int)));

    if (fileName != "")
    {
        m_scene->loadFileList(fileName);
        m_scene->slotOpenFele(fileName);
    }
}

void MainWindow::createToolBarEdit()
{
    m_spinBoxRotate = new QSpinBox(this);

    m_spinBoxRotate->setRange(0, 360);
    m_spinBoxRotate->setSingleStep(45);
    m_spinBoxRotate->setValue(90);

    toolBarEdit->addAction(actionRotateLeft);
    toolBarEdit->addWidget(m_spinBoxRotate);
    toolBarEdit->addAction(actionRotateRight);

    m_actionGroup = new QActionGroup(this);
    m_actionGroup->addAction(actionMove);
    m_actionGroup->addAction(actionSelection);

    toolBarEdit->addAction(m_scene->actionCopy);
    toolBarEdit->addAction(m_scene->actionPaste);

    menuEdit->addAction(m_scene->actionCopy);
    menuEdit->addAction(m_scene->actionPaste);
}

void MainWindow::slotShowOptions()
{
    m_settingsForm->show();
}

void MainWindow::slotOpenFile()
{
    QString initialPath = QDir::homePath() + QObject::trUtf8("/Pictures/");
    QString fileName = QFileDialog::getOpenFileName(this, QObject::trUtf8("Открыть файл"),
                                                    initialPath, tr("All Files (*.*);;"
                                                                    "Windows Bitmap file (*.bmp);;"
                                                                    "Graphic Interchange Format file (*.gif);;"
                                                                    "Joint Photographic Experts Group file (*.jpg);;"
                                                                    "Joint Photographic Experts Group (*.jpeg);;"
                                                                    "Portable Network Graphics (*.png);;"
                                                                    "Portable Bitmap (*.pbm);;"
                                                                    "Portable Graymap (*.pgm);;"
                                                                    "Portable Pixmap (*.ppm);;"
                                                                    "Tagged Image File Format (*.tiff);;"
                                                                    "X11 Bitmap (*.xbm);;"
                                                                    "X11 Pixmap (*.xpm)"));
    if (fileName != NULL)
    {
        m_scene->loadFileList(fileName);
        m_scene->slotOpenFele(fileName);
    }


}

void MainWindow::slotSaveAsFile()
{
    QString initialPath = QDir::homePath() + QObject::trUtf8("/Pictures/untitled");

    QString fileName = QFileDialog::getSaveFileName(this, QObject::trUtf8("Сохранить файл как"),
                                   initialPath, tr("Windows Bitmap file (*.bmp);;"
                                                   "Joint Photographic Experts Group file (*.jpg);;"
                                                   "Joint Photographic Experts Group (*.jpeg);;"
                                                   "Portable Network Graphics (*.png);;"
                                                   "Portable Pixmap (*.ppm);;"
                                                   "Tagged Image File Format (*.tiff);;"
                                                   "X11 Bitmap (*.xbm);;"
                                                   "X11 Pixmap (*.xpm);;"
                                                   "All Files (*.*)"));
    m_scene->slotSaveAsFile(fileName);
}

void MainWindow::slotEditCurFile(QString name)
{
    setWindowTitle(name);
    graphicsView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
    labelStatusBar->setText(QString::number(m_scene->sceneRect().width())
                            + "x" + QString::number(m_scene->sceneRect().height()));


}

void MainWindow::createStatusBar()
{
    labelStatusBar = new QLabel(QObject::trUtf8("Файл не загружен (Используйте: Файл->Открыть)"));
    QMainWindow::statusBar()->addWidget(labelStatusBar);
}

void MainWindow::slotShowResize()
{
    QSize t_oldSize(m_scene->sceneRect().width(), m_scene->sceneRect().height());
    QSize t_newSize = MResize::setNewSize(this, t_oldSize);
    if ((t_oldSize.width() != t_newSize.width())&(t_newSize.width() != -1)) {
        m_scene->setNewSize(t_newSize);
    }
}

void MainWindow::slotRotateRight()
{
    m_scene->slotRotateRight(m_spinBoxRotate->value());
}

void MainWindow::slotRotateLeft()
{
    m_scene->slotRotateLeft(m_spinBoxRotate->value());
}

void MainWindow::slotZoomIn()
{
    graphicsView->scale(2, 2);
}

void MainWindow::slotZoomOut()
{
    graphicsView->scale(0.5, 0.5);
}

MainWindow::~MainWindow()
{

}

