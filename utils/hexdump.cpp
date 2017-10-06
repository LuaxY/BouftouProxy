#include "hexdump.h"

QString hexdump(void *mem, unsigned int len)
{
    unsigned int i, j;
    QString hexdump;

    for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++)
    {
        /* print offset */
        if(i % HEXDUMP_COLS == 0)
        {
            //printf("0x%06X: ", i);
            hexdump.append(QString("0x%1: ").arg(i, 6, 16, QChar('0')));
        }

        /* print hex data */
        if(i < len)
        {
            //printf("%02X ", 0xFF & ((char*)mem)[i]);
            hexdump.append(QString("%1 ").arg(0xFF & ((char*)mem)[i], 2, 16, QChar('0')));
        }
        else /* end of block, just aligning for ASCII dump */
        {
            //printf("   ");
            hexdump.append("&nbsp;&nbsp;&nbsp;");
        }

        /* print ASCII dump */
        if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
        {
            for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
            {
                //char currentChar = 0xFF & ((char*)mem)[j];
                if(j >= len) /* end of block, not really printing */
                {
                    //putchar(' ');
                    hexdump.append(' ');
                }
                else if(isprint(((char*)mem)[j])) /* printable char */
                //else if(currentChar >= 0x20 && currentChar <= 0x7e) /* printable char */
                {
                    //putchar(0xFF & ((char*)mem)[j]);
                    hexdump.append(0xFF & ((char*)mem)[j]);
                }
                else /* other char */
                {
                    //putchar('.');
                    hexdump.append('.');
                }
            }
            //putchar('\n');
            hexdump.append("<br>\n");
        }
    }

    hexdump.append("<br>");

    return hexdump;
}
