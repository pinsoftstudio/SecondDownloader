#ifndef STACKEDWIDGETADAPTER_H
#define STACKEDWIDGETADAPTER_H


#include <QObject>
#include <QStackedWidget>
class StackedWidgetAdapter : public QObject
{
    Q_OBJECT
public:
    explicit StackedWidgetAdapter(QObject *parent = nullptr);
    QStackedWidget *stackedWidget;
    void setStackedWidget(QStackedWidget *swidget);
    bool adapt();


signals:
};

#endif // STACKEDWIDGETADAPTER_H
