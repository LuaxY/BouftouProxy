#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "console.h"
#include "network/server.h"
#include "utils/logger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    qint64 dofusClientPid = 0;
    Console* console;
    Server* server;
    QDir* dataDir;
    Logger* logger;

private slots:
    void checkDofusPath(QString path = "");
    void browseDofusPath();
    void startDofusClient();
    void openConsole();
    void injectDll();
    void enableHexdump(int state);
    void sendByteCode();
};

#endif // MAINWINDOW_H
