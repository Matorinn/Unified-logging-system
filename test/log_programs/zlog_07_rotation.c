#include "zlog.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int rc;
    rc = zlog_init("zlog_07_rotation.conf");
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

    zlog_info(category, "line 1");
    zlog_info(category, "line 2");

    zlog_fini();
    return 0;
}
