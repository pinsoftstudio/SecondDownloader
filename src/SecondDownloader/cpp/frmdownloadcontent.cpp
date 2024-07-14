#include "header/frmdownloadcontent.h"
#include "ui_frmdownloadcontent.h"
#include <QSettings>
#include <QFile>
#include "mainwindow.h"
#include "header/Style.h"
#include "QTreeWidgetItem"
#include "QMenu"
#include "QActionGroup"
frmDownloadContent::frmDownloadContent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmDownloadContent)
{
    ui->setupUi(this);
    ui->treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onCustomContextMenuRequested(QPoint)));


    ui->btnSelect->setProperty("highlight","true");
     MainWindow *Parent;
    Parent=qobject_cast<MainWindow *>(parent);
    connect(Parent,SIGNAL(downloadThreadExist(DownloadWindow*)),this,SLOT(onExistSThread(DownloadWindow*)));

}

frmDownloadContent::~frmDownloadContent()
{
    delete ui;
}

void frmDownloadContent::setDark(bool isDark)
{
    QFile *qssFile=new QFile(this);
    if(isDark)
        qssFile->setFileName(":/mainform/qss/dark_frmmain.qss");
    else
        qssFile->setFileName(":/mainform/qss/white_frmmain.qss");
    qssFile->open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile->readAll());
    qssFile->close();
    setStyleSheet(styleSheet);
}


void frmDownloadContent::onExistSThread(DownloadWindow* downloadwindow)
{
    downloaders.append(downloadwindow);
    //下面的操作...
}

void frmDownloadContent::on_btnSelect_clicked(bool checked)
{
    if(checked){
        ui->btnSelect->setText("取消全选(&C)");
        ui->treeWidget->selectAll();

    }else{
         ui->btnSelect->setText("全选(&S)");
         ui->treeWidget->clearSelection();

    }
}

void frmDownloadContent::onCustomContextMenuRequested(const QPoint &pos)
{
    if(ui->treeWidget->selectedItems().isEmpty()){
        return;
    }
    QMenu *treeMenu=new QMenu(ui->treeWidget);
    QAction *actOpen=new QAction(tr("打开(&O)"),ui->treeWidget);
    QAction *actOpenFolder=new QAction(tr("打开文件夹(&F)"),ui->treeWidget);
    QAction *actReDownload=new QAction(tr("重新下载(&R)"),ui->treeWidget);
    QAction *actDonwload=new QAction(tr("下载(&D)"),ui->treeWidget);
    QAction *actDelete=new QAction(tr("删除(&R)"),ui->treeWidget);
    QAction *actProperty=new QAction(tr("属性(&P)"),ui->treeWidget);
    QMenu *subMenu = treeMenu->addMenu(tr("双击时(&D)"));
    QAction *actDoubleOpen=new QAction(tr("打开文件"),subMenu);
    QAction *actDoubleFolder=new QAction(tr("打开文件夹"),subMenu);
    QAction *actDoubleProperty=new QAction(tr("打开“属性”对话框"),subMenu);
    QActionGroup *groupDoubleToDo=new QActionGroup(treeMenu);
    groupDoubleToDo->addAction(actDoubleFolder);
    groupDoubleToDo->addAction(actDoubleOpen);
    groupDoubleToDo->addAction(actDoubleProperty);
    subMenu->addAction(actDoubleFolder);
    subMenu->addAction(actDoubleOpen);
    subMenu->addAction(actDoubleProperty);

    treeMenu->addAction(actOpen);
    treeMenu->addAction(actOpenFolder);
    treeMenu->addAction(actReDownload);
    treeMenu->addAction(actDonwload);
    treeMenu->addAction(actDelete);
    treeMenu->addMenu(subMenu);
    treeMenu->addAction(actProperty);
    treeMenu->exec(QCursor::pos());



}

void frmDownloadContent::addTreeItems(QString memoryShareName)
{
    QSharedMemory *innerMemory=new QSharedMemory(memoryShareName);
    innerMemory->detach();

}

