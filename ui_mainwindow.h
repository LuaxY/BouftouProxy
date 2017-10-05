/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionConsole;
    QWidget *centralWidget;
    QGroupBox *dofusGroup;
    QPushButton *dofusAppPathBrowserButton;
    QLineEdit *dofusAppPathLineEdit;
    QPushButton *dofusStartButton;
    QLabel *dofusStatus;
    QGroupBox *byteCodeGroup;
    QPushButton *byteCodePathBrowserButton;
    QLineEdit *byteCodePathLineEdit;
    QPushButton *byteCodeSendButton;
    QLabel *byteCodeStatus;
    QGroupBox *proxyGroup;
    QLineEdit *proxyAuthPortLineEdit;
    QLineEdit *proxyGamePortLineEdit;
    QLabel *proxyAuthPortLabel;
    QLabel *proxyGamePortLabel;
    QCheckBox *proxyHexdumpCheckBox;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(501, 225);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionConsole = new QAction(MainWindow);
        actionConsole->setObjectName(QStringLiteral("actionConsole"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dofusGroup = new QGroupBox(centralWidget);
        dofusGroup->setObjectName(QStringLiteral("dofusGroup"));
        dofusGroup->setGeometry(QRect(10, 10, 351, 81));
        dofusAppPathBrowserButton = new QPushButton(dofusGroup);
        dofusAppPathBrowserButton->setObjectName(QStringLiteral("dofusAppPathBrowserButton"));
        dofusAppPathBrowserButton->setGeometry(QRect(300, 20, 41, 23));
        dofusAppPathLineEdit = new QLineEdit(dofusGroup);
        dofusAppPathLineEdit->setObjectName(QStringLiteral("dofusAppPathLineEdit"));
        dofusAppPathLineEdit->setGeometry(QRect(10, 21, 281, 21));
        dofusStartButton = new QPushButton(dofusGroup);
        dofusStartButton->setObjectName(QStringLiteral("dofusStartButton"));
        dofusStartButton->setGeometry(QRect(10, 50, 75, 23));
        dofusStatus = new QLabel(dofusGroup);
        dofusStatus->setObjectName(QStringLiteral("dofusStatus"));
        dofusStatus->setGeometry(QRect(100, 50, 241, 20));
        dofusStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        byteCodeGroup = new QGroupBox(centralWidget);
        byteCodeGroup->setObjectName(QStringLiteral("byteCodeGroup"));
        byteCodeGroup->setGeometry(QRect(10, 100, 351, 81));
        byteCodePathBrowserButton = new QPushButton(byteCodeGroup);
        byteCodePathBrowserButton->setObjectName(QStringLiteral("byteCodePathBrowserButton"));
        byteCodePathBrowserButton->setGeometry(QRect(300, 20, 41, 23));
        byteCodePathLineEdit = new QLineEdit(byteCodeGroup);
        byteCodePathLineEdit->setObjectName(QStringLiteral("byteCodePathLineEdit"));
        byteCodePathLineEdit->setGeometry(QRect(10, 21, 281, 21));
        byteCodeSendButton = new QPushButton(byteCodeGroup);
        byteCodeSendButton->setObjectName(QStringLiteral("byteCodeSendButton"));
        byteCodeSendButton->setGeometry(QRect(10, 50, 75, 23));
        byteCodeStatus = new QLabel(byteCodeGroup);
        byteCodeStatus->setObjectName(QStringLiteral("byteCodeStatus"));
        byteCodeStatus->setGeometry(QRect(100, 50, 241, 20));
        byteCodeStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        proxyGroup = new QGroupBox(centralWidget);
        proxyGroup->setObjectName(QStringLiteral("proxyGroup"));
        proxyGroup->setGeometry(QRect(370, 10, 121, 171));
        proxyAuthPortLineEdit = new QLineEdit(proxyGroup);
        proxyAuthPortLineEdit->setObjectName(QStringLiteral("proxyAuthPortLineEdit"));
        proxyAuthPortLineEdit->setGeometry(QRect(70, 20, 41, 20));
        proxyAuthPortLineEdit->setAlignment(Qt::AlignCenter);
        proxyGamePortLineEdit = new QLineEdit(proxyGroup);
        proxyGamePortLineEdit->setObjectName(QStringLiteral("proxyGamePortLineEdit"));
        proxyGamePortLineEdit->setGeometry(QRect(70, 50, 41, 20));
        proxyGamePortLineEdit->setAlignment(Qt::AlignCenter);
        proxyAuthPortLabel = new QLabel(proxyGroup);
        proxyAuthPortLabel->setObjectName(QStringLiteral("proxyAuthPortLabel"));
        proxyAuthPortLabel->setGeometry(QRect(10, 20, 61, 16));
        proxyGamePortLabel = new QLabel(proxyGroup);
        proxyGamePortLabel->setObjectName(QStringLiteral("proxyGamePortLabel"));
        proxyGamePortLabel->setGeometry(QRect(10, 50, 61, 16));
        proxyHexdumpCheckBox = new QCheckBox(proxyGroup);
        proxyHexdumpCheckBox->setObjectName(QStringLiteral("proxyHexdumpCheckBox"));
        proxyHexdumpCheckBox->setGeometry(QRect(10, 150, 70, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 501, 21));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionConsole);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Control", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quitter", Q_NULLPTR));
        actionConsole->setText(QApplication::translate("MainWindow", "Console", Q_NULLPTR));
        dofusGroup->setTitle(QApplication::translate("MainWindow", "Client", Q_NULLPTR));
        dofusAppPathBrowserButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        dofusStartButton->setText(QApplication::translate("MainWindow", "Start Dofus", Q_NULLPTR));
        dofusStatus->setText(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        byteCodeGroup->setTitle(QApplication::translate("MainWindow", "Byte Code", Q_NULLPTR));
        byteCodePathBrowserButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        byteCodeSendButton->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        byteCodeStatus->setText(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        proxyGroup->setTitle(QApplication::translate("MainWindow", "Proxy", Q_NULLPTR));
        proxyAuthPortLineEdit->setText(QString());
        proxyGamePortLineEdit->setText(QString());
        proxyAuthPortLabel->setText(QApplication::translate("MainWindow", "Auth port :", Q_NULLPTR));
        proxyGamePortLabel->setText(QApplication::translate("MainWindow", "Game port :", Q_NULLPTR));
        proxyHexdumpCheckBox->setText(QApplication::translate("MainWindow", "Hexdump", Q_NULLPTR));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        statusBar->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
