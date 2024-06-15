#include "header/frmmainpage.h"
#include "ui_frmmainpage.h"

frmMainPage::frmMainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmMainPage)
{
    ui->setupUi(this);
}

frmMainPage::~frmMainPage()
{
    delete ui;
}
