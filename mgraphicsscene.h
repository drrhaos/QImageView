#ifndef MGRAPHICSSCENE_H
#define MGRAPHICSSCENE_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>
#include <QClipboard>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QFileInfo>
#include <QDir>
#include <QAction>
#include <QMenu>
#include <QMimeData>
#include <QCursor>
#include <QMessageBox>
#include <QIcon>
#include <QGraphicsSceneMouseEvent>


#include "msettings.h"


class MGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MGraphicsScene(QWidget *parent = 0);
    ~MGraphicsScene();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void keyPressEvent ( QKeyEvent * keyEvent );

public slots:
    virtual void paintEvent();
    void slotOpenFele(QString fileName);
    void slotSaveAsFile(QString fileName);
    void slotRotateRight(int angle);
    void slotRotateLeft(int angle);
    void slotNextFile();
    void slotPrevFile();
    void slotSetSelection(bool selected);
    void slotClearScene();


signals:
    void areaIsSelected();
    void moveView(int dx, int dy);
    void changeCurrentFile(QString name);

public:
    QGraphicsRectItem *m_rect;
    int x0, y0, x1, y1;
    bool mousePress;
    QDir m_currentDir;
    QStringList m_currentFileList;

    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;

    void loadFileList(QString fileName);

    void checkStatActions();
    void setNewSize(QSize s);
private slots:
    void copyToClipboard();
    void pasteClipboard();
    void cutToClipboard();

private:
    QGraphicsPixmapItem *m_item;
    QPixmap m_pixmap;
    QColor m_color;
    MSettings *m_settingsForm;
    settings_app m_settingsData;
    QString m_fileName;
    bool m_selected;
    QMenu *m_popup;



    void leftMouseRelease(qreal x, qreal y);
    void rightMouseRelease(qreal x, qreal y);
    void createPopupMenu();
    void showPopup();

};

#endif // MGRAPHICSSCENE_H
