#ifndef PROPERTYDIALOG_H
#define PROPERTYDIALOG_H

#include <QDialog>

namespace Ui {
class PropertyDialog;
}

class PropertyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertyDialog(QString url, QString location, QString state, QString size, QWidget *parent = nullptr);
    ~PropertyDialog();

private slots:
    void on_btnOpen_clicked();

    void on_btnCopy_clicked();

private:
    Ui::PropertyDialog *ui;
    QString State;
    QString Url;
    QString Location;
    QString Size;
    QString  ProgetFileTypeByExtension(const QString &extension);

};

#endif // PROPERTYDIALOG_H
