#include "console.h"
#include "ui_console.h"
#include <QDesktopWidget>

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::console)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);
    move(0, 0);

    QRect windowRect = QApplication::desktop()->screenGeometry();
    int height = windowRect.height() - 75;
    setFixedSize(geometry().width(), height);

    QRect consoleRect = ui->consoleOuput->geometry();
    consoleRect.setHeight(height);
    ui->consoleOuput->setGeometry(consoleRect);
    ui->consoleOuput->setReadOnly(true);
}

Console::~Console()
{
    delete ui;
}

void Console::write(QString log)
{
    ui->consoleOuput->append(log);
}
