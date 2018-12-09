#include "hash.h"
#include <QClipboard>
#include <QDataStream>
#include <QGuiApplication>
#include <QQmlContext>
#include <QTextStream>
#include <QStringList>

const int default_password_length = 30;

Hash::Hash(QQmlContext *c, QObject *parent) :
    QObject(parent),
    hash(QCryptographicHash::Sha3_224),
    settings("pasgen"),
    context(c)
{
    context->setContextProperty("myModel", settings.value("pages").toStringList());
}

QString Hash::Do(QString password, QString page, bool isCheck)
{
    // Add page to the list
    QStringList pages = settings.value("pages").toStringList();
    if (!isCheck && !page.isEmpty())
    {
        if (!pages.contains(page))
            pages.append(page);

        pages.move(pages.indexOf(page), 0);
        settings.setValue("pages", pages);
        context->setContextProperty("myModel", pages);
    }

    // Get password length
    int password_length = default_password_length;
    if (page.startsWith("len") || page.startsWith("pin"))
    {
        QTextStream stream(&page);
        stream.seek(3); // 3 = strlen("len" or "pin")
        stream >> password_length;
        if (stream.status() != QTextStream::Ok)
            password_length = default_password_length;
    }

    // Generate password
    hash.reset();
    hash.addData(password.toUtf8());
    hash.addData(page.toUtf8());
    QByteArray raw = hash.result();
    QString result;
    if (page.startsWith("pin"))
    {
        unsigned int raw_nr;
        QDataStream(raw) >> raw_nr;
        result = QString("%1").arg(raw_nr).right(password_length);
    }
    else
        result = raw.toBase64(QByteArray::OmitTrailingEquals).replace('+', "").replace('/', "").left(password_length);

    // Copy to clipboard
    if (!isCheck)
    {
        qApp->clipboard()->setText(result, QClipboard::Clipboard);
        qApp->clipboard()->setText(result, QClipboard::Selection);
    }

    // Return result
    return result;
}

void Hash::Remove(QString page)
{
    QStringList pages = settings.value("pages").toStringList();
    pages.removeAll(page);
    settings.setValue("pages", pages);
    context->setContextProperty("myModel", pages);
}
