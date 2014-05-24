#ifndef HASH_H
#define HASH_H

#include <QObject>
#include <QCryptographicHash>
#include <QSettings>

class QQmlContext;

class Hash : public QObject
{
    Q_OBJECT
public:
    explicit Hash(QQmlContext *c, QObject *parent = 0);

    Q_INVOKABLE QString Do(QString password, QString page, bool addToList);
    Q_INVOKABLE void Remove(QString page);

private:
    QCryptographicHash hash;
    QSettings settings;
    QQmlContext *context;
};

#endif // HASH_H
