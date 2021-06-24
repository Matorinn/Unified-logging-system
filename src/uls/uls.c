#include "UlsChangeConfFile.h"
#include "uls_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            create_configfile(data);
        } else if (strcmp(data.parameter, "level") == 0) {
            set_level(data);
        } else {
            printf("Wrong input\n");
            return -1;
        }
    } else if (strcmp(data.command_name, "commit") == 0) {
        send_signal();
    }

    else {
        printf("Wrong input\n");
        return -1;
    }
    return 0;
}
