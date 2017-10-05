#include "logger.h"
#include "forms/console.h"

#include <QTime>

Logger::Logger(Console *_console) : console(_console), isHexdumpEnabled(false)
{

}

void Logger::log(QString name, LogType type, QString message)
{
    QString typeString;
    QString typeColor;

    switch (type) {
    case DEBUG:
        typeString = "DEBUG";
        typeColor = "lightblue";
        break;
    case INFO:
        typeString = "INFO";
        typeColor = "blue";
        break;
    case SUCCESS:
        typeString = "SUCCESS";
        typeColor = "green";
        break;
    case FAIL:
        typeString = "FAIL";
        typeColor = "lightred";
        break;
    case LOG_ERROR:
        typeString = "ERROR";
        typeColor = "red";
        break;
    case WARNING:
        typeString = "WARNING";
        typeColor = "orange";
        break;
    case FATAL:
        typeString = "FATAL";
        typeColor = "darkred";
        break;
    default:
        break;
    }

    QTime time = QTime::currentTime();
    QString timeFormated = time.toString("hh:mm:ss.zzz");

    console->write(QString("[%1][<font colo='%2'>%3</color>][%4] %5")
                   .arg(timeFormated)
                   .arg(typeColor)
                   .arg(typeString)
                   .arg(name)
                   .arg(message));
}

void Logger::dump(QString message)
{
    if (isHexdumpEnabled) console->write(message);
}

void Logger::enableHexdump(bool enable)
{
    isHexdumpEnabled = enable;
}
