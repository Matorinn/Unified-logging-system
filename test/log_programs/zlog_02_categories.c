#include "zlog.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int rc;
    zlog_category_t *zc;

    rc = zlog_init("zlog_02_categories.conf");
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
    zlog_debug(zc, "hello, zlog - debug");

    zc = zlog_get_category("my-cat");
    if (!zc) {
        printf("get cat fail\n");
        zlog_fini();
        return -2;
    }
    zlog_info(zc, "hello, zlog - info");

    zlog_fini();
    return 0;
}
