#include "hash.h"
#include <QClipboard>
#include <QGuiApplication>
#include <QQmlContext>
#include <QStringList>

const int password_length = 30;

Hash::Hash(QQmlContext *c, QObject *parent) :
    QObject(parent),
    hash(QCryptographicHash::Sha3_224),
    settings("pasgen"),
    context(c)
{
    context->setContextProperty("myModel", settings.value("pages").toStringList());
}

QString Hash::Do(QString password, QString page)
{
    QStringList pages = settings.value("pages").toStringList();
    if (!page.isEmpty() && !pages.contains(page))
    {
        pages.append(page);
        settings.setValue("pages", pages);
        context->setContextProperty("myModel", pages);
    }

    hash.reset();
    hash.addData(password.toUtf8());
    hash.addData(page.toUtf8());
    QString result = hash.result().toHex().left(password_length);

    qApp->clipboard()->setText(result);
    return result;
}

void Hash::Remove(QString page)
{
    QStringList pages = settings.value("pages").toStringList();
    pages.removeAll(page);
    settings.setValue("pages", pages);
    context->setContextProperty("myModel", pages);
}
