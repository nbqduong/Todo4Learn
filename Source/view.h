#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QString>

class view : public QObject
{
    Q_OBJECT
private:
    QString user_name;
    QString tempt_pass;
public:
    explicit view(QObject *parent = nullptr);

public slots:
    void start();
    void getUserName(QString str);
    void getPassWord(QString str);
    QString emitUserName();

signals:
};

#endif // VIEW_H
