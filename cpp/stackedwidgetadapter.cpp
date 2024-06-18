#include "header/stackedwidgetadapter.h"
#include <QDebug>
StackedWidgetAdapter::StackedWidgetAdapter(QObject *parent)
    : QObject{parent}
{
    setParent(parent);
}

void StackedWidgetAdapter::setStackedWidget(QStackedWidget *swidget)
{
    stackedWidget=swidget;
}


bool StackedWidgetAdapter::adapt()
{
    if (stackedWidget!=nullptr){
        qint64 stackedWidgetHeight=stackedWidget->height();
        qint64 stackedWidgetWidth=stackedWidget->width();

        const qint16 count=stackedWidget->count();
        for(int i=0;i<count;i++){
            qint64 widgetHeight=stackedWidget->widget(i)->height();
            qint64 widgetWidth=stackedWidget->widget(i)->width();
            //获取子窗口的大小，以便计算缩放比例来应用于子控件
            double scalingX=0.0000;
            double scalingY=0.0000;
            scalingX=stackedWidgetWidth/widgetWidth;
            scalingY=stackedWidgetHeight/widgetHeight;
            stackedWidget->widget(i)->resize(stackedWidgetWidth,stackedWidgetHeight);
            //调整StackedWidget中子窗口的大小
            for(QWidget *child:stackedWidget->widget(i)->findChildren<QWidget*>()){
                //遍历子窗口所有控件
                qint64 orignX=child->geometry().x();
                qint64 orignY=child->geometry().y();
                // qDebug()<<"orignX"<<orignX<<"/n";
                qint64 newX=orignX*scalingX;
                qint64 newY=orignY*scalingY;
                 // qDebug()<<"newX"<<newX<<"/n";
                qint64 orignWidth=child->width();
                qint64 orignHeight=child->height();
                qint64 newWidth=orignWidth*scalingX;
                qint64 newHeight=orignHeight*scalingY;
                child->move(newX,newY);
                child->resize(newWidth,newHeight);

            }

        }
        return 1;
    }else {
        return 0;
    }

}
