// -*- mode: c++ -*-
////
// @copyright 2023$
//  Glen Dayton, new account
//
//  Main application entry point for tests
//  
//  @param argc The number of elements in the argv array
//  @param argv The command line arguments passed to the
//              application
//  
//  @return Completion code, typically 0 for success
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define BOOST_TEST_MODULE Test orbit
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#pragma clang diagnostic pop

#include <boost/test/unit_test.hpp>
#include <numbers>
#include "vector3.hpp"

using numutil::Vector3;
using namespace std::numbers;


BOOST_AUTO_TEST_SUITE(vector3_suite)

    BOOST_AUTO_TEST_CASE(default_constructor)
    {
        Vector3<double> defaultConstructed;

        BOOST_CHECK_EQUAL(defaultConstructed.size(), 3);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[0], 0.);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[1], 0.);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[2], 0.);
    }

    BOOST_AUTO_TEST_CASE(array_constructed)
    {
        Vector3<double> constructed = {1.0, 2.0, 3.0};
        BOOST_CHECK_EQUAL(constructed.size(), 3);
        BOOST_CHECK_EQUAL(constructed.get()[0], 1.0);
        BOOST_CHECK_EQUAL(constructed.get()[1], 2.0);
        BOOST_CHECK_EQUAL(constructed.get()[2], 3.0);
    }

    BOOST_AUTO_TEST_CASE(copy_constructed)
    {
        Vector3<double> constructed = {1.0, 2.0, 3.0};
        Vector3<double> copyConstructed{constructed};
        BOOST_CHECK_EQUAL(copyConstructed.size(), 3);
        BOOST_CHECK_EQUAL(copyConstructed.get()[0], 1.0);
        BOOST_CHECK_EQUAL(copyConstructed.get()[1], 2.0);
        BOOST_CHECK_EQUAL(copyConstructed.get()[2], 3.0);
    }


    BOOST_AUTO_TEST_CASE(assign_plus)
    {
        Vector3<double> left = {1.0, 2.0, 3.0};
        Vector3<double> right = {2.0, 3.0, 4.0};
        left += right;

        BOOST_CHECK_EQUAL(left.get()[0], 3.0);
        BOOST_CHECK_EQUAL(left.get()[1], 5.0);
        BOOST_CHECK_EQUAL(left.get()[2], 7.0);
    }


    BOOST_AUTO_TEST_CASE(assign_minus)
    {
        Vector3<double> left = {1.0, 2.0, 3.0};
        Vector3<double> right = {2.0, 3.0, 4.0};
        left -= right;

        BOOST_CHECK_EQUAL(left.get()[0], -1.0);
        BOOST_CHECK_EQUAL(left.get()[1], -1.0);
        BOOST_CHECK_EQUAL(left.get()[2], -1.0);
    }


    BOOST_AUTO_TEST_CASE(binary_plus)
    {
        constexpr double f[] = {1.0, 2.0, 3.0};
        Vector3<double> left{f};

        constexpr double g[] = {2.0, 3.0, 4.0};
        Vector3<double> right{g};

        auto summand = left + right;

        BOOST_CHECK_EQUAL(summand.get()[0], 3.0);
        BOOST_CHECK_EQUAL(summand.get()[1], 5.0);
        BOOST_CHECK_EQUAL(summand.get()[2], 7.0);
    }


    BOOST_AUTO_TEST_CASE(binary_minus)
    {
        constexpr double f[] = {1.0, 2.0, 3.0};
        Vector3<double> left{f};

        constexpr double g[] = {2.0, 3.0, 4.0};
        Vector3<double> right{g};

        auto summand = left - right;

        BOOST_CHECK_EQUAL(summand.get()[0], -1.0);
        BOOST_CHECK_EQUAL(summand.get()[1], -1.0);
        BOOST_CHECK_EQUAL(summand.get()[2], -1.0);
    }


    BOOST_AUTO_TEST_CASE(assign_scalar_product)
    {
        constexpr double f[] = {1.0, 2.0, 3.0};
        Vector3<double> left{f};

        left *= 2.0;

        BOOST_CHECK_EQUAL(left.get()[0], 2.0);
        BOOST_CHECK_EQUAL(left.get()[1], 4.0);
        BOOST_CHECK_EQUAL(left.get()[2], 6.0);
    }


    BOOST_AUTO_TEST_CASE(scalar_product)
    {
        constexpr double f[] = {1.0, 2.0, 3.0};
        Vector3<double> v{f};
        double c = 2.0;

        auto w = v*c;
        auto u = c*v;

        BOOST_CHECK_EQUAL(w.get()[0], 2.0);
        BOOST_CHECK_EQUAL(w.get()[1], 4.0);
        BOOST_CHECK_EQUAL(w.get()[2], 6.0);

        BOOST_CHECK_EQUAL(w.get()[0], u.get()[0]);
        BOOST_CHECK_EQUAL(w.get()[1], u.get()[1]);
        BOOST_CHECK_EQUAL(w.get()[2], u.get()[2]);
    }


    BOOST_AUTO_TEST_CASE(dot_product)
    {
        Vector3<double> u = {1.0, 2.0, 3.0};
        Vector3<double> v = {1.0, 0.5, 1.0/3.0};
        Vector3<double> w = {-3.0, 0.0, 1.0};

        auto duv = u*v;
        BOOST_CHECK_CLOSE(duv, 3.0, 1.0e-15);
        auto duw = u*w;
        BOOST_CHECK_EQUAL(duw, 0.0);
    }


    BOOST_AUTO_TEST_CASE(norm_test)
    {
        Vector3<double> u = {3.0, 4.0, 0.0};

        auto normV = u.norm();
        BOOST_CHECK_CLOSE(normV, 5.0, 1.0e-15);

        auto uUnit = u.unit();
        BOOST_CHECK_CLOSE(uUnit.norm(), 1.0, 1.0e-15);
        BOOST_CHECK_CLOSE(uUnit*u, u.norm(), 1.0e-15);
    }


    BOOST_AUTO_TEST_CASE(cross_test)
    {
        Vector3<double> u = {1.0, 2.0, 3.0};
        Vector3<double> v = {0.0, 1.0, 0.0};
        Vector3<double> expected = {-3.0, 0.0, 1.0};

        auto w = u.cross(v);

        BOOST_CHECK_CLOSE(u*w, 0.0, 1.0e-15);
        BOOST_CHECK_CLOSE(v*w, 0.0, 1.0e-15);

        BOOST_CHECK_CLOSE( ((w - expected)*(w-expected)), 0.0, 1.0e-15);
    }


    BOOST_AUTO_TEST_CASE(angle_test)
    {
        Vector3<double> u = {1.0, 0.0, 0.0};

        auto expectedAngle = 0.0;
        while (expectedAngle <= pi)
        {
            Vector3<double> v = {std::cos(expectedAngle), std::sin(expectedAngle), 0.0};
            auto theta = u.angle(v);
            BOOST_CHECK_CLOSE(theta, expectedAngle, 1.0e-15);
            expectedAngle += pi/6.0;
        }
    }

BOOST_AUTO_TEST_SUITE_END()


