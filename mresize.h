#ifndef MRESIZE_H
#define MRESIZE_H

#include <QDialog>
#include <QSize>
#include <QDebug>

#include <cmath>

#include "ui_mresize.h"

class MResize : public QDialog, public Ui_MResize
{
    Q_OBJECT

public:
    explicit MResize(QWidget *parent = 0, QSize t_size = QSize(0,0));
    ~MResize();
    static QSize setNewSize(QWidget *parent = 0, QSize t_size = QSize(0,0));
    QSize getNewSize(){return m_newSize;}

public slots:
    void slotSetNewSize();
    void slotApply();
    void slotCancel();
    void slotEditType();
private:
    QSize m_oldSize;
    QSize m_tempSize;
    QSize m_newSize;
    void loadCurrent();
};

#endif // MRESIZE_H
