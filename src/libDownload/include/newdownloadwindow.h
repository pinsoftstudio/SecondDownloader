#ifndef NEWDOWNLOADWINDOW_H
#define NEWDOWNLOADWINDOW_H

#include <QWidget>
#include <QStringList>
// #include <include/downloadmessagewindow.h>
#include "downloadmessagewindow.h"
#include "libDownload_global.h"
namespace Ui {
class NewDownloadWindow;
}

class LIBDOWNLOAD_EXPORT NewDownloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewDownloadWindow(QWidget *parent = nullptr);
    ~NewDownloadWindow();


private:
    Ui::NewDownloadWindow *ui;
    DownloadMessageWindow   *downloadmessagewindow;
    QStringList getNoUseScheme();

private slots:


     void on_btnStart_clicked();
};

#endif // NEWDOWNLOADWINDOW_H
