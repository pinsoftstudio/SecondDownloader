#include "windowsizeadapter.h"
#include "QDesktopWidget"
#include "qmessagebox.h"
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

}




bool WindowSizeAdapter::adaptAll()
{
    if(window!=nullptr ){
        // if(window!=nullptr && widgets->count()!=0 ){
        QDesktopWidget desktop;
        // const scaling=0.68;
        // Q_UNUSED(scaling);

        qint64 height=desktop.height()*0.68;
        qint64 width=height*1.5;
        qint16 x=(desktop.width()-width)/2;
        qint16 y=(desktop.height()-height)/2;
        window->setGeometry(x,y,width,height);
        //窗口长宽缩放；
/*
        for (int i=0;widgets->count();i++){
            qint16 orignX=widgets->at(i).geometry().x();
            qint16 orignY=widgets->at(i).geometry().y();
            QWidget *w=widgets->at(i);

        }*/
        return 1;
    }
}

