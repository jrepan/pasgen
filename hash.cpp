#include "hash.h"
#include <QClipboard>
#include <QGuiApplication>
#include <QQmlContext>
#include <QStringList>
#include "common.h"

Hash::Hash(QQmlContext *c, QObject *parent) :
    QObject(parent),
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

	// Generate the password
	QString result = generate(password, page, settings);

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
