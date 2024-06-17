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
    void setDark(bool isDark);
private:
    Ui::frmSettings *ui;
    bool Dark=false;
};

#endif // FRMSETTINGS_H
