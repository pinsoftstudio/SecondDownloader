#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;

protected:
    // 声明 closeEvent 函数
    // void closeEvent(QCloseEvent *event) override;

};

#endif // MAINWINDOW_H
