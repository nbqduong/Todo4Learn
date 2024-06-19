#ifndef APPSETING_H
#define APPSETING_H

#include <QObject>

class appSeting : public QObject
{
    Q_OBJECT
public:
    explicit appSeting(QObject *parent = nullptr);

signals:
};

#endif // APPSETING_H
