#include "databasecontrol.h"

databaseControl::databaseControl(QObject *parent)
    : QObject{parent}
{
    databaseStr default_db;
    openDataBase( default_db.DataBase,  default_db.HostName,  default_db.UserName,  default_db.Password);
    taskAssignment t;
    QVector<taskInfoStr> tasks = t.getTasks(1);
    for (int i = 0; i < tasks.size(); ++i)
    {
        qInfo() << "Loaded id: " << tasks[i].id << " Name: " << tasks[i].name << "Status: " << tasks[i].status;
    }

}

void databaseControl::openDataBase(QString DataBase, QString HostName, QString UserName, QString Password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DataBase);

    qInfo() << "Opening Database";
    db.setHostName(HostName);
    db.setUserName(UserName); //Change the username
    db.setPassword(Password); //Change the password

    bool ok = db.open();
    if(ok)
    {
        qInfo() << "Opened database connection!";
        // return true;
    } else
    {
        qInfo() << "Failed to open connection!";
        qInfo() << db.lastError().text();
    }
}

void databaseControl::closeDataBase()
{
    QSqlDatabase::database().close();
}

bool databaseControl::checkUserInformation(QString name, QString pass)
{
    userInfoStr tmpt = login_usr.loadName(name);
#ifdef TDEBUG
    qInfo() << " usr id: " << tmpt.usr_id << " name: " << tmpt.usr_name << " pass: " << tmpt.password;
#endif
    return (name == tmpt.name && pass == tmpt.password);
}
