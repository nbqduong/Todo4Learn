#ifndef APPSETING_H
#define APPSETING_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>
#include <QVariant>
#include <QMap>
#include <QMapIterator>

class appSeting : public QObject
{
    Q_OBJECT

    QSettings appAttribute;

public:
    explicit appSeting(QString organizationName, QString appName );
    void saveSettings(QString group, QMap<QString, QVariant> map);
    int getSettings(QString group, QString name);

signals:
};



#endif // APPSETING_H
