#include "header/frmextention.h"
#include "ui_frmextention.h"
#include "QDesktopServices"
#include "downloadmessagewindow.h"
frmExtention::frmExtention(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmExtention)
{
    ui->setupUi(this);
}

frmExtention::~frmExtention()
{
    delete ui;
}

void frmExtention::on_btnStore_clicked()
{
    QDesktopServices::openUrl(QUrl("https://microsoftedge.microsoft.com/addons/detail/nddleeafheponjahfglnejeajlfkcibf"));

}


void frmExtention::on_btnCrx_clicked()
{
    DownloadMessageWindow *dm=new DownloadMessageWindow("https://gitee.com/pinsoft/sdup/raw/master/com.pinsoft.sder.crx"
                                                          ,nullptr,1);
    dm->setAttribute(Qt::WA_DeleteOnClose);
    dm->show();
}

