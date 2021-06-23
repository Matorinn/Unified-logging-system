#include "signal_for_zlog.h" /* для глобальных перенных */
#include "zlog.h"            /* для zlog_reload() */
#include <stdio.h>
#include <stdlib.h> /* для exit() */
#include <string.h> /* для memset() */
#include <unistd.h>

/* 
 * обработчик сигнала SIGHUP, в котором меняется 
 * конфигурация логирования 
 */
void signal_handler(int signal_number)
{
    rc = zlog_reload(config_name);
    if (rc) {
        fprintf(stderr, "error in zlog_reload()\n");
        exit(EXIT_FAILURE);
    }
}

/* связывание сигнала SIGHUP с нашим обработчиком */
int signal_binding(struct sigaction *sa)
{
    (*sa).sa_handler = &signal_handler;
    sigemptyset(&sa->sa_mask);
    sa->sa_flags = SA_SIGINFO;
    sigaction(SIGHUP, *&sa, NULL);
	return 0;
}
/* запись в файл pid */
void writing_pid_in_file(void)
{
    FILE *file;
    int pid;

    char name[] = "PID.txt";
    pid = getpid();
    file = fopen(name, "wb");
    if(file == NULL)
    {
        perror("Couldn't open the file");
        exit(-1);
    }
    fprintf(file, "%d", pid);
    fclose(file);
}
/* считывание из файла */
void read_file_for_get_pid(pid_t *pid)
{
    FILE *file;
    char name[] = "PID.txt";
    
    file = fopen(name, "r");
    if(file == NULL)
    {
        perror("Couldn't open the file");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", pid);        
    fclose(file);
}
/* отправка сигнала */
void send_signal()
{
    pid_t pid;

    read_file_for_get_pid(&pid);
    if((kill(pid, SIGHUP)) != 0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}
