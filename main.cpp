#include "main.h"
#include <QClipboard>
#include <QQmlContext>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

Hash::Hash():
    hash(QCryptographicHash::Sha3_224)
{
}

QString Hash::Do(QString password, QString page)
{
    hash.reset();
    hash.addData(password.toUtf8());
    hash.addData(page.toUtf8());
    QString result = hash.result().toHex();
    qApp->clipboard()->setText(result);
    return result;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    Hash hash;

    viewer.setMainQmlFile(QStringLiteral("qrc:/qml/pasgen/main.qml"));
    viewer.showExpanded();
    viewer.rootContext()->setContextProperty("hash", &hash);

    return app.exec();
}
