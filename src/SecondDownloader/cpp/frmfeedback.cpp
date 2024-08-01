#include "header/frmfeedback.h"
#include "ui_frmfeedback.h"
#include "QDesktopServices"
frmFeedback::frmFeedback(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmFeedback)
{
    ui->setupUi(this);
    QWebEngineView *webView=new QWebEngineView(ui->widget);
    QVBoxLayout *layout = new QVBoxLayout(ui->widget);
    layout->addWidget(webView);
    webView->load(QUrl("https://forms.office.com/r/B78YZndgYz"));


}

frmFeedback::~frmFeedback()
{
    delete ui;
}

void frmFeedback::on_btnStar_2_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/pinsoftstudio/SecondDownloader/issues/new"));
}

