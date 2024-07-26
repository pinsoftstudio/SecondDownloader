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
#include "QDesktopServices"
//#include "dialogcrtinf.h"
#include "dialogquestion.h"
#include "QMessageBox"
#include "QFileIconProvider"
#include "header/propertydialog.h"
#include "downloadmessagewindow.h"
frmDownloadContent::frmDownloadContent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmDownloadContent)
{
    ui->setupUi(this);
    ui->treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onCustomContextMenuRequested(QPoint)));
    connect(ui->treeWidget,&QTreeWidget::itemChanged,this,&frmDownloadContent::refreashDatFile);


    ui->btnSelect->setProperty("highlight","true");
    if(isDark()){
        this->setStyleSheet("QPushButton {border: 1px solid rgb(63,63,63); border-bottom-color: rgb(58,58,58);border-radius: 4px;  background-color: rgb(55,55,55); color:white;}  QPushButton:hover{background-color:rgb(60,60,60);}QPushButton:pressed {  background-color: rgb(50, 50, 50); border-bottom-color:rgb(58, 58, 58);color:rgb(208,208,208);}");

    }
    sdGetKey=new QSharedMemory;
    innerMemory=new QSharedMemory;
    updateShare=new QSharedMemory;
    newUrlShare=new QSharedMemory;
    newUrlShare->setKey("newUrl");
    if(!newUrlShare->create(1024)){
        newUrlShare->attach();
    }


    sdGetKey->setKey("passkey");
    if(!sdGetKey->create(1024)){
        sdGetKey->attach();
    }

    tmGetNewShareName=new QTimer;
    tmGetNewShareName->setInterval(1000);
    connect(tmGetNewShareName,&QTimer::timeout,this,&frmDownloadContent::onTMGetNewShareName);
    tmGetNewShareName->start();

    tmUpdateShare=new QTimer;
    connect(tmUpdateShare,&QTimer::timeout,this,&frmDownloadContent::onUpdateShare);
    tmUpdateShare->start(50);
    iniTree();
    setDisplayMode(frmDownloadContent::all);


}

frmDownloadContent::~frmDownloadContent()
{
    if(tmGetNewShareName->isActive()){
        tmGetNewShareName->stop();
        disconnect(tmGetNewShareName,&QTimer::timeout,this,&frmDownloadContent::onTMGetNewShareName);
    }
    if(tmUpdateShare->isActive()){
        tmUpdateShare->stop();
        connect(tmUpdateShare,&QTimer::timeout,this,&frmDownloadContent::onUpdateShare);
    }
    if(updateShare->isAttached()){
        updateShare->detach();
    }
    if(innerMemory->isAttached()){
        innerMemory->detach();
    }
    if(sdGetKey->isAttached()){
        sdGetKey->detach();
    }

    delete ui;
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
    QTreeWidgetItem *clickedItem=ui->treeWidget->currentItem();
    QMenu *treeMenu=new QMenu(ui->treeWidget);
    QAction *actOpen=new QAction(tr("打开(&O)"),ui->treeWidget);
    QAction *actOpenFolder=new QAction(tr("打开文件夹(&F)"),ui->treeWidget);
    QAction *actReDownload=new QAction(tr("重新下载(&E)"),ui->treeWidget);
    QAction *actDownload=new QAction(tr("下载(&D)"),ui->treeWidget);
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
    treeMenu->addAction(actDownload);
    treeMenu->addAction(actDelete);
    // treeMenu->addMenu(subMenu);
    bool fileExist=QFile(QDir::fromNativeSeparators
                           (clickedItem->text(frmDownloadContent::location))).exists();
    treeMenu->addAction(actProperty);
    if(fileExist){
        actOpen->setEnabled(1);
        actOpenFolder->setEnabled(1);
        actReDownload->setEnabled(1);
        actDownload->setEnabled(0);

    }else{
        actOpen->setEnabled(0);
        actDownload->setEnabled(1);
        actReDownload->setEnabled(0);
        if(!QDir(QFileInfo(QDir::fromNativeSeparators
                          (clickedItem->text(frmDownloadContent::location)))
                     .absolutePath()).exists()){
            actOpenFolder->setEnabled(0);
        }
    }
    connect(actOpen,&QAction::triggered,[&]{

        QString pathName=QDir::fromNativeSeparators(clickedItem->text(frmDownloadContent::location));
        if(!QDesktopServices::openUrl(QUrl(pathName))){
            QMessageBox::information(this,tr("错误"),tr("无法打开文件！"),tr("确定"));
        }

        clickedItem=nullptr;
    });
    connect(actOpenFolder,&QAction::triggered,[&]{
        QString path=QFileInfo(QDir::fromNativeSeparators
                                     (clickedItem->text(frmDownloadContent::location))).absolutePath();
        if(QFile(path).exists()){
            if(!QDesktopServices::openUrl(QUrl(path))){
                QMessageBox::information(this,tr("错误"),tr("无法打开文件夹！"),tr("确定"));
            }
        }
        clickedItem=nullptr;

    });
    connect(actDelete,&QAction::triggered,[&]{
        if(fileExist){
            DialogQuestion dialog;
            QString title=tr("问题");
            QString content=tr("需要原文件需要一同删除吗？");
            dialog.setTitle(title);
            dialog.setText(content);
            int code=dialog.exec();
            if(code==DialogQuestion::Accepted){
                QFile(QDir::fromNativeSeparators
                      (clickedItem->text(frmDownloadContent::location))).remove();
                refreashDatFile();
            }
        }
        on_btnClear_clicked();

    });
    connect(actDownload,&QAction::triggered,[&]{
        QString url=clickedItem->data(frmDownloadContent::fileName,Qt::UserRole).toString();
        DownloadMessageWindow *dm=new DownloadMessageWindow(url,nullptr,1);
        dm->show();
    });
    connect(actReDownload,&QAction::triggered,[&]{
        QString url=clickedItem->data(frmDownloadContent::fileName,Qt::UserRole).toString();
        DownloadMessageWindow *dm=new DownloadMessageWindow(url,nullptr,1);
        dm->show();
    });
    connect(actProperty,&QAction::triggered,[&]{
        PropertyDialog *pd=new PropertyDialog(clickedItem->data(frmDownloadContent::fileName,Qt::UserRole).toString(),
                                                clickedItem->text(frmDownloadContent::location),
                                                clickedItem->text(frmDownloadContent::state),
                                                clickedItem->text(frmDownloadContent::filesize),
                                                this);
        pd->show();

    });


    treeMenu->exec(QCursor::pos());




}

void frmDownloadContent::onTMGetNewShareName()
{
    getShareName();
    detectNewDownload();
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
                }else{
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
                            // aitem->setText(frmDownloadContent::location,QDir::toNativeSeparators(filePathNameGetted));
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
    newItem->setText(frmDownloadContent::location,QDir::toNativeSeparators(filePathNameGetted));
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
    QFileInfo fi(QDir::fromNativeSeparators(filePathNameGetted));
    newItem->setIcon(0,QFileIconProvider().icon(fi));
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
        goto link;
    }

    QBuffer buffer;
    buffer.setData((char*)sdGetKey->constData(),sdGetKey->size());
    buffer.open(QBuffer::ReadWrite);
    QDataStream stream(&buffer);
    stream>>key;
    sdGetKey->unlock();

    if(key!=""){
        lnk:
        if(!sdGetKey->lock()){
            goto lnk;
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
        // QSettings set("Pinsoft","SecondDownloader");
        // set.setValue("DownloadContent",count);
        datastream.writeRawData((char*)&count,sizeof(int));
        for(int i=0;i<count;i++){
            QString afileName;
            QString afileSize;
            QString afileState;
            QString aurl;
            QString apathName;
            QTreeWidgetItem *aitem=ui->treeWidget->topLevelItem(i);
            afileName=aitem->text(frmDownloadContent::fileName);
            afileSize=aitem->text(frmDownloadContent::filesize);
            aurl=aitem->data(frmDownloadContent::fileName,Qt::UserRole).toString();
            afileState=aitem->data(frmDownloadContent::state,Qt::UserRole).toString();
            apathName=aitem->text(frmDownloadContent::location);
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

            btArray=apathName.toUtf8();
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
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(ui->treeWidget,&QTreeWidget::itemDoubleClicked,this,[=](QTreeWidgetItem *item, int column){
        Q_UNUSED(column);
        QFileInfo file(QDir::fromNativeSeparators(item->text(frmDownloadContent::location)));
        if(file.exists()){
            if(!QDesktopServices::openUrl(QUrl(file.absoluteFilePath()))){
                QMessageBox::information(this,tr("错误"),tr("无法打开文件！"),tr("确定"));
            }
        }

    });
    if(QFile("data/download.dat").exists()){
        QFile file("data/download.dat");
         QDataStream datastream(&file);

        // QSettings set("Pinsoft","SecondDownloader");
        // int itemCount=set.value("DownloadContent",0).toInt();
        if(file.open(QIODevice::ReadOnly)){
             int itemCount=0;
             datastream.readRawData((char*)&itemCount,sizeof(int));
            for (int i=0;i<itemCount;i++){


                datastream.setByteOrder(QDataStream::LittleEndian);
                qsizetype size;
                char *buf;
                datastream.readRawData((char*)&size,sizeof(qsizetype));
                datastream.readBytes(buf,size);
                QString afilename=QString::fromLocal8Bit(buf,size);

                datastream.readRawData((char*)&size,sizeof(qsizetype));
                datastream.readBytes(buf,size);
                QString afilesize=QString::fromLocal8Bit(buf,size);

                datastream.readRawData((char*)&size,sizeof(qsizetype));
                datastream.readBytes(buf,size);
                QString aurl=QString::fromLocal8Bit(buf,size);

                datastream.readRawData((char*)&size,sizeof(qsizetype));
                datastream.readBytes(buf,size);
                QString apathName=QString::fromLocal8Bit(buf,size);
                QTreeWidgetItem *aitem=new  QTreeWidgetItem(ui->treeWidget);

                datastream.readRawData((char*)&size,sizeof(qsizetype));
                datastream.readBytes(buf,size);
                QString astate=QString::fromLocal8Bit(buf,size);



                aitem->setText(frmDownloadContent::fileName,afilename.trimmed());
                aitem->setText(frmDownloadContent::filesize,afilesize.trimmed());
                QString finalState;
                if(astate.trimmed()=="pre"){
                    finalState=tr("准备下载");
                }else if(astate.trimmed()=="downloading"){
                    finalState=tr("正在下载");
                }else if(astate.trimmed()=="failed"){
                    finalState=tr("下载失败");
                }else if(astate.trimmed()=="succeed"){
                    finalState=tr("下载成功");
                }
                aitem->setText(frmDownloadContent::state,finalState);
                aitem->setData(frmDownloadContent::state,Qt::UserRole,QVariant(astate.trimmed()));
                aitem->setText(frmDownloadContent::location,apathName.trimmed());
                aitem->setData(frmDownloadContent::fileName,Qt::UserRole,aurl.trimmed());
                QFileInfo fi(QDir::fromNativeSeparators(apathName));
                aitem->setIcon(0,QFileIconProvider().icon(fi));
                ui->treeWidget->addTopLevelItem(aitem);
                aitem=nullptr;
            }
            file.close();
        }
    }

}

void frmDownloadContent::detectNewDownload()
{

    if(newUrlShare->lock()){

        QBuffer buffer;
        buffer.setData((char*)newUrlShare->constData(),newUrlShare->size());
        buffer.open(QBuffer::ReadWrite);
        QDataStream stream(&buffer);
        QString newUrl;
        stream>>newUrl;
        if(!newUrl.isEmpty()){
            QString empty="";
            char *Key=static_cast<char*>(newUrlShare->data());
            QBuffer Buffer;
            Buffer.open(QBuffer::WriteOnly);
            QDataStream Stream(&Buffer);
            Stream<<empty;
            memcpy(Key,Buffer.data(),Buffer.size());
            DownloadMessageWindow *downloadMs=new DownloadMessageWindow(newUrl,nullptr,1);
            downloadMs->show();
        }
        newUrlShare->unlock();

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


void frmDownloadContent::on_btnClear_clicked()
{
    QList<QTreeWidgetItem*> items=ui->treeWidget->selectedItems();
    if(items.count()==0){
        return;
    }
    foreach (QTreeWidgetItem *aitem, items) {
        ui->treeWidget->removeItemWidget(aitem,frmDownloadContent::fileName);
        ui->treeWidget->removeItemWidget(aitem,frmDownloadContent::filesize);
        ui->treeWidget->removeItemWidget(aitem,frmDownloadContent::downloadSpeed);
        ui->treeWidget->removeItemWidget(aitem,frmDownloadContent::state);
        delete aitem;
        aitem=nullptr;
        refreashDatFile();
    }

}

