#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QWidget>


namespace Ui {
class frmSettings;
}

class frmSettings : public QWidget
{
    Q_OBJECT

public:
    explicit frmSettings(QWidget *parent = nullptr);
    ~frmSettings();
private:
    Ui::frmSettings *ui;
    void iniSettings();
    QStringList getAllWavs(QString location);
};

#endif // FRMSETTINGS_H
