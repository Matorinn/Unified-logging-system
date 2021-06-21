#include "zlog.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int rc;
    rc = zlog_init("zlog_06_levels.conf");
    if (rc) {
        printf("init failed\n");
        return -1;
    }

    zlog_category_t *category;
    category = zlog_get_category("my_category");
    if (!category) {
        printf("get category fail\n");
        zlog_fini();
        return -2;
    }

    zlog_debug(category, "log debug");
    zlog_info(category, "log info");
    zlog_notice(category, "log notice");

    zlog_fini();
    return 0;
}
