#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class login : public QObject
{
    Q_OBJECT
public:
    explicit login(QObject *parent = nullptr);
    ~login();

    int id;
    QString password;
    QString name;
    QString date;

    void openDataBase(QString DataBase, QString HostName, QString UserName, QString Password);
    void closeDataBase();
    void begin();
    void commit();
    void rollback();
    bool open();
    void create();
    void load(int value);
    void save();
    void remove();
    bool insert();

signals:

public slots:

private:

    bool update();
    bool exec(QSqlQuery &query);
};

#endif // LOGIN_H
