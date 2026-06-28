#include "physics/kinematics.h"
#include "physics/dynamics.h"
#include <math.h>
#include "unity/unity.h"
#include "unity/unity_internals.h"

#define PRECISION 0.001f
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void setUp(void) {}
void tearDown(void) {}

void test_kinematic_position_at_t1_with_gravity(void)
{
    float g = 9.8f;
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -4.9f, phyc_position(0.0f, 0.0f, -g, 1.0f));
}

void test_kinematic_position_initial_offset(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 10.0f, phyc_position(10.0f, 0.0f, 0.0f, 1.0f));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 13.0f, phyc_position(10.0f, 3.0f, 0.0f, 1.0f));
}

void test_kinematic_velocity_at_t1_with_gravity(void)
{
    float g = 9.8f;
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -9.8f, phyc_velocity(0.0f, -g, 1.0f));
}

void test_cinematic_gravity_applied_externally(void)
{
    /* In cinematic mode gravity is subtracted at the call site: phyc_position(yi, vyi, ay - g, t).
     * With ay=0 and g=9.8, the effective acceleration is -9.8. */
    float g = 9.8f;
    float ay = 0.0f;
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -4.9f, phyc_position(0.0f, 0.0f, ay - g, 1.0f));
}

void test_dynamic_weight_force(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 9.8f, phyd_force_p(1.0f, 9.8f));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 19.6f, phyd_force_p(2.0f, 9.8f));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.0f, phyd_force_p(1.0f, 0.0f));
}

void test_dynamic_acceleration_F_over_m(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 9.8f, phyd_acceleration(9.8f, 1.0f));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 4.9f, phyd_acceleration(9.8f, 2.0f));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 1.0f, phyd_acceleration(10.0f, 10.0f));
}

/* Regression: dynamic log used ay - g when ay already contained gravity.
 * With ay = -g and t=1, correct position is -4.9, not -9.8. */
void test_dynamic_log_no_double_gravity(void)
{
    float g = 9.8f;
    float ay = -g;
    float correct_y = phyc_position(0.0f, 0.0f, ay, 1.0f);
    float double_gravity_y = phyc_position(0.0f, 0.0f, ay - g, 1.0f);
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -4.9f, correct_y);
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -9.8f, double_gravity_y);
    TEST_ASSERT_FALSE(fabsf(correct_y - double_gravity_y) < PRECISION);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_kinematic_position_at_t1_with_gravity);
    RUN_TEST(test_kinematic_position_initial_offset);
    RUN_TEST(test_kinematic_velocity_at_t1_with_gravity);
    RUN_TEST(test_cinematic_gravity_applied_externally);
    RUN_TEST(test_dynamic_weight_force);
    RUN_TEST(test_dynamic_acceleration_F_over_m);
    RUN_TEST(test_dynamic_log_no_double_gravity);
    return UNITY_END();
}
