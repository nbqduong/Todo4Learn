#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "view.h"
#include "savelogin.h"
#include "databasecontrol.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //Register a type in QML
    qmlRegisterType<view>("com.company.view",1,0,"View");

    const QUrl url(QStringLiteral("qrc:/Source/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    databaseControl db;
    return app.exec();
}
