#include "signswf.h"
#include <QProcess>
#include <QFileInfo>
#include <QDebug>

SignSwf::SignSwf(QFileInfo* _swfFileInfo, QString _publicKey, QString _privateKey, Logger* _logger) :
    swfFileInfo(_swfFileInfo),
    publicKey(_publicKey),
    privateKey(_privateKey),
    logger(_logger)
{

}

QByteArray SignSwf::sign()
{
    QString input = swfFileInfo->absoluteFilePath();
    QString output = input + "s"; // swfs
    QByteArray data;

    QStringList arguments;
    arguments << input
              << output
              << privateKey
              << publicKey
              << "false";

    QProcess* process = new QProcess();
    process->start("signswf.bat", arguments);
    qDebug() << process->arguments();

    if (process->waitForFinished()) {
        QString cmdOuput = process->readAllStandardOutput();
        cmdOuput.replace("\r\n", "<br>").prepend("signswf.bat result:<br>");
        logger->log("SWF", "#fff", DEBUG, cmdOuput);

        QFile swfSignedFile(output);
        swfSignedFile.open(QIODevice::ReadOnly);
        data = swfSignedFile.readAll();
        swfSignedFile.close();
    } else {
        logger->log("SWF", "#fff", LOG_ERROR, process->errorString());
    }

    return data;
}
