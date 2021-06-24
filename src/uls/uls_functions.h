#ifndef ULS_FUNCTIONS_H
#define ULS_FUNCTIONS_H

#include <unistd.h>

struct input_data {
    char *prog_name;
    char *command_name;
    char *parameter;
    char *value;
};

int is_path_to_configfile_exist(char *prog_name, char **path_to_configfile, char **path_to_logfile);
void writer_to_config_file(char *level, char *path_to_logfile, char *path_to_configfile);
void set_level(struct input_data data);
void create_configfile(struct input_data data);
void create_logfile_path(struct input_data data);
void read_file_for_get_pid(pid_t *pid); /* считывание pid в память */
void send_signal();                     /* отправка сигнала нашей программе */

#endif
