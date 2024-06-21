#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <appseting.h>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    appSeting a("a","b");
    QMap<QString, QVariant> map;
    map.insert("plenty", 100);
    map.insert("plenty1", 1100);
    a.saveSettings("a", map);
    qInfo() << a.getSettings("a","plenty");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/todoApp/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
