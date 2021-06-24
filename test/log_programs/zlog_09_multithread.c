#include "zlog.h"
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define CONFIG "zlog_09_multithread.conf"
#define NB_THREADS 5

struct thread_info {     /* Used as argument to thread_start() */
    pthread_t thread_id; /* ID returned by pthread_create() */
    int thread_num;      /* Application-defined thread # */
    zlog_category_t *zc; /* The logger category struc address; (All threads will use the same category, so he same address) */
    long long int loop;  /* Counter incremented to check the thread's health */
};

struct thread_info *tinfo;

void *myThread(void *arg)
{
    struct thread_info *tinfo = arg;

    tinfo->zc = zlog_get_category("main");
    if (!tinfo->zc) {
        printf("get thrd %d cat fail\n", tinfo->thread_num);
    } else {
        for (int i = 0; i < 5; i++)
            zlog_info(tinfo->zc, "thread %d, iteration %d",
                      tinfo->thread_num, i + 1);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    int rc;
    zlog_category_t *zc;
    int i = 0;
    struct stat stat_0;

    if (stat(CONFIG, &stat_0)) {
        printf("Configuration file not found\n");
        return -1;
    }

    rc = zlog_init(CONFIG);
    if (rc) {
        printf("main init failed\n");
        return -2;
    }

    zc = zlog_get_category("main");
    if (!zc) {
        printf("main get cat fail\n");
        zlog_fini();
        return -3;
    }

    // start threads
    tinfo = calloc(NB_THREADS, sizeof(struct thread_info));
    for (i = 0; i < NB_THREADS; i++) {
        tinfo[i].thread_num = i + 1;
        tinfo[i].loop = 0;
        tinfo[i].zc = zc;
        if (pthread_create(&tinfo[i].thread_id, NULL, myThread, &tinfo[i]) != 0) {
            zlog_fatal(zc, "Unable to start thread %d", i);
            zlog_fini();
            return (-5);
        }
    }

    for (i = 0; i < NB_THREADS; i++)
        pthread_join(tinfo[i].thread_id, NULL);

    exit(EXIT_SUCCESS);
}
