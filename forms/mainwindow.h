#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "console.h"
#include "network/server.h"

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



private slots:
    void checkDofusPath(QString path = "");
    void browseDofusPath();
    void startDofusClient();
    void openConsole();
    void injectDll();
    void sendByteCode();
};

#endif // MAINWINDOW_H
