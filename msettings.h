#ifndef MSETTINGS_H
#define MSETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QColorDialog>
#include <QDir>

#include "ui_msettings.h"


struct settings_app
{
    int styleApp;
    QString language;
    QColor colorBackgroundView;
    QColor colorBackgroundImage;
};

class MSettings : public QDialog, public Ui_MSettings
{
    Q_OBJECT

public:
    explicit MSettings(QWidget *parent = 0);
    ~MSettings();
    settings_app loadSettings();



public slots:
    void saveSettings();
    void setColorView();
    void setColorImage();

private:


};

#endif // MSETTINGS_H
