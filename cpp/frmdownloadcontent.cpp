#include "header/frmdownloadcontent.h"
#include "ui_frmdownloadcontent.h"

frmDownloadContent::frmDownloadContent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmDownloadContent)
{
    ui->setupUi(this);
}

frmDownloadContent::~frmDownloadContent()
{
    delete ui;
}
