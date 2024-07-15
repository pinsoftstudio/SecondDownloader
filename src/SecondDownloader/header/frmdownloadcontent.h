#ifndef FRMDOWNLOADCONTENT_H
#define FRMDOWNLOADCONTENT_H

#include <QWidget>
#include <QEvent>
#include <string.h>
#include <downloadwindow.h>
#include "QList"
#include "QSharedMemory"

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

private:
    Ui::frmDownloadContent *ui;
    bool Dark=false;
    QList<DownloadWindow*> downloaders;
    QTimer *tmGetNewShareName;
    // DownloadWindow *DownloadWindow;
private slots:
    void onExistSThread(DownloadWindow* downloadwindow);
    void on_btnSelect_clicked(bool checked);
    void onCustomContextMenuRequested(const QPoint &pos);
    void addTreeItems(QString memoryShareName);
    void getShareName();

};

#endif // FRMDOWNLOADCONTENT_H
