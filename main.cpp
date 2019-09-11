#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScopedPointer>
#include "fluxhub.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setApplicationName("SimplePromise");
    app.setOrganizationName("Demo");

    qmlRegisterUncreatableType<SimplePromise>("SimplePromise", 1, 0, "SimplePromise", "cannot create directly!");

    QQmlApplicationEngine engine;

    QScopedPointer<FluxHub> hub(new FluxHub);
    engine.rootContext()->setContextProperty("$hub", hub.data());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
