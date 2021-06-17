#include <stdio.h>

int main(int argc, char *argv[])
{
    /* открытие файла, в который будут записываться логи: */
    FILE *fileLogs = fopen("../log_files/simple_example.txt", "w");
    if (fileLogs == NULL) {
        perror("error in fopen()");
        return 1;
    }
    fprintf(fileLogs, "Application launch\n");

    /* заполнение массива: */
    char data[8] = {0};
    for (int i = 0; i < 8; i++) {
        data[i] = 'A' + i;
    }

    /* вывод массива в виде лога: */
    fprintf(fileLogs, "%s\n", data);

    fprintf(fileLogs, "This is a error message\n");
    fprintf(fileLogs, "This is a log message\n");

    /* закрытие файла: */
    fprintf(fileLogs, "Termination of the application\n");
    fclose(fileLogs);

    return 0;
}
