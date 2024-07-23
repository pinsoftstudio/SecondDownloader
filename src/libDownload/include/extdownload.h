#ifndef EXTDOWNLOAD_H
#define EXTDOWNLOAD_H

#include <QDialog>

namespace Ui {
class extDownload;
}

class extDownload : public QDialog
{
    Q_OBJECT

public:
    explicit extDownload(QWidget *parent = nullptr);
    ~extDownload();

private:
    Ui::extDownload *ui;
};

#endif // EXTDOWNLOAD_H
