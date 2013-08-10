#include "main.h"
#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include "qtquick2applicationviewer.h"
#include "hash.h"

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
