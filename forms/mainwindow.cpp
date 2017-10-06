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
    ui->dofusAppPathLineEdit->setText("C:/Program Files (x86)/Ankama/Dofus/app/Dofus.exe");

    ui->proxyPortLineEdit->setText("5555");
    ui->proxyStatus->setText("Proxy OFF");

    ui->byteCodeGroup->setEnabled(false);
    ui->byteCodePathLineEdit->setText("C:/Workspace/ByteCode/dev/ByteCodeTester/bin/ByteCodeTester.swf");

    connect(ui->actionConsole, SIGNAL(triggered()), this, SLOT(openConsole()));

    connect(ui->dofusAppPathLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkDofusClient(QString)));
    connect(ui->dofusAppPathBrowserButton, SIGNAL(clicked()), this, SLOT(browseDofusClient()));
    connect(ui->dofusStartButton, SIGNAL(clicked()), this, SLOT(startDofusClient()));

    connect(ui->proxyStartButton, SIGNAL(clicked()), this, SLOT(startDofusClient()));
    connect(ui->proxyFastFowardCheckBox, SIGNAL(stateChanged(int)), this, SLOT(enableFastForward(int)));
    connect(ui->proxyHexdumpCheckBox, SIGNAL(stateChanged(int)), this, SLOT(enableHexdump(int)));

    connect(ui->byteCodePathLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkByteCodeFile(QString)));
    connect(ui->byteCodePathBrowserButton, SIGNAL(clicked()), this, SLOT(browseByteCodeFile()));
    connect(ui->byteCodeSendButton, SIGNAL(clicked()), this, SLOT(sendByteCode()));

    checkDofusClient(ui->dofusAppPathLineEdit->text());
    checkByteCodeFile(ui->byteCodePathLineEdit->text());

    openConsole();

    logger = new Logger(console);
    logger->log("MAIN", "#fff", INFO, "Start " + qAppName());
    logger->enableHexdump(false);
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

void MainWindow::startProxy()
{
    server = new Server(logger, this);
    server->setNext("213.248.126.39", 5555);
    server->start(ui->proxyPortLineEdit->text().toShort());

    connect((Proxy*)server, SIGNAL(isInGame()), this, SLOT(onIsInGame()));

    ui->proxyPortLineEdit->setEnabled(false);
    ui->proxyStartButton->setEnabled(false);
    ui->proxyStatus->setText("Proxy ON");
}

void MainWindow::enableHexdump(int state)
{
    logger->enableHexdump(state == Qt::Checked);
}

void MainWindow::enableFastForward(int state)
{
    server->setFastForward(state == Qt::Checked);
}

void MainWindow::onIsInGame()
{
    ui->proxyFastFowardCheckBox->setChecked(true);
    ui->byteCodeGroup->setEnabled(true);
}

void MainWindow::checkByteCodeFile(QString path)
{
    if (QFile(path).exists())  {
        ui->byteCodeStatus->setText("ByteCode ready");
        ui->byteCodeSendButton->setEnabled(true);
    } else {
        ui->dofusStatus->setText("ByteCode not found");
        ui->byteCodeSendButton->setEnabled(false);
    }
}

void MainWindow::browseByteCodeFile()
{
    QFileDialog dirBrowser;

    dirBrowser.setFileMode(QFileDialog::ExistingFile);
    dirBrowser.setNameFilter("*.swf *.swfs");

    if (dirBrowser.exec())
    {
        QString path = dirBrowser.selectedFiles()[0];
        ui->byteCodePathLineEdit->setText(path);
        checkDofusClient(path);
    }
}

void MainWindow::checkDofusClient(QString path)
{
    if (QFile(path).exists())  {
        ui->dofusStatus->setText("Dofus found");
        ui->dofusStartButton->setEnabled(true);
    } else {
        ui->dofusStatus->setText("Dofus client not found");
        ui->dofusStartButton->setEnabled(false);
    }
}

void MainWindow::browseDofusClient()
{
    QFileDialog dirBrowser;

    dirBrowser.setFileMode(QFileDialog::ExistingFile);
    dirBrowser.setNameFilter("*.exe");

    if (dirBrowser.exec())
    {
        QString path = dirBrowser.selectedFiles()[0];
        ui->dofusAppPathLineEdit->setText(path);
        checkDofusClient(path);
    }
}

void MainWindow::startDofusClient()
{
    QString dofusClientPath = ui->dofusAppPathLineEdit->text();

    QProcess::startDetached(dofusClientPath, QStringList(), QString(), &dofusClientPid);
    // TODO: check if dofusClientPid is running, if not enable start button

    if (dofusClientPid) {
        ui->dofusStatus->setText("Dofus client started");
        ui->dofusStartButton->setEnabled(false);

        QTimer::singleShot(1500, this, SLOT(injectDll()));

        startProxy();
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
    QFile byteCodeFile(ui->byteCodePathLineEdit->text());
    byteCodeFile.open(QIODevice::ReadOnly);
    QByteArray byteCode = byteCodeFile.readAll();
    byteCodeFile.close();

    server->sendByteCode(byteCode);

    ui->byteCodeStatus->setText("ByteCode sent");
}


