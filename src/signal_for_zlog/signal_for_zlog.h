#ifndef SIGNAL_FOR_ZLOG_H
#define SIGNAL_FOR_ZLOG_H

#include <signal.h> /* для работы с сигналами */

int rc; /* переменная для открытия конфиг-файла */
char *config_name; /* имя конфиг-файла*/

int signal_binding();
void signal_handler(int);

#endif