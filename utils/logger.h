#ifndef LOGGER_H
#define LOGGER_H

#include "signleton.h"
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

class Logger : public Singleton<Logger>
{
private:
    Console* console;
    bool isHexdumpEnabled;

public:
    Logger() : console(nullptr), isHexdumpEnabled(false) { }
    Logger(Console* _console);

    void log(QString name, LogType type, QString message);
    void dump(QString message);

    void enableHexdump(bool enable);
};

#endif // LOGGER_H
