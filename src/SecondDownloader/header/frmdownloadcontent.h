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
struct shareDownloadData{
    double  percentFinished=0;
    enum downloadItemState{PREDOWNLOAD,DOWNLOADING,SUCCEED,FAILED};
    std::string URL;
    std::string fileLocation;
};
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
    // DownloadWindow *DownloadWindow;
private slots:
    void onExistSThread(DownloadWindow* downloadwindow);
    void on_btnSelect_clicked(bool checked);
    void onCustomContextMenuRequested(const QPoint &pos);
    void addTreeItems(QString memoryShareName);

};

#endif // FRMDOWNLOADCONTENT_H
