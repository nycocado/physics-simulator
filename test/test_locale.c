#include <glib.h>
#include "unity/unity.h"
#include "unity/unity_internals.h"

#define PRECISION 0.001

void setUp(void) {}
void tearDown(void) {}

void test_dot_decimal_parses_correctly(void)
{
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 9.8, g_ascii_strtod("9.8", NULL));
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, -9.8, g_ascii_strtod("-9.8", NULL));
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 0.001, g_ascii_strtod("0.001", NULL));
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 1000.0, g_ascii_strtod("1e3", NULL));
}

/* g_ascii_strtod always uses '.' as decimal separator regardless of locale.
 * A comma-decimal string like "9,8" is read as 9 (stops at the comma).
 * This guarantees dot-decimal .sabino files are parsed identically in any locale. */
void test_comma_decimal_stops_at_comma(void)
{
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 9.0, g_ascii_strtod("9,8", NULL));
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 0.0, g_ascii_strtod(",8", NULL));
}

void test_zero_and_negative(void)
{
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 0.0, g_ascii_strtod("0", NULL));
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 0.0, g_ascii_strtod("0.0", NULL));
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, -1.0, g_ascii_strtod("-1", NULL));
}

void test_nonnumeric_string_returns_zero(void)
{
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 0.0, g_ascii_strtod("abc", NULL));
    TEST_ASSERT_DOUBLE_WITHIN(PRECISION, 0.0, g_ascii_strtod("", NULL));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_dot_decimal_parses_correctly);
    RUN_TEST(test_comma_decimal_stops_at_comma);
    RUN_TEST(test_zero_and_negative);
    RUN_TEST(test_nonnumeric_string_returns_zero);
    return UNITY_END();
}
