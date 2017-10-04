/********************************************************************************
** Form generated from reading UI file 'console.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLE_H
#define UI_CONSOLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_console
{
public:
    QTextEdit *consoleOuput;

    void setupUi(QWidget *console)
    {
        if (console->objectName().isEmpty())
            console->setObjectName(QStringLiteral("console"));
        console->resize(550, 280);
        consoleOuput = new QTextEdit(console);
        consoleOuput->setObjectName(QStringLiteral("consoleOuput"));
        consoleOuput->setGeometry(QRect(0, 0, 550, 280));
        consoleOuput->setStyleSheet(QLatin1String("background-color: black;\n"
"color: white;"));
        consoleOuput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        consoleOuput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        retranslateUi(console);

        QMetaObject::connectSlotsByName(console);
    } // setupUi

    void retranslateUi(QWidget *console)
    {
        console->setWindowTitle(QApplication::translate("console", "Console", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class console: public Ui_console {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLE_H
