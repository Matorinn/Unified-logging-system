#include <stdio.h>
#include <string.h> /* для memset() */
#include <stdlib.h> /* для exit() */
#include "zlog.h" /* для zlog_reload() */
#include "signal_for_zlog.h" /* для глобальных перенных */

/* 
 * обработчик сигнала SIGUSR2, в котором меняется 
 * конфигурация логирования 
 */
void signal_handler(int signal_number) {
	rc = zlog_reload(config_name);
	if (rc) {
		fprintf(stderr, "error in zlog_reload()\n");
		exit(EXIT_FAILURE);
	}
}

/* связывание сигнала SIGUSR2 с нашим обработчиком */
int signal_binding() {
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &signal_handler;
	sigaction(SIGUSR2, &sa, NULL);
	return 0;
}
