
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "window.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    SerialReader serialReader;
    engine.rootContext()->setContextProperty("serialReader", &serialReader);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
