#include "mgraphicsview.h"


MGraphicsView::MGraphicsView(QWidget *parent)
{

}

MGraphicsView::~MGraphicsView()
{

}


void MGraphicsView::wheelEvent( QWheelEvent * event)
{
    if (QApplication::keyboardModifiers()&& Qt::ControlModifier)
    {
            double delta = event->delta();
            double sf = 1.0 + delta / 600;

            QPoint p0 = mapFromScene( 0.0, 0.0 );

            if ( p0.x() - x() < 10 || sf > 0.1 ) // точно уже не помню зачем
            {
                scale( sf, sf );
            }
    }
}

void MGraphicsView::scrollContents(int dx, int dy)
{/*
    qDebug() << "dx = " << dx;
    qDebug() << "dy = " << dy;
    qDebug() << horizontalScrollBar()->value();
    qDebug() << verticalScrollBar()->value();*/


//    qDebug() << horizontalScrollBar()->maximum();
//    qDebug() << verticalScrollBar()->maximum();
//    qDebug() << pos()->x();
//    qDebug() << pos()->y();
//    horizontalScrollBar()->setValue(100);
//    verticalScrollBar()->setValue(100);

//    move(dx, dy);
}



