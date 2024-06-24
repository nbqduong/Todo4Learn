#include "savelogin.h"
#define TDEBUG
login::login(QObject *parent) : QObject(parent)
{
    // QString DataBase = "QMYSQL",  HostName = "localhost",  UserName = "qt6ca",  Password = "qt6ca-Password";
    // openDataBase( DataBase,  HostName,  UserName,  Password);

    // load(1);

    // return false;


}

login::~login()
{
    closeDataBase();
}

void login::openDataBase(QString DataBase, QString HostName, QString UserName, QString Password)
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

void login::closeDataBase()
{
    QSqlDatabase::database().close();
}

void login::begin()
{
    QSqlDatabase::database().transaction();
}

void login::commit()
{
    QSqlDatabase::database().commit();
}

void login::rollback()
{
    QSqlDatabase::database().rollback();
}

bool login::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    qInfo() << "isOpen: " << isOpen;
    return isOpen;
}

void login::create()
{
    id = 0;
    password = 0;
    name = "";
}

void login::load(int id)
{
#ifdef TDEBUG
    qInfo() << "Loading id: " << id;
#endif

    QSqlQuery query;
    QString cmd = "SELECT * FROM voidrealms.user WHERE usr_id = :id;";
    query.prepare(cmd);
    query.bindValue(":id",id);

    if(exec(query))
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            id = record.value(0).toInt();
            password = record.value(2).toString();
            name = record.value(1).toString();
#ifdef TDEBUG
            qInfo() << "Loaded id: " << id << " Name: " << name << "Pass: " << password;
#endif
        }
        return;
    }
    else
    {
        qInfo() << "Fail command: " << cmd;
    }
}

userInfoStr login::loadName(QString name)
{
#ifdef TDEBUG
    qInfo() << "Loading name: " << name;
#endif
    userInfoStr local_data;

    QSqlQuery query;
    QString cmd = "SELECT * FROM voidrealms.user WHERE usr_name = :var;";
    query.prepare(cmd);
    query.bindValue(":var",name);

    if(exec(query))
    {

        while (query.next())
        {
            QSqlRecord record = query.record();
            local_data.id = record.value(0).toInt();
            local_data.name = record.value(1).toString();
            local_data.password = record.value(2).toString();
            local_data.created_day = record.value(3).toString();
#ifdef TDEBUG
            qInfo() << "Loaded id: " << local_data.id << " Name: " << local_data.name << "Pass: " << local_data.password;
#endif

        }
    }
    else
    {
        qInfo() << "Fail command: " << cmd;
    }
    return local_data;
}

void login::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM voidrealms.user WHERE usr_id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", id);

    exec(query);
}

bool login::insert()
{
    qInfo() << "Inserting row";
    QSqlQuery query;
    QString cmd = "INSERT INTO `voidrealms`.`user` (`usr_id`,`usr_name`,`password`)VALUES(:id,:name,:age);";
    query.prepare(cmd);
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":age", password);

    bool ok = exec(query);

    if(ok)
    {
        id = query.lastInsertId().toInt();
        qInfo() << "Inserted " << id;
    }
    else
    {
        id = 0;
    }

    return ok;
}

bool login::update()
{
    qInfo() << "Inserting row";
    QSqlQuery query;
    QString cmd = "UPDATE `voidrealms`.`user` SET `usr_id` = :id, `usr_name` = :name, `password` = :age WHERE `usr_id` = :id;";
    query.prepare(cmd);
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":age", password);


    bool ok = exec(query);

    if(ok)
    {
        qInfo() << "Updated " << id;
    }


    return ok;
}

bool login::exec(QSqlQuery &query)
{
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen())
    {
        qInfo() << "The connection is not open!";
        return false;
    }

    qInfo() << "Exec: " << query.executedQuery();
    bool ok =  query.exec();

    if(!ok)
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }

    return ok;
}
