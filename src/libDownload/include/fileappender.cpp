#include "fileappender.h"
#include "QFile"
#include "QByteArray"
#include "qDebug"
#include "QDir"
fileAppender::fileAppender(QString savinglocation,QObject *parent)

{
    savingLocation=savinglocation;
    if(parent!=nullptr) setParent(parent);

}

void fileAppender::addToFileList(QString filePathName)
{
    tempfileList.append(filePathName);
}

void fileAppender::run()
{
    int totalFiles=tempfileList.count();
    int now=0;
    qint64 bufferSize=4096;
    qDebug()<<savingLocation;
    QFile finalFile(QDir::fromNativeSeparators(savingLocation));
    if(finalFile.exists())  {finalFile.remove();}
    if(!finalFile.open(QIODevice::Append|QIODevice::WriteOnly)){

        emit appendFailed();
        cleanup();
        return;
    }
    QByteArray buffer(bufferSize,Qt::Uninitialized);
    foreach (const QString tempPath, tempfileList) {
        QFile aFile(tempPath);
        if(!aFile.open(QIODevice::ReadOnly)){
            emit appendFailed();
            cleanup();
            return;
        }
        qint64 bytesRead=0;
        while((bytesRead=aFile.read(buffer.data(),bufferSize))>0){
            finalFile.write(buffer.constData(),bytesRead);

        }
        now++;
        emit appendProgress(now,totalFiles);
        aFile.close();
    }
    finalFile.close();
    cleanup();
    emit appendSucceed();

}

void fileAppender::cleanup()
{


    QDir pathRemove=QFileInfo(QDir::toNativeSeparators(tempfileList[0])).absoluteDir();
    if(pathRemove.removeRecursively()){
        qDebug()<<"Succeed";
    }else{
        qDebug()<<"Failed";
    };

}


