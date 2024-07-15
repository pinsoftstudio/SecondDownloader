#ifndef FRMDOWNLOADCONTENT_H
#define FRMDOWNLOADCONTENT_H

#include <QWidget>
#include <QEvent>
#include <string.h>
#include <downloadwindow.h>
#include "QList"
#include "QSharedMemory"
#include "QStringList"
namespace Ui {
class frmDownloadContent;
}

class frmDownloadContent : public QWidget
{
    Q_OBJECT

public:
    explicit frmDownloadContent(QWidget *parent);
    ~frmDownloadContent();
    void setDark(bool isDark);
    enum treeColNum{fileName=0,filesize,downloadSpeed,state,location};
    enum displayMode{all=0,downloading,succeed,faild};
    void setDisplayMode(frmDownloadContent::displayMode mode);

private:
    Ui::frmDownloadContent *ui;
    bool Dark=false;
    QList<DownloadWindow*> downloaders;
    QTimer *tmGetNewShareName;
    QTimer *tmUpdateShare;
    // DownloadWindow *DownloadWindow;
    QSharedMemory *sdGetKey;
    QStringList keyGetted;
    QSharedMemory *innerMemory;
    QSharedMemory *updateShare;
    QTimer *tmRefreashDat;
    void iniTree();
private slots:
    void onExistSThread(DownloadWindow* downloadwindow);
    void on_btnSelect_clicked(bool checked);
    void onCustomContextMenuRequested(const QPoint &pos);
    void onTMGetNewShareName();
    void onUpdateShare();
    void addTreeItems(QString memoryShareName);
    void getShareName();
    void refreashDatFile();



    void on_btnAll_clicked();
    void on_btnDownloading_clicked();
    void on_btnSucceed_clicked();
    void on_btnFailed_clicked();
};

#endif // FRMDOWNLOADCONTENT_H
