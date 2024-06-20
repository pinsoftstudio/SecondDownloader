#ifndef MAINFORM_H
#define MAINFORM_H
#include <QPainter>
#include <QMouseEvent>
#include <header/frmmainpage.h>
#include <QWidget>
#include <header/frmdownloadcontent.h>
#include <header/frmsettings.h>
#include <header/frmdonate.h>
#include <QRect>
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
    void configWindowStyle();
    void configWindowFlag();
    QPainter *siderBarPainter;
    void refreshStyleSheet();
private:
    Ui::mainform *ui;
    frmMainPage *mainPage;
    frmDownloadContent *dwncontent;
    frmSettings *set;
    frmDonate *donate;
    QPoint  m_lastPos;
    bool    m_moving=false;
    bool dark=false;
    QRect siderBarRect;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_btnMin_clicked();

    void on_btnChangeStyle_clicked();
    void on_btnMainPage_clicked(bool checked);
    void on_btnDownloadContent_clicked(bool checked);
    void on_btnDonate_clicked(bool checked);
    void on_btnSettings_clicked(bool checked);
};

#endif // MAINFORM_H
