#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils/signswf.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <QTimer>
#include <windows.h>

#include <QDebug>

BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam);
DWORD pid;
int posX, posY, sizeW, sizeL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dofusClientPid(0),
    console(nullptr),
    server(nullptr),
    dataDir(nullptr),
    settings("config.ini", QSettings::IniFormat)
{
    ui->setupUi(this);

    posX = settings.value("dofus/x").toInt();
    posY = settings.value("dofus/y").toInt();
    sizeW = settings.value("dofus/w").toInt();
    sizeL = settings.value("dofus/l").toInt();

    int appX = settings.value("app/x", 600).toInt();
    int appY = settings.value("app/y", 300).toInt();

    move(appX, appY);

    setFixedSize(geometry().width(), geometry().height());

    ui->dofusStartButton->setEnabled(false);
    ui->dofusAppPathLineEdit->setText(settings.value("dofus/path", "").toString());

    ui->proxyPortLineEdit->setText(settings.value("proxy/port", "5555").toString());
    ui->proxyStatus->setText("Proxy OFF");

    ui->byteCodeGroup->setEnabled(false);
    ui->byteCodePathLineEdit->setText(settings.value("bytecode/path", "").toString());

    connect(ui->actionConsole, SIGNAL(triggered()), this, SLOT(openConsole()));

    connect(ui->dofusAppPathLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkDofusClient(QString)));
    connect(ui->dofusAppPathBrowserButton, SIGNAL(clicked()), this, SLOT(browseDofusClient()));
    connect(ui->dofusStartButton, SIGNAL(clicked()), this, SLOT(startDofusClient()));

    connect(ui->proxyStartButton, SIGNAL(clicked()), this, SLOT(startProxy()));
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

    pid = dofusClientPid;
    EnumWindows(EnumWindowsProc, 0);
}

void MainWindow::startProxy()
{
    server = new Server(logger, this);
    server->setNext(settings.value("dofus/ip", "213.248.126.39").toString(), settings.value("dofus/port", 5555).toInt());
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

        QTimer::singleShot(settings.value("dofus/injectDelay", 1500).toInt(), this, SLOT(injectDll()));

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
    QString publicKey = settings.value("bytecode/public_key").toString();
    QString privateKey = settings.value("bytecode/private_key").toString();

    QFile byteCodeFile(ui->byteCodePathLineEdit->text());

    QFileInfo byteCodeFileInfo(byteCodeFile);
    QByteArray byteCode;

    if (byteCodeFileInfo.fileName().endsWith(".swfs")) {
        byteCodeFile.open(QIODevice::ReadOnly);
        byteCode = byteCodeFile.readAll();
        byteCodeFile.close();
    } else {
        SignSwf signSwf(&byteCodeFileInfo, publicKey, privateKey, logger);
        byteCode = signSwf.sign();
    }

    server->sendByteCode(byteCode);

    ui->byteCodeStatus->setText("ByteCode sent");
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam) {
    if (IsWindowVisible(hWnd)) {
        DWORD lpdwProcessId;
        GetWindowThreadProcessId(hWnd,&lpdwProcessId);

        if (pid == lpdwProcessId) {
            SetWindowPos(hWnd, NULL, posX, posY, sizeW, sizeL, SWP_SHOWWINDOW);
        }
    }

    return true;
}


