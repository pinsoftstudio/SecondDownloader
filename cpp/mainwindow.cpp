#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configWindowStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configWindowStyle()
{
    // setFixedSize(1000,800);
    //setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint);
}
