#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "calculatormodel.h"
#include "calculatorcontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    calculatormodel* model = new calculatormodel(0, 0, 0);
    calculatorcontroller* controller = new calculatorcontroller(model);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("model", model);
    engine.rootContext()->setContextProperty("controller", controller);
    engine.loadFromModule("temp_calculator", "Main");

    return app.exec();
}
