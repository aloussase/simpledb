#include "unity.h"
#include "page.h"
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_page_set_get_int(void)
{
    Page page;
    page_init(&page);
    page_set_int(&page, 0, 12345);
    int value;
    int error = page_get_int(&page, 0, &value);
    TEST_ASSERT_EQUAL_INT(PAGE_ERROR_NONE, error);
    TEST_ASSERT_EQUAL_INT(12345, value);
    page_free(&page);
}

void test_page_set_get_bytes(void)
{
    Page page;
    page_init(&page);
    char src[] = "hello world";
    char dest[20] = {0};
    page_set_bytes(&page, 10, src, sizeof(src));
    int error = page_get_bytes(&page, 10, dest, sizeof(src));
    TEST_ASSERT_EQUAL_INT(PAGE_ERROR_NONE, error);
    TEST_ASSERT_EQUAL_STRING(src, dest);
    page_free(&page);
}

void test_page_set_get_string(void)
{
    Page page;
    page_init(&page);
    const char *str = "simpledb";
    char buf[32];
    page_set_string(&page, 100, str);
    int error = page_get_string(&page, 100, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_INT(PAGE_ERROR_NONE, error);
    TEST_ASSERT_EQUAL_STRING(str, buf);
    page_free(&page);
}

void test_page_get_string_error(void)
{
    Page page;
    page_init(&page);
    char buf[16];
    int error = page_get_string(&page, 1000, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_INT(PAGE_ERROR_GET_STRING, error);
    page_free(&page);
}

void test_page_get_int_error(void)
{
    Page page;
    page_init(&page);
    int value;
    int error = page_get_int(&page, 1000, &value);
    TEST_ASSERT_EQUAL_INT(PAGE_ERROR_GET_INT, error);
    page_free(&page);
}

void test_page_get_bytes_error(void)
{
    Page page;
    page_init(&page);
    char buf[8];
    int error = page_get_bytes(&page, 1000, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_INT(PAGE_ERROR_GET_BYTES, error);
    page_free(&page);
}

void test_page_set_bytes_multiple_offsets(void)
{
    typedef struct
    {
        const char *data;
        size_t offset;
    } TestEntry;

    TestEntry tests[] = {
        {"foo", 0},
        {"barbaz", 10},
        {"qux", 25}};

    const size_t num_entries = sizeof(tests) / sizeof(tests[0]);

    Page page;
    page_init(&page);

    for (size_t i = 0; i < num_entries; ++i)
    {
        page_set_bytes(&page, tests[i].offset, tests[i].data, strlen(tests[i].data) + 1);
    }

    char out[32];
    for (size_t i = 0; i < num_entries; ++i)
    {
        memset(out, 0, sizeof(out));
        int error = page_get_bytes(&page, tests[i].offset, out, strlen(tests[i].data) + 1);
        TEST_ASSERT_EQUAL_INT(PAGE_ERROR_NONE, error);
        TEST_ASSERT_EQUAL_STRING(tests[i].data, out);
    }

    page_free(&page);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_page_set_get_int);
    RUN_TEST(test_page_set_get_bytes);
    RUN_TEST(test_page_set_get_string);
    RUN_TEST(test_page_get_string_error);
    RUN_TEST(test_page_get_int_error);
    RUN_TEST(test_page_get_bytes_error);
    RUN_TEST(test_page_set_bytes_multiple_offsets);
    return UNITY_END();
}
