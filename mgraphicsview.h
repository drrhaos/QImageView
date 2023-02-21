#ifndef MGRAPHICSVIEW_H
#define MGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QApplication>
#include <QDebug>
#include <QScrollBar>

class MGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MGraphicsView(QWidget *parent = 0);
    ~MGraphicsView();
protected slots:
    virtual void wheelEvent (QWheelEvent * event );
    virtual void scrollContents(int dx, int dy);




private:

};

#endif // MGRAPHICSVIEW_H
