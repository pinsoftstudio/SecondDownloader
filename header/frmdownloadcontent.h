#ifndef FRMDOWNLOADCONTENT_H
#define FRMDOWNLOADCONTENT_H

#include <QWidget>


namespace Ui {
class frmDownloadContent;
}

class frmDownloadContent : public QWidget
{
    Q_OBJECT

public:
    explicit frmDownloadContent(QWidget *parent = nullptr);
    ~frmDownloadContent();

private:
    Ui::frmDownloadContent *ui;
};

#endif // FRMDOWNLOADCONTENT_H
