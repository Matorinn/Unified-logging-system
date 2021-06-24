#include "uls_functions.h"
#include "UlsChangeConfFile.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char uls_cache_path[256] = "uls_cache";

int is_path_to_configfile_exist(char *prog_name, char **path_to_configfile, char **path_to_logfile)
{
    FILE *uls_cache;
    if ((uls_cache = fopen(uls_cache_path, "r")) == NULL) {
        printf("Type configfile path at first!\n");
        return -1;
    }
    char uls_cache_parsed_line[256];

    *path_to_configfile = malloc(sizeof(char) * 256);
    *path_to_logfile = malloc(sizeof(char) * 256);
    while (fgets(uls_cache_parsed_line, 256, uls_cache)) {

        char *split_line;
        split_line = strtok(uls_cache_parsed_line, " ");

        while (split_line != NULL) {
            if (strcmp(prog_name, split_line) == 0) {
                split_line = strtok(NULL, " ");
                strcpy(*path_to_configfile, split_line);
                split_line = strtok(NULL, "\n");
                if (split_line == NULL) {
                    return -1;
                }
                strcpy(*path_to_logfile, split_line);
                fclose(uls_cache);
                return 0;
            } else {
                split_line = strtok(NULL, " ");
            }
        }
    }
    fclose(uls_cache);
    return -1;
}

void writer_to_config_file(char *level, char *path_to_logfile, char *path_to_configfile)
{
    int check_remake = UlsChangeConfFile(level, path_to_configfile, ULS_LOG_LEVEL);
    if (check_remake != 0) {
        FILE *config_file;
        if ((config_file = fopen(path_to_configfile, "a")) == NULL) {
            printf("Configfile doesn't not exist\n");
            exit(-1);
        }
        fprintf(config_file, "my_cat.%s \"%s\"\n", level, path_to_logfile);
        fclose(config_file);
    }
}

void set_level(struct input_data data)
{
    int checker_config;
    char *path_to_configfile;
    char *path_to_logfile;
    checker_config = is_path_to_configfile_exist(data.prog_name, &path_to_configfile, &path_to_logfile);
    if (checker_config == 0) {
        writer_to_config_file(data.value, path_to_logfile, path_to_configfile);
    } else {
        printf("Type logfile and configfile path at first!\n");
        exit(-1);
    }
}

void create_configfile(struct input_data data)
{
    FILE *uls_cache;
    if ((uls_cache = fopen(uls_cache_path, "a")) == NULL) {
        printf("Cant create/open uls_cache file\n");
        exit(-1);
    }
    fprintf(uls_cache, "%s %s\n", data.prog_name, data.value);
    fclose(uls_cache);

    FILE *config_file;
    if ((config_file = fopen(data.value, "w")) == NULL) {
        printf("Cant create/open config_file\n");
        exit(-1);
    }
    fprintf(config_file, "[rules]\n");
    fclose(config_file);
}

void create_logfile_path(struct input_data data)
{
    FILE *uls_cache;
    if ((uls_cache = fopen(uls_cache_path, "r")) == NULL) {
        printf("Input configfile path at first!\n");
        exit(-1);
    }
    char uls_cache_parsed_line[256];
    char *path_to_configfile = malloc(sizeof(char) * 256);
    char *split_line = malloc(sizeof(char) * 256);

    FILE *stpd;
    if ((stpd = fopen("stdp", "a")) == NULL) {
        printf("&&&&&");
        exit(-1);
    }

    while (fgets(uls_cache_parsed_line, 256, uls_cache)) {

        strcpy(split_line, uls_cache_parsed_line);
        split_line = strtok(split_line, " ");

        while (split_line != NULL) {
            if (strcmp(data.prog_name, split_line) == 0) {
                split_line = strtok(NULL, " \n");
                if (split_line == NULL) {
                    printf("Input configfile path at first!\n");
                    exit(-1);
                }
                strcpy(path_to_configfile, split_line);
                break;

            } else {
                fprintf(stpd, "%s", uls_cache_parsed_line);
                break;
            }
        }
    }

    fclose(uls_cache);
    fclose(stpd);
    remove(uls_cache_path);
    rename("stdp", uls_cache_path);

    int check_remake = UlsChangeConfFile(data.value, path_to_configfile, ULS_LOG_FILE);
    if (check_remake != 0) {
        uls_cache = fopen(uls_cache_path, "a");
        fprintf(uls_cache, "%s %s %s\n", data.prog_name, path_to_configfile, data.value);
        fclose(uls_cache);
    }
}

/* считывание из файла */
void read_file_for_get_pid(pid_t *pid)
{
    FILE *file;

    char *user_name;
    user_name = getlogin();
    char name[256] = "/home/";
    strcat(name, user_name);
    strcat(name, "/.cache/uls/PID");

    file = fopen(name, "r");
    if (file == NULL) {
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
    if ((kill(pid, SIGHUP)) != 0) {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}
