#include "console.h"
#include "ui_console.h"

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::console)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);
    setFixedSize(geometry().width(), geometry().height());
    move(0, 0);

    ui->consoleOuput->setReadOnly(true);
}

Console::~Console()
{
    delete ui;
}
