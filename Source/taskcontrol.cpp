#include "taskcontrol.h"
#define TDEBUG 0
taskInterface::taskInterface(QObject *parent)
    : QObject{parent}, schema("voidrealms"), task("task")
{}

bool taskInterface::createTask(QString task)
{
#ifdef TDEBUG
    qInfo() << "Inserting task";
#endif
    QSqlQuery query;

    QString cmd = QString(
                      "INSERT INTO `%1`.`%2` (`task_name`,`status`)VALUES(:var1,:var2);")
                      .arg(this->schema).arg(this->task);
    query.prepare(cmd);
    query.bindValue(":var1", task);
    query.bindValue(":var2", "undone");

    bool ok = exec(query);
#ifdef TDEBUG
    if(ok)
    {

        qInfo() << "Task created " ;
    }
    else
    {
        qInfo() << "Error: Task not created ";
    }
#endif
    return ok;

}

void taskInterface::settingAttributes(QString schema, QString task)
{
    this->schema = schema;
    this->task = task;
}

bool taskInterface::exec(QSqlQuery &query)
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

bool taskInterface::markDone(int id)
{
    // UPDATE `voidrealms`.`task` SET `status` = 'done' WHERE (`task_id` = '4');
#ifdef TDEBUG
    qInfo() << "Mark task done";
#endif
    QSqlQuery query;

    QString cmd = QString(
                      "UPDATE `%1`.`%2` SET `status` = :var1 WHERE (`task_id` = :var2);")
                      .arg(this->schema).arg(this->task);
    query.prepare(cmd);
    query.bindValue(":var1", "done");
    query.bindValue(":var2", id);

    bool ok = exec(query);
#ifdef TDEBUG
    if(ok)
    {

        qInfo() << "Successed!!!" ;
    }
    else
    {
        qInfo() << "Error: EXECUTE ERROR";
    }
#endif
    return ok;
}

taskAssignment::taskAssignment(QObject *parent)
    : QObject{parent}, schema("voidrealms"), task("taskmm"), table(schema+"."+task)
{

}

bool taskAssignment::exec(QSqlQuery &query)
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

QVector<taskInfoStr> taskAssignment::getTasks(int id)
{
#if TDEBUG
    qInfo() << "View table schedule: ";
#endif
    qInfo() << table;
    QString usr_table = schema+".user",
            task_table = schema+".task";
    QVector<taskInfoStr> tasks;

    QSqlQuery query;
    QString cmd = QString("SELECT * FROM %1 "
                        "INNER JOIN %2 "
                        "ON %1.usr_id = 1 "
                        "AND %2.task_id = %1.task_id;")
                                  .arg(this->table).arg(task_table);
    query.prepare(cmd);
    query.bindValue(":var1",id);

    if(exec(query))
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            taskInfoStr tmp;
            tmp.id = record.value(3).toInt();
            tmp.name = record.value(4).toString();
            tmp.status = record.value(5).toString();
            tasks << std::move(tmp);
#if TDEBUG
            qInfo() << "Loaded id: " << tmp.id << " Name: " << tmp.name << "Status: " << tmp.status;
#endif
        }
        return tasks;
    }
    else
    {
        qInfo() << "Fail command: " << cmd;
    }
}

bool taskAssignment::addTask(int task_id, int usr_id)
{

}
