#ifndef DIALOGDOWNLOADED_H
#define DIALOGDOWNLOADED_H

#include <QDialog>
#include <QCloseEvent>
namespace Ui {
class DialogDownloaded;
}

class DialogDownloaded : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDownloaded(QWidget *parent = nullptr);
    ~DialogDownloaded();
    void setSavedLocation(QString location);

private:
    Ui::DialogDownloaded *ui;

    QString fileLocation;
    QString folderLocation;


protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private slots:
    void on_btnOpenFolder_clicked();
    void on_btnOpen_clicked();
};

#endif // DIALOGDOWNLOADED_H
