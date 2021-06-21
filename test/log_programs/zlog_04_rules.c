#include "zlog.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int rc;
    rc = zlog_init("zlog_04_rules.conf");
    if (rc) {
        printf("init failed\n");
        return -1;
    }


    int count_categories = 6;
    zlog_category_t *category[count_categories];
    category[0] = zlog_get_category("aa");
    category[1] = zlog_get_category("aa_1");
    category[2] = zlog_get_category("aa_2");
    category[3] = zlog_get_category("bb");
    category[4] = zlog_get_category("bb_1");
    category[5] = zlog_get_category("cc");

    for (int i = 0; i < count_categories; i++) {
        if (!category[i]) {
            printf("get category[%d] fail\n", i);
            zlog_fini();
            return -2;
        }
    }

    zlog_info(category[0], "howdy, aa");
    zlog_info(category[1], "howdy, aa_1");
    zlog_info(category[2], "howdy, aa_2");
    zlog_info(category[3], "howdy, bb");
    zlog_info(category[4], "howdy, bb_1");
    zlog_info(category[5], "howdy, cc");

    zlog_fini();
    return 0;
}
