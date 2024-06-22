#include "view.h"
#include <QDebug>

view::view(QObject *parent)
    : QObject{parent}, user_name("default")
{}

void view::start()
{
    qInfo() << "test";
}

void view::getUserName(QString str)
{
    user_name = str;
}

void view::getPassWord(QString str)
{
    tempt_pass = str;
}

QString view::emitUserName()
{
    return user_name;
}
