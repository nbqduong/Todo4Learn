#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

#include <QObject>
#include "savelogin.h"
#include "Parameter.h"
#include "taskcontrol.h"

class databaseControl : public QObject
{
    Q_OBJECT
    login login_usr;
public:
    explicit databaseControl(QObject *parent = nullptr);
    void openDataBase(QString DataBase, QString HostName, QString UserName, QString Password);
    void closeDataBase();
    bool checkUserInformation(QString name, QString pass);
signals:
};

#endif // DATABASECONTROL_H
