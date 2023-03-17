// -*- mode: c++ -*-
////
// @copyright 2023$
//  Glen Dayton, new account
//
// Test numutil::Matrix3x3
//
// Part of the orbit test suite
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define BOOST_TEST_DYN_LINK
#pragma clang diagnostic pop

#include <boost/test/unit_test.hpp>
#include "matrix3x3.hpp"
#include "vector3.hpp"

using numutil::Matrix3x3;
using numutil::Vector3;


BOOST_AUTO_TEST_SUITE(matrix3x3_suite)

    BOOST_AUTO_TEST_CASE(default_constructor)
    {
        Matrix3x3<double> defaultConstructed;

        BOOST_CHECK_EQUAL(defaultConstructed.get()[0][0], 1.0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[0][1], 0.0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[0][2], 0.0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[1][0], 0.0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[1][1], 1.0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[1][2], 0.0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[2][0], 0.0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[2][1], 0.0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[2][2], 1.0);
    }


    BOOST_AUTO_TEST_CASE(transfrom_constructor)
    {
        Matrix3x3<double> constructed{5.289934140020225, 2.165043638879379, 3.3269406035854874};

        auto m = constructed.get();
        BOOST_CHECK_CLOSE(m[0][0], -0.45017252305484823, 1.0e-15);
        BOOST_CHECK_CLOSE(m[0][1], -0.56165649727272582, 1.0e-15);
        BOOST_CHECK_CLOSE(m[0][2], -0.69418058065446109, 1.0e-15);
        BOOST_CHECK_CLOSE(m[1][0], -0.87978897316928595, 1.0e-15);
        BOOST_CHECK_CLOSE(m[1][1],  0.14604637564202644, 1.0e-15);
        BOOST_CHECK_CLOSE(m[1][2],  0.45237353907093375, 1.0e-15);
        BOOST_CHECK_CLOSE(m[2][0], -0.15269597956778574, 1.0e-15);
        BOOST_CHECK_CLOSE(m[2][1],  0.81437855769486012, 1.0e-15);
        BOOST_CHECK_CLOSE(m[2][2], -0.55988525841521641, 1.0e-15);
    }


    BOOST_AUTO_TEST_CASE(transform_test)
    {
        Matrix3x3<double> m{5.289934140020225, 2.165043638879379, 3.3269406035854874};
        Vector3<double> v = {-8.11772E6, 3.01706E6, 0.0};

        auto w = m.transform(v);
        // Slack tolerances due to limited digits in input
        BOOST_CHECK_CLOSE(w[0], 1.0e6, 5.0e-4);
        BOOST_CHECK_CLOSE(w[1], 5.0e6, 5.0e-5);
        BOOST_CHECK_CLOSE(w[2], 7.0e6, 5.0e-5);
    }
BOOST_AUTO_TEST_SUITE_END()
