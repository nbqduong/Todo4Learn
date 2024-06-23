#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>

class processor : public QObject
{
    Q_OBJECT
public:
    explicit processor(QObject *parent = nullptr);

signals:
};

#endif // PROCESSOR_H
