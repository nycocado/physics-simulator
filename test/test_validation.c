#include <glib.h>
#include "unity/unity.h"
#include "unity/unity_internals.h"

void setUp(void) {}
void tearDown(void) {}

/* Mirrors the mass validation guard in open_project:
 *   if (g_ascii_strtod(mass, NULL) <= 0) continue;
 * Returns TRUE when the string would be accepted as a valid mass. */
static gboolean mass_is_valid(const char* str)
{
    return g_ascii_strtod(str, NULL) > 0.0;
}

void test_positive_mass_accepted(void)
{
    TEST_ASSERT_TRUE(mass_is_valid("1.0"));
    TEST_ASSERT_TRUE(mass_is_valid("0.001"));
    TEST_ASSERT_TRUE(mass_is_valid("1e10"));
    TEST_ASSERT_TRUE(mass_is_valid("9.8"));
    TEST_ASSERT_TRUE(mass_is_valid("100"));
}

void test_zero_mass_rejected(void)
{
    TEST_ASSERT_FALSE(mass_is_valid("0"));
    TEST_ASSERT_FALSE(mass_is_valid("0.0"));
    TEST_ASSERT_FALSE(mass_is_valid("0.000"));
}

void test_negative_mass_rejected(void)
{
    TEST_ASSERT_FALSE(mass_is_valid("-1.0"));
    TEST_ASSERT_FALSE(mass_is_valid("-0.001"));
    TEST_ASSERT_FALSE(mass_is_valid("-9.8"));
}

/* Corrupted or blank fields must not crash and must be rejected. */
void test_nonnumeric_mass_rejected(void)
{
    TEST_ASSERT_FALSE(mass_is_valid("abc"));
    TEST_ASSERT_FALSE(mass_is_valid(""));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_positive_mass_accepted);
    RUN_TEST(test_zero_mass_rejected);
    RUN_TEST(test_negative_mass_rejected);
    RUN_TEST(test_nonnumeric_mass_rejected);
    return UNITY_END();
}
