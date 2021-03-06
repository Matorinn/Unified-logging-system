#define CTEST_MAIN
#include "ctest.h"

int main(int argc, const char **argv)
{
    return ctest_main(argc, argv);
}

int compare_logfiles2(const char *filename1, const char *filename2)
{
    /* открытие файлов по переданным именам: */
    FILE *fp1 = fopen(filename1, "rb");
    if (fp1 == NULL)
        return -1;

    FILE *fp2 = fopen(filename2, "rb");
    if (fp2 == NULL) {
        fclose(fp1);
        return -2;
    }

    /* побайтное сравнение: */
    unsigned char byte1 = 0, byte2 = 0;
    while (!feof(fp1) && !feof(fp2) && (byte1 == byte2)) {
        byte1 = fgetc(fp1);
        byte2 = fgetc(fp2);
        //printf("%c %c\n", byte1, byte2);
    }

    /* анализ, совпадают файлы или нет: */
    int ret = 0; /* если файлы одинаковые, то ret == 0 */
    if (byte1 != byte2)
        ret = 1;
    //else if (feof(fp1) != feof(fp2))
    //    ret = 2;

    fclose(fp1), fclose(fp2);
    return ret;
}

/*
 * Это функция для сравнения лог-файлов, в которых часть
 * данных надо игнорировать. Например, если в начале 
 * каждого лога записывается время или PID, то эту 
 * информацию надо игнорировать, потому что она всегда
 * будет разной. Сравнивать надо именно сообщения.
 */

int compare_logfiles5(const char *filename1, /* 1-ый лог-файл */
                      const char *filename2, /* 2-ой лог-файл */
                      int string_len,        /* максимальная длина строки */
                      char start_symbol,     /* символ, откуда надо сравнивать */
                      int offset)            /* смещение влево от start_symbol */
{
    /* открытие файлов по переданным именам: */
    FILE *fp1 = fopen(filename1, "rb");
    if (fp1 == NULL)
        return -1;

    FILE *fp2 = fopen(filename2, "rb");
    if (fp2 == NULL) {
        fclose(fp1);
        return -2;
    }

    int ret = 0; /* что будет возвращать функция */
    while (1) {
        char *string1 = malloc(string_len * sizeof(char));
        char *string2 = malloc(string_len * sizeof(char));
        memset(string1, '\0', string_len);
        memset(string2, '\0', string_len);

        char *ret_fgets1 = fgets(string1, string_len, fp1);
        char *ret_fgets2 = fgets(string2, string_len, fp2);
        //printf("\n%s%s", string1, string2);

        /* если конец файлов */
        if (ret_fgets1 == NULL && ret_fgets2 == NULL) {
            free(string1), free(string2);
            break;
        }

        /* найти место в логе, откуда сравнивать (где нет времени и пр.) */
        int i;
        for (i = 0; i < string_len; i++) {
            if (string1[i] == start_symbol)
                break;
        }
        //printf("\n%s%s", string1 + i - offset, string2 + i - offset);

        /* если подстроки не совпадают, вернуть 1 */
        if (strcmp(string1 + i - offset, string2 + i - offset)) {
            ret = 1;
            free(string1), free(string2);
            break;
        }

        free(string1), free(string2);
    }

    fclose(fp1), fclose(fp2);
    return ret;
}


/*
 * CTEST(<suite_name>, <test_name>) - макрос для создания и 
 * регистрации тестовой функции. Все определенные таким образом 
 * тесты запускаются автоматически при вызове ctest_main()
 */

CTEST(simple_example_suite, usual)
{
    /* файлы для тестирования: */
    const char fileToCompare[] = "log_files/simple_example.txt";
    const char fileCorrect[] = "log_correct/simple_example.txt";

    /* результат тестирования: */
    const int result = compare_logfiles2(fileToCompare, fileCorrect);

    /* сравнить полученное и ожидаемое значения: */
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(simple_example_suite, corrupted)
{
    const char fileToCompare[] = "log_files/simple_example_corrupted.txt";
    const char fileCorrect[] = "log_correct/simple_example.txt";

    const int result = compare_logfiles2(fileToCompare, fileCorrect);

    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(zlog_suite, 01_simple)
{
    const char fileToCompare[] = "log_files/zlog_01_simple.log";
    const char fileCorrect[] = "log_correct/zlog_01_simple.log";

    const int result = compare_logfiles5(fileToCompare, fileCorrect, 256, '_', 4);

    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(zlog_suite, 02_categories)
{
    const char fileToCompare[] = "log_files/zlog_02_categories.log";
    const char fileCorrect[] = "log_correct/zlog_02_categories.log";

    const int result = compare_logfiles2(fileToCompare, fileCorrect);

    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(zlog_suite, 03_formats)
{
    const char fileToCompare[] = "log_files/zlog_03_formats.log";
    const char fileCorrect[] = "log_correct/zlog_03_formats.log";

    const int result = compare_logfiles5(fileToCompare, fileCorrect, 256, '!', 0);

    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(zlog_suite, 04_rules)
{
    const char fileToCompare[] = "log_files/zlog_04_rules.log";
    const char fileCorrect[] = "log_correct/zlog_04_rules.log";

    const int result = compare_logfiles2(fileToCompare, fileCorrect);

    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(zlog_suite, 05_levels)
{
    const char fileToCompare[] = "log_files/zlog_05_levels.log";
    const char fileCorrect[] = "log_correct/zlog_05_levels.log";

    const int result = compare_logfiles2(fileToCompare, fileCorrect);

    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(zlog_suite, 06_levels)
{
    const char fileToCompare[] = "log_files/zlog_06_levels.log";
    const char fileCorrect[] = "log_correct/zlog_06_levels.log";

    const int result = compare_logfiles2(fileToCompare, fileCorrect);

    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(zlog_suite, 07_rotation)
{
    char fileToCompare[] = "log_files/zlog_07_rotation_(21).log";
    char fileCorrect[] = "log_correct/zlog_07_rotation_(21).log";

    int result = compare_logfiles2(fileToCompare, fileCorrect);

    strcpy(fileToCompare, "log_files/zlog_07_rotation_(22).log");
    strcpy(fileCorrect, "log_files/zlog_07_rotation_(22).log");

    result += compare_logfiles2(fileToCompare, fileCorrect);

    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(zlog_suite, 08_MDC)
{
    const char fileToCompare[] = "log_files/zlog_08_MDC.log";
    const char fileCorrect[] = "log_correct/zlog_08_MDC.log";

    const int result = compare_logfiles2(fileToCompare, fileCorrect);

    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}