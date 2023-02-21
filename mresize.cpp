#include "mresize.h"


MResize::MResize(QWidget *parent, QSize t_size) :
    QDialog(parent)
{
    setupUi(this);
    m_oldSize = t_size;
    m_tempSize = t_size;
    loadCurrent();

    connect(doubleSpinBoxWidth, SIGNAL(valueChanged ( double )), this, SLOT(slotSetNewSize()));
    connect(doubleSpinBoxHeight, SIGNAL(valueChanged ( double )), this, SLOT(slotSetNewSize()));

    connect(spinBoxWidthPercent, SIGNAL(valueChanged ( int)), this, SLOT(slotSetNewSize()));
    connect(spinBoxHeightPercent, SIGNAL(valueChanged (int )), this, SLOT(slotSetNewSize()));

    connect(radioButtonPixel, SIGNAL(clicked(bool)), this, SLOT(slotEditType()));
    connect(radioButtonSm, SIGNAL(clicked(bool)), this, SLOT(slotEditType()));

    connect(pushButtonApply, SIGNAL(clicked(bool)), this, SLOT(slotApply()));
    connect(pushButtonCancel, SIGNAL(clicked(bool)), this, SLOT(slotCancel()));


}



MResize::~MResize()
{

}

QSize MResize::setNewSize(QWidget *parent, QSize t_size)
{
    MResize dialog(parent, t_size);
    dialog.exec();

    return dialog.getNewSize();
}

void MResize::slotEditType()
{
    if (radioButtonPixel->isChecked())
    {
        doubleSpinBoxWidth->setDecimals(0);
        doubleSpinBoxHeight->setDecimals(0);
        doubleSpinBoxWidth->setValue((double)m_oldSize.width());
        label_4->setText(QObject::trUtf8("Пикселей"));
    }

    if (radioButtonSm->isChecked())
    {
        doubleSpinBoxWidth->setDecimals(2);
        doubleSpinBoxHeight->setDecimals(2);
        doubleSpinBoxWidth->setValue(m_oldSize.width() / 37.79527559055);
        label_4->setText(QObject::trUtf8("Сантиметров"));
    }
}

void MResize::slotSetNewSize()
{
    if (groupBox_2->isChecked()) {
            double m_w = doubleSpinBoxWidth->value() / (double)m_oldSize.width();
            double m_h = doubleSpinBoxHeight->value() / (double)m_oldSize.height();

            if (m_tempSize.width() != (int)doubleSpinBoxWidth->value())
            {
                doubleSpinBoxHeight->setValue((int)(m_w * m_oldSize.height()));
                m_tempSize.setWidth((int)(doubleSpinBoxWidth->value()));
                m_tempSize.setHeight((int)(m_w * m_oldSize.height()));
            }else if (m_tempSize.height() != (int)doubleSpinBoxHeight->value())
            {
                doubleSpinBoxWidth->setValue((int)(m_h * m_oldSize.width()));
                m_tempSize.setHeight((int)(doubleSpinBoxHeight->value()));
                m_tempSize.setWidth((int)(m_h * m_oldSize.width()));
            }
    }else if (groupBox_3->isChecked()) {
        if(pushButtonCocked->isChecked())
        {

            if ((100 * m_tempSize.width()) / m_oldSize.width() != (int)spinBoxWidthPercent->value())
            {
                m_tempSize.setWidth((int)(100 * m_oldSize.width() / spinBoxWidthPercent->value()));
                m_tempSize.setHeight((int)(100 * m_oldSize.height() / spinBoxWidthPercent->value()));
                spinBoxHeightPercent->setValue(spinBoxWidthPercent->value());
            }else if ((100 * m_tempSize.height()) / m_oldSize.height() != (int)spinBoxHeightPercent->value())
            {
                m_tempSize.setWidth((int)(100 * m_oldSize.width() / spinBoxHeightPercent->value()));
                m_tempSize.setHeight((int)(100 * m_oldSize.height() / spinBoxHeightPercent->value()));
                spinBoxWidthPercent->setValue(spinBoxHeightPercent->value());
            }
        }else{
            m_tempSize.setWidth((int)(spinBoxWidthPercent->value() * m_oldSize.width() / 100));
            m_tempSize.setHeight((int)(spinBoxHeightPercent->value() * m_oldSize.height() / 100));
        }
    }

    qDebug() << (100 * m_tempSize.width()) / m_oldSize.width();
    qDebug() << spinBoxWidthPercent->value();

    labelNewSize->setText(QString::number(m_tempSize.width()) + "x" + QString::number(m_tempSize.height()));
}

void MResize::slotApply()
{
    if(radioButtonPixel->isChecked())
    {
        m_newSize = m_tempSize;
    }else{
        m_newSize = m_tempSize * 37.79527559055;
    }
    close();
}

void MResize::slotCancel()
{
    close();
}

void MResize::loadCurrent()
{
    labelCurSize->setText(QString::number(m_oldSize.width()) + "x" + QString::number(m_oldSize.height()));
    labelNewSize->setText(QString::number(m_oldSize.width()) + "x" + QString::number(m_oldSize.height()));

    doubleSpinBoxWidth->setValue(m_oldSize.width());
    doubleSpinBoxHeight->setValue(m_oldSize.height());

}
