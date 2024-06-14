#ifndef MAINFORM_H
#define MAINFORM_H
#include <frmmainpage.h>
#include <QWidget>
#include <frmdownloadcontent.h>
#include <frmsettings.h>
#include <frmdonate.h>
namespace Ui {
class mainform;
}

class mainform : public QWidget
{
    Q_OBJECT

public:
    explicit mainform(QWidget *parent = nullptr);
    ~mainform();
    void adaptWindowAndControls();
    void iniWindowMenu();
    void iniWindowFlagAndStyle();
    void addWidgetTostackedWidget();
    void adaptStackedWidgetAndSubControls();
private:
    Ui::mainform *ui;
    frmMainPage *mainPage;
    frmDownloadContent *dwncontent;
    frmSettings *set;
    frmDonate *donate;

};

#endif // MAINFORM_H
