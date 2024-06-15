#include "header/frmdonate.h"
#include "ui_frmdonate.h"

frmDonate::frmDonate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmDonate)
{
    ui->setupUi(this);
}

frmDonate::~frmDonate()
{
    delete ui;
}
