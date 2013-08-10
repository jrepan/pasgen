#include "main.h"
#include <QClipboard>
#include <QQmlContext>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

const int password_length = 30;

Hash::Hash(QQmlContext *c):
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

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;
    Hash hash(viewer.rootContext());

    viewer.rootContext()->setContextProperty("hash", &hash);
    viewer.setMainQmlFile(QStringLiteral("qrc:/qml/pasgen/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
