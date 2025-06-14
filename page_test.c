#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_dummy(void)
{
    TEST_ASSERT_EQUAL_INT(1, 1);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_dummy);
    return UNITY_END();
}
