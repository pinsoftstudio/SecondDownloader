#include "extdownload.h"
#include "ui_extdownload.h"

extDownload::extDownload(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::extDownload)
{
    ui->setupUi(this);
}

extDownload::~extDownload()
{
    delete ui;
}
