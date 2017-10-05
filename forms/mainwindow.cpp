#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <QTimer>
#include <windows.h>

#include <QDebug>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dofusClientPid(0),
    console(nullptr),
    server(nullptr),
    dataDir(nullptr)
{
    ui->setupUi(this);

    move(600, 300);

    setFixedSize(geometry().width(), geometry().height());

    ui->dofusStartButton->setEnabled(false);
    ui->dofusAppPathLineEdit->setText("C:/Program Files (x86)/Ankama/Dofus/app");

    ui->byteCodeGroup->setEnabled(false);

    ui->proxyAuthPortLineEdit->setText("5555");
    ui->proxyGamePortLineEdit->setText("5556");

    connect(ui->actionConsole, SIGNAL(triggered()), this, SLOT(openConsole()));

    connect(ui->dofusAppPathLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkDofusPath(QString)));
    connect(ui->dofusAppPathBrowserButton, SIGNAL(clicked()), this, SLOT(browseDofusPath()));
    connect(ui->dofusStartButton, SIGNAL(clicked()), this, SLOT(startDofusClient()));

    connect(ui->proxyHexdumpCheckBox, SIGNAL(toggled(bool)), this, SLOT(enableHexdump(bool)));

    connect(ui->byteCodeSendButton, SIGNAL(clicked()), this, SLOT(sendByteCode()));

    checkDofusPath(ui->dofusAppPathLineEdit->text());

    openConsole();

    logger = Logger::create(console);
    logger.log("MAIN", INFO, "Start " + qAppName());
    logger.enableHexdump(false);
}

MainWindow::~MainWindow()
{
    if (dofusClientPid) {
        QProcess::execute(QString("taskkill /pid %1 /f").arg(dofusClientPid));
    }

    if (dataDir) {
        delete dataDir;
    }

    delete ui;
}

void MainWindow::injectDll()
{
    QString dataDirPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    dataDir = new QDir(dataDirPath);

    if (!dataDir->exists()) {
        dataDir->mkpath(dataDirPath);
    }

    QString absoluteDllFilePath = dataDir->absoluteFilePath("hook_connect.dll");

    if (!QFile::exists(absoluteDllFilePath)) {
        QFile::copy(":/dll/hook_connect.dll", absoluteDllFilePath);
    }

    HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, false, dofusClientPid);

    const char* dllName = absoluteDllFilePath.toStdString().c_str();

    if(h)
    {
        LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
        LPVOID dereercomp = VirtualAllocEx(h, NULL, strlen(dllName), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(h, dereercomp, dllName, strlen(dllName), NULL);
        HANDLE asdc = CreateRemoteThread(h, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, dereercomp, 0, NULL);
        WaitForSingleObject(asdc, INFINITE);
        VirtualFreeEx(h, dereercomp, strlen(dllName), MEM_RELEASE);
        CloseHandle(asdc);
        CloseHandle(h);
    }
}

void MainWindow::enableHexdump(bool enable)
{
    qDebug() << enable;
    logger.enableHexdump(enable);
}

void MainWindow::checkDofusPath(QString path)
{
    if (QDir(path).exists() && QFile(path + "/Dofus.exe").exists())  {
        ui->dofusStatus->setText("Dofus found");
        ui->dofusStartButton->setEnabled(true);
    } else {
        ui->dofusStatus->setText("Dofus client not found");
        ui->dofusStartButton->setEnabled(false);
    }
}

void MainWindow::browseDofusPath()
{
    QFileDialog dirBrowser;

    dirBrowser.setFileMode(QFileDialog::Directory);
    dirBrowser.setOption(QFileDialog::ShowDirsOnly);

    if (dirBrowser.exec())
    {
        QString path = dirBrowser.selectedFiles()[0];
        ui->dofusAppPathLineEdit->setText(path);
        checkDofusPath(path);
    }
}

void MainWindow::startDofusClient()
{
    QString dofusClientPath = ui->dofusAppPathLineEdit->text() + "/Dofus.exe";

    QProcess::startDetached(dofusClientPath, QStringList(), QString(), &dofusClientPid);
    // TODO: check if dofusClientPid is running, if not enable start button

    if (dofusClientPid) {
        ui->proxyAuthPortLineEdit->setEnabled(false);
        ui->proxyGamePortLineEdit->setEnabled(false);

        ui->dofusStatus->setText("Dofus client started");
        ui->dofusStartButton->setEnabled(false);

        QTimer::singleShot(1500, this, SLOT(injectDll()));

        server = new Server(this);
        server->start(ui->proxyAuthPortLineEdit->text().toShort());
    }
}

void MainWindow::openConsole()
{
    if (!console) {
        console = new Console(this);
    }

    console->show();
}

void MainWindow::sendByteCode()
{

}


