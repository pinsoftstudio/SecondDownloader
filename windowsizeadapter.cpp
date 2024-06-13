#include "windowsizeadapter.h"
#include "QDesktopWidget"
WindowSizeAdapter::WindowSizeAdapter(QObject *parent)
    : QObject{parent}
{

}

void WindowSizeAdapter::setWindow(QWidget *w)
{
    window=w;

}

void WindowSizeAdapter::addWidget(QWidget *widget)
{
    widgets.append(widget);
}




bool WindowSizeAdapter::adaptAll()
{

    if(window!=nullptr && widgets.count()!=0 ){
        QDesktopWidget desktop;


        qint64 height=desktop.height()*0.68;
        qint64 width=height*1.5;
        qint16 x=(desktop.width()-width)/2;
        qint16 y=(desktop.height()-height)/2;

        //窗口长宽缩放以及窗口居中；
        long double scaling=0.0000000000;
        scaling=height/window->geometry().height();
        window->setGeometry(x,y,width,height);
        foreach(QWidget *w,widgets)
        {
            qint64 orignX=w->geometry().x();
            qint64 orignY=w->geometry().y();
            qint64 newX=orignX*scaling;
            qint64 newY=orignY*scaling;
            w->move(newX,newY);
            qint64 orignWidth=w->geometry().width();
            qint64 orignHeight=w->geometry().height();
            qint64 newWidth=orignWidth*scaling;
            qint64 newHeight=orignHeight*scaling;
            w->resize(QSize(newWidth,newHeight));
        }
        //控件大小缩放以及控件位置调整
        return 1;   
    }
    else{
        return 0;
    }
}
