#ifndef PARAMETER_H
#define PARAMETER_H
#include <QString>
namespace parameter {
    struct userInfoStr
    {
        int id;
        QString name;
        QString password;
        QString created_day;
    } ;

    struct databaseStr
    {
        QString DataBase;
        QString HostName;
        QString UserName;
        QString Password;
        databaseStr() :DataBase("QMYSQL"), HostName("localhost"),UserName("qt6ca"), Password("qt6ca-Password")
        {
        }
    } ;

    struct taskInfoStr
    {
        int id;
        QString name;
        QString status;
    } ;
}



#endif // PARAMETER_H
