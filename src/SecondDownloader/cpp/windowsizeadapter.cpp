#include "header/windowsizeadapter.h"
#include "QScreen"
#include "qdebug.h"
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

QRect WindowSizeAdapter::getPaintRect()
{
    QRect reRect;
    reRect.setX(0);
    reRect.setY(0);
    reRect.setHeight(window->height());
    reRect.setWidth(70*windowScaling);
    return reRect;
}




bool WindowSizeAdapter::adaptAll()
{

    if(window!=nullptr && widgets.count()!=0 ){
        QScreen desktop;


        qint64 height=desktop.height()*0.68;
        qint64 width=height*1.5;
        qint16 y=(desktop.height()-height)/2;
        qint16 x=(desktop.width()-width)/2;
        qDebug()<<"desktopheight"<<desktop.height();
        qDebug()<<"desktopwidth"<<desktop.width();
        qDebug()<<"height"<<height;
        qDebug()<<"width"<<width;
        //窗口长宽缩放以及窗口居中；

        double scaling=(height+0.0001)/window->geometry().height();
        windowScaling=scaling;
        window->setGeometry(x,y,width,height);
        foreach(QWidget *w,widgets)
        {
            qint64 orignX=w->geometry().x();
            qint64 orignY=w->geometry().y();
            qint64 newX=orignX*scaling;
            qint64 newY=orignY*scaling;
             w->move(newX,newY);
            qDebug()<<w->objectName();
             qDebug()<<"x"<<newX;
            qDebug()<<"y"<<newY;
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
