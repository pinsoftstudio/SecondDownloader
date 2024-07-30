#include "dialogabout.h"
#include "ui_dialogabout.h"
#include "QDesktopServices"
#include "Style.h"
DialogAbout::DialogAbout(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
     ui->label_3->setStyleSheet("color:grey;");

}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_btnGithub_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/pinsoftstudio/SecondDownloader"));
}

