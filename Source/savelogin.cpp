#include "savelogin.h"

login::login(QObject *parent) : QObject(parent)
{
    QString DataBase = "QMYSQL",  HostName = "localhost",  UserName = "qt6ca",  Password = "qt6ca-Password";
    openDataBase( DataBase,  HostName,  UserName,  Password);

    load(1);

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

void login::load(int value)
{
    qInfo() << "Loading record: " << value;

    QSqlQuery query;
    QString cmd = "SELECT * FROM voidrealms.user WHERE usr_id = :id;";
    query.prepare(cmd);
    query.bindValue(":id",value);

    bool ok = exec(query);

    if(ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            id = record.value(0).toInt();
            password = record.value(2).toString();
            name = record.value(1).toString();

            qInfo() << "Loaded " << id << " pass " << password << " name " << name;

            return;
        }
    }
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
