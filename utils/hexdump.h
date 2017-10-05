#ifndef HEXDUMP_H
#define HEXDUMP_H

#include <stdio.h>
#include <ctype.h>
#include <QString>

#define HEXDUMP_COLS 16

QString hexdump(void *mem, unsigned int len);

#endif // HEXDUMP_H
