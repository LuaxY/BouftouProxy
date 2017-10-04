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
    QAction *actionQuitter;
    QWidget *centralWidget;
    QGroupBox *dofusGroup;
    QPushButton *dofusAppPathBrowserButton;
    QLineEdit *dofusAppPathLineEdit;
    QPushButton *dofusStartButton;
    QLabel *dofusInjectionStatus;
    QGroupBox *byteCodeGroup;
    QPushButton *byteCodePathBrowserButton;
    QLineEdit *byteCodePathLineEdit;
    QPushButton *byteCodeSendButton;
    QLabel *byteCodeStatus;
    QGroupBox *proxyGroup;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(543, 225);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
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
        dofusInjectionStatus = new QLabel(dofusGroup);
        dofusInjectionStatus->setObjectName(QStringLiteral("dofusInjectionStatus"));
        dofusInjectionStatus->setGeometry(QRect(100, 50, 241, 20));
        dofusInjectionStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
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
        dofusGroup->raise();
        dofusAppPathBrowserButton->raise();
        dofusAppPathLineEdit->raise();
        byteCodePathBrowserButton->raise();
        byteCodePathLineEdit->raise();
        byteCodeSendButton->raise();
        byteCodeStatus->raise();
        proxyGroup = new QGroupBox(centralWidget);
        proxyGroup->setObjectName(QStringLiteral("proxyGroup"));
        proxyGroup->setGeometry(QRect(370, 10, 161, 171));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 543, 21));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionQuitter);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Byte Code Proxy", Q_NULLPTR));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", Q_NULLPTR));
        dofusGroup->setTitle(QApplication::translate("MainWindow", "Client", Q_NULLPTR));
        dofusAppPathBrowserButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        dofusStartButton->setText(QApplication::translate("MainWindow", "Start Dofus", Q_NULLPTR));
        dofusInjectionStatus->setText(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        byteCodeGroup->setTitle(QApplication::translate("MainWindow", "Byte Code", Q_NULLPTR));
        byteCodePathBrowserButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        byteCodeSendButton->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        byteCodeStatus->setText(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        proxyGroup->setTitle(QApplication::translate("MainWindow", "Proxy", Q_NULLPTR));
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
