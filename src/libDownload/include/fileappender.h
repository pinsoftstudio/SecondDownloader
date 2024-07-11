#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H

#include <QObject>
#include <QThread>
class fileAppender : public QThread
{
    Q_OBJECT
public:
    explicit fileAppender(QString savinglocation,QList<QString> tempFileNames,Object *parent = nullptr);

signals:
};

#endif // FILEAPPENDER_H
