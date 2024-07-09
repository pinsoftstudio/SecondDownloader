#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H

#include <QWidget>
#include "libdownload.h"
namespace Ui {
class DownloadWindow;
}

class LIBDOWNLOAD_EXPORT DownloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadWindow(QWidget *parent = nullptr);
    ~DownloadWindow();


private:
    Ui::DownloadWindow *ui;
    LibDownload *downloader;
signals:
    void  downloadThreadExist(DownloadWindow *download);
private slots:
    void  ondownloadThreadExist(DownloadWindow *download);


};

#endif // DOWNLOADWINDOW_H