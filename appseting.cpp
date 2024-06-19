#include "appseting.h"

appSeting::appSeting(QString organizationName, QString appName )
 :appAttribute(organizationName, appName)
{
    // appAttribute("organizationName","appName");
}

void appSeting::saveSettings(QString group,QMap<QString, QVariant> map)
{

    QMapIterator<QString, QVariant> i(map);
    appAttribute.beginGroup(group);

    while (i.hasNext()) {
        i.next();
        qInfo() << qPrintable(i.key()) << ": " << i.value() ;
        appAttribute.setValue(i.key(),i.value());
    }
    appAttribute.endGroup();
}

int appSeting::getSettings(QString group, QString name)
{
    appAttribute.beginGroup(group);

    if(!appAttribute.contains(name))
    {
        qWarning() << "Does not contain " << name << " in " << group;
        appAttribute.endGroup();
        return 0;
    }

    bool ok;
    int value = appAttribute.value(name).toInt(&ok);
    appAttribute.endGroup();

    if(!ok)
    {
        qWarning() << "Could not convert to int";
        return 0;
    }

    return value;
}
