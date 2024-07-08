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
    void setDark(bool isDark);
private:
    Ui::frmDownloadContent *ui;
        bool Dark=false;
};

#endif // FRMDOWNLOADCONTENT_H
