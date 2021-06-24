#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct input_data {
    char *prog_name;
    char *command_name;
    char *parameter;
    char *value;
};

int is_path_to_configfile_exist(char *prog_name, char **path_to_configfile, char **path_to_logfile)
{
    FILE *uls_cache;
    if ((uls_cache = fopen("uls_cache", "r")) == NULL) {
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
    FILE *config_file;

    if ((config_file = fopen(path_to_configfile, "a")) == NULL) {
        printf("Configfile doesn't not exist\n");
        exit(-1);
    }
    fprintf(config_file, "my_cat.%s \"%s\"\n", level, path_to_logfile);
    fclose(config_file);
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

void create_logfile_path(struct input_data data)
{

    FILE *uls_cache;
    if ((uls_cache = fopen("uls_cache", "r")) == NULL) {
        printf("Input configfile path at first!\n");
        exit(-1);
    }
    char uls_cache_parsed_line[256];
    char *path_to_configfile = malloc(sizeof(char) * 256);
    char *split_line = malloc(sizeof(char) * 256);

    FILE *stpd;
    if ((stpd = fopen("stpd", "a")) == NULL) {
        printf("&&&&&");
        exit(-1);
    }

    while (fgets(uls_cache_parsed_line, 256, uls_cache)) {

        strcpy(split_line, uls_cache_parsed_line);
        split_line = strtok(split_line, " ");

        while (split_line != NULL) {
            printf(".%s. .%s.\n", data.prog_name, split_line);
            if (strcmp(data.prog_name, split_line) == 0) {
                split_line = strtok(NULL, "\n");
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
    remove("uls_cache");
    rename("stpd", "uls_cache");

    uls_cache = fopen("uls_cache", "a");
    fprintf(uls_cache, "%s %s %s\n", data.prog_name, path_to_configfile, data.value);
    fclose(uls_cache);
}


int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 5) {
        fprintf(stderr, "Wrong number of arguments\n");
        return -1;
    }

    struct input_data data;

    if (argc == 3) {
        data.prog_name = argv[1];
        data.command_name = argv[2];
    } else if (argc == 5) {
        data.prog_name = argv[1];
        data.command_name = argv[2];
        data.parameter = argv[3];
        data.value = argv[4];
    } else {
        fprintf(stderr, "Wrong number of arguments\n");
        return -1;
    }

    if (strcmp(data.command_name, "set") == 0) {
        if (strcmp(data.parameter, "logfile") == 0) {
            create_logfile_path(data);

        } else if (strcmp(data.parameter, "configfile") == 0) {

            FILE *uls_cache;
            if ((uls_cache = fopen("uls_cache", "a")) == NULL) {
                printf("Cant create/open uls_cache file\n");
                return -1;
            }
            fprintf(uls_cache, "%s %s\n", data.prog_name, data.value);
            fclose(uls_cache);

            FILE *config_file;
            if ((config_file = fopen(data.value, "w")) == NULL) {
                printf("Cant create/open config_file\n");
                return -1;
            }
            fprintf(config_file, "[rules]\n");
            fclose(config_file);

        } else if (strcmp(data.parameter, "level") == 0) {
            set_level(data);
        } else {
            printf("Wrong input\n");
            return -1;
        }
    } else if (strcmp(data.command_name, "commit") == 0) {
        printf("commit\n");
        //отправка сигнала о изменении конфига
    }

    else {
        printf("Wrong input\n");
        return -1;
    }
    return 0;
}
