#ifndef SIGNAL_FOR_ZLOG_H
#define SIGNAL_FOR_ZLOG_H

#include <signal.h> /* для работы с сигналами */

int rc;            /* переменная для открытия конфиг-файла */
char *config_name; /* имя конфиг-файла*/

void signal_handler(int signal_number);
int signal_binding(struct sigaction *sa);
void writing_pid_in_file(void); /* получение pid нашей программы и запись в файл */
void read_file_for_get_pid(pid_t *pid);/* считывание pid в память */
void send_signal();/* отправка сигнала нашей программе */

#endif