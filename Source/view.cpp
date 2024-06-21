#include "view.h"
#include <QDebug>

view::view(QObject *parent)
    : QObject{parent}
{}

void view::start()
{
    qInfo() << "test";
}

void view::get(QString str)
{
    user_name = str;
}

QString view::emitUserName()
{
    return user_name;
}
