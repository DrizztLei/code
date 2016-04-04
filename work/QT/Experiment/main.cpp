#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
using std :: cout;
using std :: cin;
using std :: endl;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    cout << "Hello qt" << endl;
    return app.exec();
    cout << "Debuging . " << endl;
    cout << "Againg ." << endl;
    return 0;
}
