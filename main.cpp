#include "forms/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("BotDetector");
    a.setApplicationDisplayName("BotDetector");
    a.setApplicationVersion("0.0.1");

    MainWindow w;
    w.show();

    return a.exec();
}
