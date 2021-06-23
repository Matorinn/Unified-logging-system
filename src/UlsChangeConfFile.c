/*=============================================================================

UlsCangeConfFile.c

                                                                   Полянский А.
                                                                     23.06.2021

=============================================================================*/

#include "UlsChangeConfFile.h"

int UlsChangeConfFile(char *newValue, char *fileName, int option)
{
    if((option != ULS_LOG_LEVEL) && (option != ULS_LOG_FILE))
        return -1;

    pid_t pid;

    char *egrepRequest = "^\\w+\\.[A-Z]+ \"(\\w|/|\\.)+\"$";

    if((pid = fork()) == 0) {
        int fd = open("/dev/null", O_WRONLY | O_CREAT, 0666);

        dup2(fd, 1);
        close(fd);

        if(execlp("egrep", "egrep", egrepRequest, fileName, NULL) == -1)
            return -1;
    }
    else if(pid == -1) {
        return -1;
    }

    int pid_status;

    waitpid(pid, &pid_status, 0);

    if(pid_status == 0) {
        char sedRequest[ULS_REQUEST_LENGTH] = "";

        if(option == ULS_LOG_LEVEL) {
            char *sedRequestBegin = "s:\\(^[[:alnum:]_]\\+\\.\\)[A-Z]\\+\\( \"[[:alnum:]_/\\.]\\+\"$\\):\\1";
            char *sedRequestEnd = "\\2:";

            strcat(sedRequest, sedRequestBegin);
            strcat(sedRequest, newValue);
            strcat(sedRequest, sedRequestEnd);
        }
        if(option == ULS_LOG_FILE) {
            char *sedRequestBegin = "s:\\(^[[:alnum:]_]\\+\\.[A-Z]\\+ \"\\)[[:alnum:]_/\\.]\\+\\(\"$\\):\\1";
            char *sedRequestEnd = "\\2:";

            strcat(sedRequest, sedRequestBegin);
            strcat(sedRequest, newValue);
            strcat(sedRequest, sedRequestEnd);
        }
        if((pid = fork()) == 0) {
            if(execlp("sed", "sed", "-i", sedRequest, fileName, NULL) == -1)
                return -1;
        }
        else if (pid == -1)
            return -1;

    }
    else
        return -1;

    waitpid(pid, &pid_status, 0);

    return 0;
}
