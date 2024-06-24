#ifndef TASKCONTROL_H
#define TASKCONTROL_H

#include <QObject>
#include <QString>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include "Parameter.h"

using namespace parameter;
class taskInterface : public QObject
{
    Q_OBJECT
    // taskInfoStr &&task;
    QString schema;
    QString task;
public:
    explicit taskInterface(QObject *parent = nullptr);
    bool createTask(QString task);
    void settingAttributes(QString schema, QString task);
    bool exec(QSqlQuery &query);
    bool markDone(int id);
signals:
};

class taskAssignment : public QObject
{
    Q_OBJECT
    // taskInfoStr &&task;
    QString schema;
    QString task;
    QString table;
public:
    explicit taskAssignment(QObject *parent = nullptr);
    bool createTask(QString task);
    void settingAttributes(QString schema, QString task);
    bool exec(QSqlQuery &query);
    bool markDone(int id);
    QVector<taskInfoStr> getTasks(int id);
signals:
};


#endif // TASKCONTROL_H
