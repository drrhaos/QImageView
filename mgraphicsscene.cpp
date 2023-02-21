#include "mgraphicsscene.h"

MGraphicsScene::MGraphicsScene(QWidget *parent)
{
    m_settingsForm = new MSettings;
    m_settingsData = m_settingsForm->loadSettings();
    createPopupMenu();

    mousePress = false;
    x0 = 0;
    y0 = 0;
    x1 = 0;
    y1 = 0;
    m_rect = 0;
    m_selected = false;
    connect(this, SIGNAL(areaIsSelected()), this, SLOT(paintEvent()));

}

MGraphicsScene::~MGraphicsScene()
{


}

void MGraphicsScene::createPopupMenu()
{
    actionCopy = new QAction(QIcon(":/icon/copy.png"), QObject::trUtf8("Копировать"), this);
    actionCopy->setShortcut(QKeySequence(trUtf8("Ctrl+C")));
    actionCut = new QAction(QIcon(":/icon/cut.png"), QObject::trUtf8("Вырезать"), this);
    actionCut->setShortcut(QKeySequence(trUtf8("Ctrl+X")));
    actionPaste = new QAction(QIcon(":/icon/paste.png"), QObject::trUtf8("Вставить"), this);
    actionPaste->setShortcut(QKeySequence(trUtf8("Ctrl+V")));

    m_popup = new QMenu();

    m_popup->addAction(actionCopy);
    m_popup->addAction(actionCut);
    m_popup->addAction(actionPaste);

    connect(actionCopy, SIGNAL(triggered(bool)), this, SLOT(copyToClipboard()));
    connect(actionCopy, SIGNAL(triggered(bool)), this, SLOT(cutToClipboard()));
    connect(actionPaste, SIGNAL(triggered(bool)), this, SLOT(pasteClipboard()));

    checkStatActions();
}

void MGraphicsScene::showPopup()
{
    checkStatActions();
    m_popup->popup(QCursor::pos());
}

void MGraphicsScene::checkStatActions()
{
    if (m_rect != NULL)
    {
        actionCopy->setEnabled(true);
        actionCut->setEnabled(true);
    }else{
        actionCopy->setEnabled(false);
        actionCut->setEnabled(false);
    }

    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();

    if (mimeData->hasImage())
    {
        actionPaste->setEnabled(true);
    }else{
        actionPaste->setEnabled(false);
    }

}

void MGraphicsScene::setNewSize(QSize s)
{
    m_item->setPixmap(m_item->pixmap().scaled(s, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setSceneRect(m_item->pixmap().rect());
    qDebug() << s.width();
    qDebug() << m_item->pixmap().rect().width();
}

void MGraphicsScene::paintEvent()
{
    if (m_rect != NULL) {
        delete m_rect;
        m_rect = NULL;
    }

    QPen pen;
    pen.setColor(Qt::white);
    pen.setStyle(Qt::DashLine);

    if ((x0 < x1)and(y0 < y1))
    {
        m_rect = addRect(x0 - 1 , y0 - 1, x1 - x0, y1 - y0, pen);
    }
    if ((x0 > x1)and(y0 < y1))
    {
        m_rect = addRect(x1, y0 - 1, x0 - x1 - 1, y1 - y0, pen);
    }
    if ((x0 < x1)and(y0 > y1))
    {
        m_rect = addRect(x0 - 1, y1, x1 - x0, y0 - y1 - 1, pen);
    }
    if ((x0 > x1)and(y0 > y1))
    {
        m_rect = addRect(x1, y1, x0 - x1 - 1, y0 - y1 - 1, pen);
    }
}

void MGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if((mouseEvent->button() == Qt::LeftButton) and (m_selected == true) and (sceneRect().width() != 0))
    {
        QApplication::setOverrideCursor(Qt::CrossCursor);
        if (m_rect != NULL) {
            delete m_rect;
            m_rect = 0;
        }

        mousePress = true;
        x0 = mouseEvent->lastScenePos().x();
        y0 = mouseEvent->lastScenePos().y();
    }

    if((mouseEvent->button() == Qt::LeftButton) and (m_selected == false))
    {
        mousePress = true;
        x0 = mouseEvent->lastScenePos().x();
        y0 = mouseEvent->lastScenePos().y();
    }

    if (mouseEvent->button() == Qt::RightButton)
    {
       showPopup();
    }

    if((mouseEvent->button() == Qt::LeftButton) and (m_selected == false) and (m_fileName != ""))
    {
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    }
}


void MGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ((mousePress == true)and(m_selected == true))
    {
        x1 = event->lastScenePos().x();
        y1 = event->lastScenePos().y();

        if (x0 < sceneRect().x())
            x0 = sceneRect().x();
        if (y0 < sceneRect().y())
            y0 = sceneRect().y();
        if (x1 < sceneRect().x())
            x1 = sceneRect().x();
        if (y1 < sceneRect().y())
            y1 = sceneRect().y();

        if (x0 > sceneRect().width())
            x0 = sceneRect().width();
        if (y0 > sceneRect().height())
            y0 = sceneRect().height();
        if (x1 > sceneRect().width())
            x1 = sceneRect().width();
        if (y1 > sceneRect().height())
            y1 = sceneRect().height();

        update();
        emit areaIsSelected();
    }

    if ((mousePress == true)and(m_selected == false))
    {
        x1 = event->lastScenePos().x();
        y1 = event->lastScenePos().y();
//        qDebug() << "x0 = " << x0;
//        qDebug() << "x1 = " << x1;
//        qDebug() << "y0 = " << y0;
//        qDebug() << "y1 = " << y1;

        emit moveView(x1 - x0, y1 - y0);
        x0 = x1;
        y0 = y1;

    }



}

void MGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        mousePress = false;
    }
    checkStatActions();
}


void MGraphicsScene::keyPressEvent(QKeyEvent *keyEvent)
{
    if ((keyEvent->key() == Qt::Key_C)  && QApplication::keyboardModifiers()&& Qt::ControlModifier)
    {
        copyToClipboard();
    }

    if ((keyEvent->key() == Qt::Key_V)  && QApplication::keyboardModifiers() && Qt::ControlModifier)
    {
        pasteClipboard();
    }

    if (keyEvent->key() == Qt::Key_Right)
    {
        slotNextFile();
    }

    if (keyEvent->key() == Qt::Key_Left)
    {
        slotPrevFile();
    }
    checkStatActions();
}

void MGraphicsScene::copyToClipboard()
{
    if ( m_rect != 0)
    {
        QRect t_rect = QRect(m_rect->rect().x() + 1, m_rect->rect().y() + 1, m_rect->rect().width() - 1, m_rect->rect().height() - 1);
        QImage image;
        image = QImage(width(), height(), QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&image);
        render(&painter);
        painter.end();

        QPixmap pixmap;
        pixmap = QPixmap::fromImage(image);
        pixmap = pixmap.copy(t_rect);
        QImage imageRect;
        image = QImage(t_rect.width(), t_rect.height(), QImage::Format_ARGB32_Premultiplied);
        imageRect = pixmap.toImage();

        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setImage(imageRect);
    }
    checkStatActions();
}

void MGraphicsScene::cutToClipboard()
{

}

void MGraphicsScene::pasteClipboard()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    if (mimeData->hasImage())
    {
        clear();
        QPixmap t_pixmap;
        t_pixmap = clipboard->pixmap();

        m_item = new QGraphicsPixmapItem();
        m_item->setPixmap(t_pixmap);
        addItem(m_item);
        emit changeCurrentFile("QImageView Clipboard");
        setSceneRect(m_item->pixmap().rect());
    }
    checkStatActions();
}

void MGraphicsScene::loadFileList(QString fileName)
{
    QFileInfo t_info(fileName);
    m_currentDir = t_info.absoluteDir();
    m_currentFileList = m_currentDir.entryList(QStringList() << "*.bmp" << "*.gif" << "*.jpg"
                           << "*.jpeg" << "*.png" << "*.pbm" << "*.pgm"
                           << "*.ppm" << "*.tiff" << "*.xbm" << "*.xpmb");

}

void MGraphicsScene::slotOpenFele(QString fileName)
{
    if (fileName != "")
    {
        m_fileName = fileName;
        clear();
        m_item = new QGraphicsPixmapItem();
        m_item->setPixmap(QPixmap(m_fileName));
        addItem(m_item);
        setSceneRect(m_item->pixmap().rect());
        emit changeCurrentFile("QImageView " + m_fileName);
    }
}

void MGraphicsScene::slotSaveAsFile(QString fileName)
{
    if (fileName != "")
    {
        m_fileName = fileName;
        loadFileList(m_fileName);
        setBackgroundBrush(QBrush(m_settingsData.colorBackgroundImage));
        QImage image;
        image = QImage(width(), height(), QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&image);
        render(&painter);
        setBackgroundBrush(QBrush(m_settingsData.colorBackgroundView));
        image.save(m_fileName);
        painter.end();
        emit changeCurrentFile("QImageView " + m_fileName);
    }
}

void MGraphicsScene::slotRotateRight(int angle)
{
    qreal t_x = m_item->pixmap().rect().width()/2;
    qreal t_y = m_item->pixmap().rect().height()/2;
    m_item->setTransform(QTransform().translate(t_x, t_y).rotate(angle).translate(-t_x, -t_y));
    setSceneRect(m_item->pixmap().rect());
}

void MGraphicsScene::slotRotateLeft(int angle)
{
    qreal t_x = m_item->pixmap().width()/2;
    qreal t_y = m_item->pixmap().rect().height()/2;
    m_item->setTransform(QTransform().translate(t_x, t_y).rotate(-angle).translate(-t_x, -t_y));
    setSceneRect(m_item->pixmap().rect());
}

void MGraphicsScene::slotNextFile()
{
    int t_nextIndex;
    t_nextIndex = m_currentFileList.indexOf(QFileInfo(m_fileName).fileName()) + 1;
    if (t_nextIndex < m_currentFileList.count())
    {
        m_fileName = m_currentDir.path() + "/" +  m_currentFileList.at(t_nextIndex);
        slotOpenFele(m_fileName);
    }else{
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/icon/qimageview.png"));
        msgBox.setText(QObject::trUtf8("Это последний файл, начать просмотр с начала?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Yes, QObject::trUtf8("Да"));
        msgBox.setButtonText(QMessageBox::No, QObject::trUtf8("Нет"));
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Yes:
              t_nextIndex = 0;
              m_fileName = m_currentDir.path() + "/" +  m_currentFileList.at(t_nextIndex);
              slotOpenFele(m_fileName);
              break;
          default:
              break;
        }
    }
}

void MGraphicsScene::slotPrevFile()
{
    int t_prevIndex;
    t_prevIndex = m_currentFileList.indexOf(QFileInfo(m_fileName).fileName()) - 1;
    if (t_prevIndex >= 0)
    {
        m_fileName = m_currentDir.path() + "/" +  m_currentFileList.at(t_prevIndex);
        slotOpenFele(m_fileName);
    }else{
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/icon/qimageview.png"));
        msgBox.setText(QObject::trUtf8("Это первый файл, начать просмотр с конца?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Yes, QObject::trUtf8("Да"));
        msgBox.setButtonText(QMessageBox::No, QObject::trUtf8("Нет"));
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Yes:
              t_prevIndex = m_currentFileList.count() - 1;
              m_fileName = m_currentDir.path() + "/" +  m_currentFileList.at(t_prevIndex);
              slotOpenFele(m_fileName);
              break;
          default:
              break;
        }
    }
}

void MGraphicsScene::slotSetSelection(bool selected)
{
    m_selected = selected;
}

void MGraphicsScene::slotClearScene()
{
    clear();
    setSceneRect(0,0,0,0);
    emit changeCurrentFile("QImageView");
}

