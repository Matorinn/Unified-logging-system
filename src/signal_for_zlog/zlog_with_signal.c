#include <stdio.h>
#include "zlog.h"
#include <unistd.h>

#include <signal.h> /* для работы с сигналами */
#include <string.h> /* для memset() */
#include <stdlib.h> /* для exit() */

int rc; /* переменная для открытия конфиг-файла */
#define CONFIG "zlog_with_signal.conf" /* имя конфиг-файла*/

/* 
 * обработчик сигнала SIGUSR2, в котором меняется 
 * конфигурация логирования 
 */
void signal_handler(int signal_number) {
	rc = zlog_reload(CONFIG);
	if (rc) {
		fprintf(stderr, "error in zlog_reload()\n");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char** argv)
{
	/* связывание сигнала SIGUSR2 с нашим обработчиком */
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &signal_handler;
	sigaction(SIGUSR2, &sa, NULL);

	printf("SIGUSR2 == %d\n", SIGUSR2);
	printf("my PID == %d\n", getpid());
	printf("use command \"kill -%d %d\"\n\n", 
	       SIGUSR2, getpid());

	zlog_category_t *zc;

	rc = zlog_init(CONFIG);
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

	for (int i = 0; i < 60; i++) {
		zlog_debug(zc, "%s%d", "hello ", i);
		zlog_info(zc, "%s%d", "world ", i);
		sleep(2);
	}

	zlog_fini();
	return 0;
}
