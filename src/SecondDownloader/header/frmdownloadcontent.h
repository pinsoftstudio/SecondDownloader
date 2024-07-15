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
    enum treeColNum{fileName=0,filesize,downloadSpeed,state};

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
private slots:
    void onExistSThread(DownloadWindow* downloadwindow);
    void on_btnSelect_clicked(bool checked);
    void onCustomContextMenuRequested(const QPoint &pos);
    void onTMGetNewShareName();
    void onUpdateShare();
    void addTreeItems(QString memoryShareName);
    void getShareName();

};

#endif // FRMDOWNLOADCONTENT_H
