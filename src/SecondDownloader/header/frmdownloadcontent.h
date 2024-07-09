#ifndef FRMDOWNLOADCONTENT_H
#define FRMDOWNLOADCONTENT_H

#include <QWidget>


#include <downloadwindow.h>
#include "QList"
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
    // DownloadWindow *DownloadWindow;
private slots:
    void onExistSThread(DownloadWindow* downloadwindow);
};

#endif // FRMDOWNLOADCONTENT_H
