#include "header/frmextention.h"
#include "ui_frmextention.h"
#include "QDesktopServices"
#include "downloadmessagewindow.h"
#include <dialogcrtinf.h>
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


void frmExtention::on_btnchrome_clicked()
{
    DialogCrtInf da;
    QString title="暂时不受支持";
    QString text="暂时不支持谷歌浏览器,未来将添加支持!";
    da.setTitle(title);
    da.setText(text);
    da.exec();
}


void frmExtention::on_btn360_clicked()
{
    DialogCrtInf da;
    QString title="暂时不能很好兼容";
    QString text="暂时不支持360浏览器,未来将尽力兼容!";
    da.setTitle(title);
    da.setText(text);
    da.exec();
}


void frmExtention::on_btnMolizza_clicked()
{
    DialogCrtInf da;
    QString title="暂时不受支持";
    QString text="暂时不支持火狐浏览器,未来将添加支持!";
    da.setTitle(title);
    da.setText(text);
    da.exec();
}


void frmExtention::on_btnmsedge_clicked()
{
    QString videoBilibili="https://www.bilibili.com/video/BV1ecete1Eim/?vd_source=1f53d50e4c3a6bc4aae303ad114ef2c0";
    QDesktopServices::openUrl(QUrl(videoBilibili));
}

