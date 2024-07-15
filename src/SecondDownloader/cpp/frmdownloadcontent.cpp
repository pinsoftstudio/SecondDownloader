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
    QAction *actReDownload=new QAction(tr("重新下载(&E)"),ui->treeWidget);
    QAction *actDonwload=new QAction(tr("下载(&D)"),ui->treeWidget);
    QAction *actDelete=new QAction(tr("删除(&R)"),ui->treeWidget);
    QAction *actProperty=new QAction(tr("属性(&P)"),ui->treeWidget);

    // QActionGroup *groupDoubleToDo=new QActionGroup(subMenu);
    // groupDoubleToDo->setEnabled(1);
    // groupDoubleToDo->addAction(actDoubleFolder);
    // groupDoubleToDo->addAction(actDoubleOpen);
    // groupDoubleToDo->addAction(actDoubleProperty);
    // actDoubleFolder->setCheckable(1);
    // actDoubleOpen->setCheckable(1);
    // actDoubleProperty->setCheckable(1);
    // actDoubleFolder->setChecked(1);
    // groupDoubleToDo->setExclusionPolicy(QActionGroup::ExclusionPolicy::None);
    // subMenu->addAction(actDoubleFolder);
    // subMenu->addAction(actDoubleOpen);
    // subMenu->addAction(actDoubleProperty);
    treeMenu->addAction(actOpen);
    treeMenu->addAction(actOpenFolder);
    treeMenu->addAction(actReDownload);
    treeMenu->addAction(actDonwload);
    treeMenu->addAction(actDelete);
    // treeMenu->addMenu(subMenu);
    treeMenu->addAction(actProperty);
    connect(actOpen,&QAction::triggered,[=]{});
    connect(actOpenFolder,&QAction::triggered,[=]{});
    connect(actDelete,&QAction::triggered,[=]{});
    connect(actDelete,&QAction::triggered,[=]{});
    connect(actReDownload,&QAction::triggered,[=]{});
    connect(actProperty,&QAction::triggered,[=]{});



    treeMenu->exec(QCursor::pos());




}

void frmDownloadContent::addTreeItems(QString memoryShareName)
{
    QSharedMemory *innerMemory=new QSharedMemory(memoryShareName);
    innerMemory->detach();

}

void frmDownloadContent::getShareName()
{
    // getNewShareName=new QSharedMemory("passkey");

}

