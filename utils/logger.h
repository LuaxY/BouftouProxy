#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

enum LogType {
    DEBUG,
    INFO,
    SUCCESS,
    FAIL,
    LOG_ERROR,
    WARNING,
    FATAL
};

class Console;

class Logger
{
private:
    Console* console;
    bool isHexdumpEnabled;

public:
    Logger(Console* _console);

    void log(QString name, QString color, LogType type, QString message);
    void dump(QString color, QString message);

    void enableHexdump(bool enable);
};

#endif // LOGGER_H
