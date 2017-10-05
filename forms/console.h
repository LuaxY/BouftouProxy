#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>

namespace Ui {
class console;
}

class Console : public QWidget
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();

    void write(QString log);

private:
    Ui::console *ui;
};

#endif // CONSOLE_H
