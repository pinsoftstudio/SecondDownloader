#include "header/frmdownloadcontent.h"
#include "ui_frmdownloadcontent.h"
#include <QSettings>
#include <QFile>
#include "mainwindow.h"
#include "header/Style.h"
#include "QTreeWidgetItem"
#include "QMenu"
#include "QActionGroup"
#include "QBuffer"
#include "QThread"
#include "QDataStream"
#include "QFileInfo"
#include "QDir"

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
    innerMemory=new QSharedMemory;
    sdGetKey=new QSharedMemory;
    updateShare=new QSharedMemory;
    sdGetKey->setKey("passkey");
    if(!sdGetKey->create(1024)){
        sdGetKey->attach(QSharedMemory::ReadOnly);
    }
    tmGetNewShareName=new QTimer;
    tmGetNewShareName->setInterval(1);
    connect(tmGetNewShareName,&QTimer::timeout,this,&frmDownloadContent::onTMGetNewShareName);
    tmGetNewShareName->start();
    tmUpdateShare=new QTimer;
    connect(tmUpdateShare,&QTimer::timeout,this,&frmDownloadContent::onUpdateShare);
    tmUpdateShare->start(100);
    tmRefreashDat=new QTimer;
    connect(tmRefreashDat,&QTimer::timeout,this,&frmDownloadContent::refreashDatFile);
    tmRefreashDat->start(5000);
    setDisplayMode(frmDownloadContent::all);

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

void frmDownloadContent::onTMGetNewShareName()
{
    getShareName();
}

void frmDownloadContent::onUpdateShare()
{
    if(keyGetted.count()>0){
        foreach (const QString aKey, keyGetted) {
            QString urlGetted;
            QString filePathNameGetted;
            QString stateGetted;
            QString sizeGetted;
            QString finalState;
            QString speed;
            updateShare->setKey(aKey);
            if(!updateShare->create(4096)){
                updateShare->attach();
            }
            if(updateShare->lock()){
                QBuffer getBuffer;
                getBuffer.setData((char*)updateShare->constData(),updateShare->size());
                getBuffer.open(QBuffer::ReadWrite);
                QDataStream stream (&getBuffer);
                stream>>filePathNameGetted>>urlGetted>>stateGetted>>sizeGetted>>speed;
                getBuffer.close();
                innerMemory->unlock();

                if(stateGetted=="pre"){
                    finalState=tr("准备下载");
                }else if(stateGetted=="downloading"){
                    finalState=tr("正在下载");
                }else if(stateGetted=="failed"){
                    finalState=tr("下载失败");
                }else if(stateGetted=="succeed"){
                    finalState=tr("下载成功");
                }

                int  count=ui->treeWidget->topLevelItemCount();
                for(int i=0;i<count;i++){
                    QTreeWidgetItem *aitem=ui->treeWidget->topLevelItem(i);
                    if(aitem->
                        data(frmDownloadContent::filesize,Qt::UserRole)==aKey){
                        aitem->setText(frmDownloadContent::state,finalState);
                        aitem->setData(frmDownloadContent::state,Qt::UserRole,QVariant(stateGetted));
                        if(finalState=="下载成功" || finalState=="下载失败"){
                            aitem->setText(frmDownloadContent::downloadSpeed,"");
                        }else{
                            aitem->setText(frmDownloadContent::downloadSpeed,speed);
                        }

                        aitem=nullptr;
                    }
                }

            }
            updateShare->detach();
        }
    }

}

void frmDownloadContent::addTreeItems(QString memoryShareName)
{
    qDebug()<<"Name:"<<memoryShareName;
    QBuffer getBuffer;
    QDataStream stream;
    QString urlGetted="";
    QString filePathNameGetted;
    QString stateGetted;
    QString sizeGetted;
    QString finalState;
    QString speed;
    innerMemory->setKey(memoryShareName);
    tryagain:
    if(!innerMemory->create(4096)){
            qDebug()<<"Name:"<<memoryShareName;
            if(!innerMemory->attach()){
            qDebug()<<"innerMemory attach error";
            }else{
                qDebug()<<"innerMemory attach suc";
            }
    }

    if(!innerMemory->lock()){
        qDebug()<<"innerMemory failed to lock!";
        return;
    }

    getBuffer.setData((char*)innerMemory->constData(),innerMemory->size());
    getBuffer.open(QBuffer::ReadWrite);
    stream.setDevice(&getBuffer);
    stream>>filePathNameGetted>>urlGetted>>stateGetted>>sizeGetted>>speed;
    getBuffer.close();
    innerMemory->unlock();
    if(urlGetted==""){
        qDebug()<<urlGetted;
        QThread::msleep(1000);
        innerMemory->detach();
        goto tryagain;
    }
    QTreeWidgetItem *newItem=new QTreeWidgetItem(ui->treeWidget);

    newItem->setText(frmDownloadContent::fileName,
                     QFileInfo(QDir::toNativeSeparators(filePathNameGetted)).fileName());
    newItem->setText(frmDownloadContent::filesize,sizeGetted);
    newItem->setText(frmDownloadContent::downloadSpeed,speed);
    newItem->setData(frmDownloadContent::fileName,Qt::UserRole,QVariant(urlGetted));
    newItem->setData(frmDownloadContent::filesize,Qt::UserRole,QVariant(memoryShareName));
    newItem->setData(frmDownloadContent::state,Qt::UserRole,QVariant(stateGetted));
    if(stateGetted=="pre"){
        finalState=tr("准备下载");
    }else if(stateGetted=="downloading"){
        finalState=tr("正在下载");
    }else if(stateGetted=="failed"){
        finalState=tr("下载失败");
    }else if(stateGetted=="succeed"){
        finalState=tr("下载成功");
    }
    newItem->setText(frmDownloadContent::state,finalState);

    keyGetted.append(memoryShareName);
    ui->treeWidget->addTopLevelItem(newItem);





}

void frmDownloadContent::getShareName()
{
    QString key;

    // getNewShareName=new QSharedMemory("passkey");
    if(sdGetKey->create(1024)){
        sdGetKey->attach();
    }
    link:

    if(!sdGetKey->lock()){
        QThread::msleep(1000);
        goto link;
    }
    QBuffer buffer;
    buffer.setData((char*)sdGetKey->constData(),sdGetKey->size());
    buffer.open(QBuffer::ReadWrite);
    QDataStream stream(&buffer);
    stream>>key;

    if(key!=""){

        sdGetKey->unlock();

    link1:
        if(!sdGetKey->lock()){
            QThread::msleep(1000);
            goto link1;
        }
        QString empty="";
        char *toKey=static_cast<char*>(sdGetKey->data());
        QBuffer keyBuffer;
        keyBuffer.open(QBuffer::WriteOnly);
        QDataStream keyStream(&keyBuffer);
        keyStream<<empty;

        memcpy(toKey,keyBuffer.data(),keyBuffer.size());
        sdGetKey->unlock();
        QString passKeystr=key;
        key="";
        addTreeItems(passKeystr);


    }




}

void frmDownloadContent::refreashDatFile()
{
    if(!QDir("data/").exists()){QDir().mkdir("data/");}
    QFile dataFile("data/download.dat");
    if(dataFile.open(QIODevice::WriteOnly)){
        QDataStream datastream(&dataFile);
        datastream.setByteOrder(QDataStream::LittleEndian);
        int count=ui->treeWidget->topLevelItemCount();
        for(int i=0;i<count;i++){
            QString afileName;
            QString afileSize;
            QString afileState;
            QString aurl;
            QTreeWidgetItem *aitem=ui->treeWidget->topLevelItem(i);
            afileName=aitem->text(frmDownloadContent::fileName);
            afileSize=aitem->text(frmDownloadContent::filesize);
            aurl=aitem->data(frmDownloadContent::fileName,Qt::UserRole).toString();
            afileState=aitem->data(frmDownloadContent::state,Qt::UserRole).toString();
            QByteArray btArray;
            btArray=afileName.toUtf8();
            qsizetype size=btArray.length();
            datastream.writeRawData((char*)&size,sizeof(qsizetype));
            datastream.writeBytes(btArray,btArray.length());

            btArray=afileSize.toUtf8();
            size=btArray.length();
            datastream.writeRawData((char*)&size,sizeof(qsizetype));
            datastream.writeBytes(btArray,btArray.length());

            btArray=aurl.toUtf8();
            size=btArray.length();
            datastream.writeRawData((char*)&size,sizeof(qsizetype));
            datastream.writeBytes(btArray,btArray.length());

            btArray=afileState.toUtf8();
            size=btArray.length();
            datastream.writeRawData((char*)&size,sizeof(qsizetype));
            datastream.writeBytes(btArray,btArray.length());
            aitem=nullptr;

        }

        dataFile.close();
    }

}

void frmDownloadContent::setDisplayMode(displayMode mode)
{
    int count=ui->treeWidget->topLevelItemCount();
    switch (mode) {
    case 0:
        ui->btnAll->setChecked(1);
        ui->btnDownloading->setChecked(0);
        ui->btnSucceed->setChecked(0);
        ui->btnFailed->setChecked(0);
        for(int i=0;i<count;i++){
            QTreeWidgetItem *aitem=ui->treeWidget->topLevelItem(i);
            aitem->setHidden(0);
        }

        break;
    case 1:
        ui->btnAll->setChecked(0);
        ui->btnDownloading->setChecked(1);
        ui->btnSucceed->setChecked(0);
        ui->btnFailed->setChecked(0);
        for(int i=0;i<count;i++){
            QTreeWidgetItem *aitem=ui->treeWidget->topLevelItem(i);
            if(aitem->data(frmDownloadContent::state,Qt::UserRole).toString()=="downloading"
                ||aitem->data(frmDownloadContent::state,Qt::UserRole).toString()=="pre"){
                aitem->setHidden(0);
            }else{
                aitem->setHidden(1);
            }
        }
        break;
    case 2:
        ui->btnAll->setChecked(0);
        ui->btnDownloading->setChecked(0);
        ui->btnSucceed->setChecked(1);
        ui->btnFailed->setChecked(0);
        for(int i=0;i<count;i++){
            QTreeWidgetItem *aitem=ui->treeWidget->topLevelItem(i);
            if(aitem->data(frmDownloadContent::state,Qt::UserRole).toString()=="succeed"){
                aitem->setHidden(0);
            }else{
                aitem->setHidden(1);
            }
        }
        break;
    case 3:
        ui->btnAll->setChecked(0);
        ui->btnDownloading->setChecked(0);
        ui->btnSucceed->setChecked(0);
        ui->btnFailed->setChecked(1);
        for(int i=0;i<count;i++){
            QTreeWidgetItem *aitem=ui->treeWidget->topLevelItem(i);
            if(aitem->data(frmDownloadContent::state,Qt::UserRole).toString()=="failed"){
                aitem->setHidden(0);
            }else{
                aitem->setHidden(1);
            }
        }
    }
}

void frmDownloadContent::iniTree()
{
    if(QFile("data/download.dat").exists()){
        QFile file("data/download.dat");
        if(file.open(QIODevice::ReadOnly)){
            QDataStream datastream(&file);
            datastream.setByteOrder(QDataStream::LittleEndian);
            qsizetype size;
            datastream.readRawData((char*)&size,sizeof(qsizetype));
            char *buf;
            datastream.readBytes(buf,size);
            QString filename=QString::fromLocal8Bit(buf,size);
            // QString filename=datastream.readBytes()
        }
    }

}


void frmDownloadContent::on_btnAll_clicked()
{
    setDisplayMode(frmDownloadContent::all);
}


void frmDownloadContent::on_btnDownloading_clicked()
{
    setDisplayMode(frmDownloadContent::downloading);
}


void frmDownloadContent::on_btnSucceed_clicked()
{
    setDisplayMode(frmDownloadContent::succeed);
}


void frmDownloadContent::on_btnFailed_clicked()
{
    setDisplayMode(frmDownloadContent::faild);
}

