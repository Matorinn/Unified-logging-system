#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include "zlog.h"
#include "signal_for_zlog.h"

int main(int argc, char** argv)
{
	/* какой конфиг-файл использовать */
	config_name = malloc(sizeof("example.conf"));
	strcpy(config_name, "example.conf");
	printf("config_name == %s\n", config_name); 

	/* связывание сигнала SIGUSR2 с нашим обработчиком */
	signal_binding();

	/* информация о том, как передать SIGUSR2 */
	printf("SIGUSR2 == %d\n", SIGUSR2);
	printf("my PID == %d\n", getpid());
	printf("use command \"kill -%d %d\"\n\n", 
	       SIGUSR2, getpid());

	/* считывание конфиг-файла */
	rc = zlog_init(config_name);
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	zlog_category_t *zc;
	zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

	/* вывод сообщений в течение 2 минут */
	for (int i = 0; i < 60; i++) {
		zlog_debug(zc, "%s%d", "hello ", i);
		zlog_info(zc, "%s%d", "world ", i);
		sleep(2);
	}

	zlog_fini();
	return 0;
}
