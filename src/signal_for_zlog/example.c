#include "signal_for_zlog.h"
#include "zlog.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    /* какой конфиг-файл использовать */
    writing_pid_in_file();
    config_name = malloc(sizeof("example.conf"));
    strcpy(config_name, "example.conf");
    printf("config_name == %s\n", config_name);
    /* связывание сигнала SIGHUP с нашим обработчиком */
    struct sigaction sa; /* структура для сигнала */
    signal_binding(&sa);

    /* информация о том, как передать SIGHUP */
    printf("SIGHUP == %d\n", SIGHUP);
    printf("my PID == %d\n", getpid());
    printf("use command \"kill -%d %d\"\n\n",
           SIGHUP, getpid());

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
