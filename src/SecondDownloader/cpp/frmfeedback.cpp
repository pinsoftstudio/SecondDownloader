#include "header/frmfeedback.h"
#include "ui_frmfeedback.h"

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
