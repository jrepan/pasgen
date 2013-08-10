#ifndef MAIN_H
#define MAIN_H

#include <QCryptographicHash>
#include <QObject>
#include <QSettings>

class QQmlContext;

class Hash: public QObject
{
    Q_OBJECT
public:
    Hash(QQmlContext *c);
    Q_INVOKABLE QString Do(QString password, QString page);
    Q_INVOKABLE void Remove(QString page);
private:
    QCryptographicHash hash;
    QSettings settings;
    QQmlContext *context;
};

#endif // MAIN_H
