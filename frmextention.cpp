#include "header/frmextention.h"
#include "ui_frmextention.h"

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
