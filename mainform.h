#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

namespace Ui {
class mainform;
}

class mainform : public QWidget
{
    Q_OBJECT

public:
    explicit mainform(QWidget *parent = nullptr);
    ~mainform();

private:
    Ui::mainform *ui;
};

#endif // MAINFORM_H
