#ifndef MAIN_H
#define MAIN_H

#include <QCryptographicHash>
#include <QObject>

class Hash: public QObject
{
    Q_OBJECT
public:
    Hash();
    Q_INVOKABLE QString Do(QString password, QString page);
private:
    QCryptographicHash hash;
};

#endif // MAIN_H
