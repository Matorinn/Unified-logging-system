#define CTEST_MAIN
#include "ctest.h"

int main(int argc, const char **argv)
{
    return ctest_main(argc, argv);
}

int compare_logfiles(const char *filename1, const char *filename2)
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
    int ret = 0;//если файлы одинаковые, то ret == 0
    if (byte1 != byte2)
        ret = 1;
    //else if (feof(fp1) != feof(fp2))
    //    ret = 2;

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
    const char fileToCompare[] = "test/log_files/simple_example.txt";
    const char fileCorrect[] = "test/log_correct/simple_example.txt";

    /* результат тестирования: */
    const int result = compare_logfiles(fileToCompare, fileCorrect);

    /* сравнить полученное и ожидаемое значения: */
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(simple_example_suite, corrupted)
{
    const char fileToCompare[] = "test/log_files/simple_example_corrupted.txt";
    const char fileCorrect[] = "test/log_correct/simple_example.txt";

	const int result = compare_logfiles(fileToCompare, fileCorrect);

	const int expected = 1;
	ASSERT_EQUAL(expected, result);
}