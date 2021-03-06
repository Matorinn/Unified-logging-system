#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "zlog.h"

int main(int argc, char **argv)
{
    int rc;
    zlog_category_t *zc;

    rc = zlog_init("zlog_08_MDC.conf");
    if (rc) {
        printf("init failed\n");
        return -1;
    }

    zc = zlog_get_category("my_cat");
    if (!zc) {
        printf("get cat fail\n");
        zlog_fini();
        return -2;
    }

    zlog_info(zc, "1.hello, zlog");

    zlog_put_mdc("myname", "Zhang");

    zlog_info(zc, "2.hello, zlog");

    zlog_put_mdc("myname", "Li");

    zlog_info(zc, "3.hello, zlog");

    zlog_fini();

    return 0;
}
