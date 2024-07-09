#ifndef DOWNLOADMESSAGEWINDOW_H
#define DOWNLOADMESSAGEWINDOW_H

#include <QWidget>
#include "downloadwindow.h"

#include "libDownload_global.h"
namespace Ui {
class LIBDOWNLOAD_EXPORT DownloadMessageWindow;
}

class LIBDOWNLOAD_EXPORT DownloadMessageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadMessageWindow(QWidget *parent = nullptr);
    ~DownloadMessageWindow();

private:
    Ui::DownloadMessageWindow *ui;
    DownloadWindow *downloadwindow;
signals:
    void  downloadThreadExist(DownloadWindow *downloadwindow);
private slots:
    void  ondownloadThreadExist(DownloadWindow *downloadwindow);

    void on_btnStart_clicked();
};

#endif // DOWNLOADMESSAGEWINDOW_H
