#include "unity/unity.h"
#include "unity/unity_internals.h"
#include "math.h"
#include "../src/model/phy_forms_dynamics.h"
#include "../src/model/phy_forms_cinematics.h"

#define PRECISION 0.001
#define M_PI 3.14159265358979323846

void setUp(void) {}

void tearDown(void) {}

void test_position(void)
{
    TEST_ASSERT_EQUAL_FLOAT(66, phyc_position(1, 3, 4, 5));
    TEST_ASSERT_EQUAL_FLOAT(8, phyc_position(4, 3, 2, 1));
    TEST_ASSERT_EQUAL_FLOAT(8452, phyc_position(4, 8, 16, 32));
    TEST_ASSERT_EQUAL_FLOAT(4.5, phyc_position(0.5, 3, 2, 1));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 15, phyc_position(3, 0.5, 10, 1.5));
}

void test_velocity(void)
{
    TEST_ASSERT_EQUAL_FLOAT(11, phyc_velocity(1, 2, 5));
    TEST_ASSERT_EQUAL_FLOAT(7, phyc_velocity(5, 2, 1));
    TEST_ASSERT_EQUAL_FLOAT(132, phyc_velocity(4, 8, 16));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 18.745, phyc_velocity(5.6, 2.32, 5.666));
    TEST_ASSERT_EQUAL_FLOAT(16, phyc_velocity(14, 2, 1));
}

void test_medium_velocity(void)
{
    TEST_ASSERT_EQUAL_FLOAT(2, phyc_medium_velocity(0, 10, 0, 5));
    TEST_ASSERT_EQUAL_FLOAT(1, phyc_medium_velocity(1, 2, 3, 4));
    TEST_ASSERT_EQUAL_FLOAT(1, phyc_medium_velocity(4, 3, 2, 1));
    TEST_ASSERT_EQUAL_FLOAT(0.25, phyc_medium_velocity(2, 4, 8, 16));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2.5, phyc_medium_velocity(10, 5, 2.5, 0.5));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.726, phyc_medium_velocity(13, 7, 9, 0.737));
}

void test_medium_acceleration(void)
{
    TEST_ASSERT_EQUAL_FLOAT(5, phyc_medium_acceleration(5, 15, 2));
    TEST_ASSERT_EQUAL_FLOAT(0, phyc_medium_acceleration(10, 10, 10));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 4.666, phyc_medium_acceleration(1, 15, 3));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.415, phyc_medium_acceleration(0, 32, 77));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.4396, phyc_medium_acceleration(2.5, 7.776, 12));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 16.915, phyc_medium_acceleration(0, 80.35, 4.75));
}

void test_magnitude(void)
{
    TEST_ASSERT_EQUAL_FLOAT(5, phyc_magnitude(3, 4));
    TEST_ASSERT_EQUAL_FLOAT(5, phyc_magnitude(4, 3));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 22.360, phyc_magnitude(10, 20));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 15.811, phyc_magnitude(15, 5));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 42.151, phyc_magnitude(42, 3.5653));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2.692, phyc_magnitude(2.5, 1));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2, phyc_magnitude(2, 0));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 1.414, phyc_magnitude(1, 1));
}

void test_displacement_x_y(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 4.123, phyc_displacement_x_y(3, 4, 2, 6));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 14.142, phyc_displacement_x_y(10, 20, 20, 10));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 14.142, phyc_displacement_x_y(5, 15, 5, 15));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 3.383, phyc_displacement_x_y(2, 3.565, 2, 5));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 10.111, phyc_displacement_x_y(2.5, 1, 10, 20));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 6.324, phyc_displacement_x_y(2, 0, 0, 6));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2, phyc_displacement_x_y(1, 1, 2, 4));
}

void test_magnitude_velocity(void)
{

    TEST_ASSERT_EQUAL_FLOAT(5, phyc_magnitude_velocity(3, 4));
    TEST_ASSERT_EQUAL_FLOAT(5, phyc_magnitude_velocity(4, 3));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 22.360, phyc_magnitude_velocity(10, 20));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 15.811, phyc_magnitude_velocity(15, 5));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 42.151, phyc_magnitude_velocity(42, 3.5653));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2.692, phyc_magnitude_velocity(2.5, 1));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2, phyc_magnitude_velocity(2, 0));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 1.414, phyc_magnitude_velocity(1, 1));
}

void test_magnitude_acceleration(void)
{
    TEST_ASSERT_EQUAL_FLOAT(5, phyc_magnitude_acceleration(3, 4));
    TEST_ASSERT_EQUAL_FLOAT(5, phyc_magnitude_acceleration(4, 3));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 22.360, phyc_magnitude_acceleration(10, 20));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 15.811, phyc_magnitude_acceleration(15, 5));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 42.151, phyc_magnitude_acceleration(42, 3.5653));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2.692, phyc_magnitude_acceleration(2.5, 1));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2, phyc_magnitude_acceleration(2, 0));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 1.414, phyc_magnitude_acceleration(1, 1));
}

void test_decompose_x(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 1, phyc_decompose_x(1, phyc_degree_to_radian(0)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.866, phyc_decompose_x(1, phyc_degree_to_radian(30)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.5, phyc_decompose_x(1, phyc_degree_to_radian(60)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.0, phyc_decompose_x(1, phyc_degree_to_radian(90)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -0.5, phyc_decompose_x(1, phyc_degree_to_radian(120)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -1, phyc_decompose_x(1, phyc_degree_to_radian(180)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0, phyc_decompose_x(1, phyc_degree_to_radian(270)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 1, phyc_decompose_x(1, phyc_degree_to_radian(360)));
}

void test_decompose_y(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0, phyc_decompose_y(1, phyc_degree_to_radian(0)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.5, phyc_decompose_y(1, phyc_degree_to_radian(30)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.866, phyc_decompose_y(1, phyc_degree_to_radian(60)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 1, phyc_decompose_y(1, phyc_degree_to_radian(90)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.866, phyc_decompose_y(1, phyc_degree_to_radian(120)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0, phyc_decompose_y(1, phyc_degree_to_radian(180)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -0.866, phyc_decompose_y(1, phyc_degree_to_radian(240)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -1, phyc_decompose_y(1, phyc_degree_to_radian(270)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0, phyc_decompose_y(1, phyc_degree_to_radian(360)));
}
void test_angle(void)
{
    TEST_ASSERT_EQUAL_FLOAT(M_PI / 4, phyc_angle(1, 1));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 1.570, phyc_angle(0, 1));
    TEST_ASSERT_EQUAL_FLOAT(-(M_PI / 4), phyc_angle(1, -1));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, -1.249, phyc_angle(1, -3));
}

void test_degree_to_radian(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0, phyc_degree_to_radian(0));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, M_PI / 6, phyc_degree_to_radian(30));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, M_PI / 4, phyc_degree_to_radian(45));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, M_PI / 3, phyc_degree_to_radian(60));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, M_PI / 2, phyc_degree_to_radian(90));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, M_PI, phyc_degree_to_radian(180));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 3 * M_PI / 2, phyc_degree_to_radian(270));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 2 * M_PI, phyc_degree_to_radian(360));
}

void test_radian_to_degree(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0, phyc_radian_to_degree(0));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 30, phyc_radian_to_degree(M_PI / 6));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 45, phyc_radian_to_degree(M_PI / 4));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 60, phyc_radian_to_degree(M_PI / 3));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 90, phyc_radian_to_degree(M_PI / 2));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 180, phyc_radian_to_degree(M_PI));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 270, phyc_radian_to_degree(3 * M_PI / 2));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 360, phyc_radian_to_degree(2 * M_PI));
}

void test_phyd_force_p(void)
{
    TEST_ASSERT_EQUAL_FLOAT(98.0, phyd_force_p(10.0, 9.8));
    TEST_ASSERT_EQUAL_FLOAT(0.0, phyd_force_p(0.0, 9.8));
    TEST_ASSERT_EQUAL_FLOAT(196.0, phyd_force_p(20.0, 9.8));
}

void test_phyd_force_r(void)
{
    TEST_ASSERT_EQUAL_FLOAT(20.0, phyd_force_r(10.0, 2.0));
    TEST_ASSERT_EQUAL_FLOAT(0.0, phyd_force_r(10.0, 0.0));
    TEST_ASSERT_EQUAL_FLOAT(50.0, phyd_force_r(25.0, 2.0));
}

void test_phyd_decompose_force_x(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 7.071, phyd_decompose_force_x(10, phyc_degree_to_radian(45))); 
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 10.0, phyd_decompose_force_x(10, phyc_degree_to_radian(0))); 
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.0, phyd_decompose_force_x(10, phyc_degree_to_radian(90))); 
}

void test_phyd_decompose_force_y(void)
{
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 7.071, phyd_decompose_force_y(10, phyc_degree_to_radian(45))); 
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 0.0, phyd_decompose_force_y(10, phyc_degree_to_radian(0)));
    TEST_ASSERT_FLOAT_WITHIN(PRECISION, 10.0, phyd_decompose_force_y(10, phyc_degree_to_radian(90))); 
}

void test_phyd_acceleration(void)
{
    TEST_ASSERT_EQUAL_FLOAT(2.0, phyd_acceleration(20.0, 10.0));
    TEST_ASSERT_EQUAL_FLOAT(0.0, phyd_acceleration(0.0, 10.0));
    TEST_ASSERT_EQUAL_FLOAT(1.5, phyd_acceleration(15.0, 10.0));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_position);
    RUN_TEST(test_velocity);
    RUN_TEST(test_medium_velocity);
    RUN_TEST(test_medium_acceleration);
    RUN_TEST(test_magnitude);
    RUN_TEST(test_displacement_x_y);
    RUN_TEST(test_magnitude_velocity);
    RUN_TEST(test_magnitude_acceleration);
    RUN_TEST(test_decompose_x);
    RUN_TEST(test_decompose_y);
    RUN_TEST(test_angle);
    RUN_TEST(test_degree_to_radian);
    RUN_TEST(test_radian_to_degree);
    RUN_TEST(test_phyd_force_p);
    RUN_TEST(test_phyd_force_r);
    RUN_TEST(test_phyd_decompose_force_x);
    RUN_TEST(test_phyd_decompose_force_y);
    RUN_TEST(test_phyd_acceleration);
    UNITY_END();
    return 0;
}