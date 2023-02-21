#include "msettings.h"


MSettings::MSettings(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    loadSettings();
    QDir dir("language");
    setModal(true);
    setWindowFlags(Qt::Tool);
    QStringList fileName = dir.entryList(QStringList("*.qm"));
    foreach (QString lang, fileName) {
        comboBoxLanguage->addItem(lang.replace(".qm", ""));
    }

    connect(pushButtonColorView, SIGNAL(clicked()), this, SLOT(setColorView()));
    connect(pushButtonColorImage, SIGNAL(clicked()), this, SLOT(setColorImage()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
}

MSettings::~MSettings()
{

}

settings_app MSettings::loadSettings()
{
    settings_app t_setData;
    QSettings t_set("settings.ini", QSettings::IniFormat);

    t_setData.styleApp = t_set.value("style").toInt();

    t_setData.language = t_set.value("language").toString();
    comboBoxLanguage->setCurrentIndex(comboBoxLanguage->findText(t_setData.language));

    t_setData.colorBackgroundView = QColor(t_set.value("colorBackgroundView").toString());
    labelColorView ->setText(t_setData.colorBackgroundView.name());
    labelColorView->setPalette(QPalette(t_setData.colorBackgroundView));
    labelColorView->setAutoFillBackground(true);

    t_setData.colorBackgroundImage = QColor(t_set.value("colorBackgroundImage").toString());
    labelColorImage ->setText(t_setData.colorBackgroundImage.name());
    labelColorImage->setPalette(QPalette(t_setData.colorBackgroundImage));
    labelColorImage->setAutoFillBackground(true);

    return t_setData;
}

void MSettings::saveSettings()
{
    QSettings t_set("settings.ini", QSettings::IniFormat);
    t_set.setValue("language", comboBoxLanguage->currentText());
    t_set.setValue("colorBackgroundView", labelColorView->text());
    t_set.setValue("colorBackgroundImage", labelColorImage->text());
}


void MSettings::setColorView()
{
    QColor wColor = QColorDialog::getColor(Qt::white, this, QObject::trUtf8("Цвет"), QColorDialog::ShowAlphaChannel);

    if (wColor.isValid()) {
        labelColorView ->setText(wColor.name());
        labelColorView->setPalette(QPalette(wColor));
        labelColorView->setAutoFillBackground(true);
    }
}



void MSettings::setColorImage()
{
    QColor wColor = QColorDialog::getColor(Qt::white, this, QObject::trUtf8("Цвет"), QColorDialog::ShowAlphaChannel);

    if (wColor.isValid()) {
        labelColorImage ->setText(wColor.name());
        labelColorImage->setPalette(QPalette(wColor));
        labelColorImage->setAutoFillBackground(true);
    }
}
