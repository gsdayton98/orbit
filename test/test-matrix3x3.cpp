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
        Matrix3x3<float> defaultConstructed;

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
        Matrix3x3<float> constructed{5.289934140020225F, 2.165043638879379F, 3.3269406035854874F};

        auto m = constructed.get();
        BOOST_CHECK_CLOSE(m[0][0], -0.450173f, 1.0e-04f);
        BOOST_CHECK_CLOSE(m[0][1], -0.561656f, 1.0e-04f);
        BOOST_CHECK_CLOSE(m[0][2], -0.694181f, 1.0e-04f);
        BOOST_CHECK_CLOSE(m[1][0], -0.879789f, 1.0e-04f);
        BOOST_CHECK_CLOSE(m[1][1],  0.146046415f, 1.0e-04f);
        BOOST_CHECK_CLOSE(m[1][2],  0.452374f, 1.0e-04f);
        BOOST_CHECK_CLOSE(m[2][0], -0.152696f, 1.0e-04f);
        BOOST_CHECK_CLOSE(m[2][1],  0.814379f, 1.0e-04f);
        BOOST_CHECK_CLOSE(m[2][2], -0.559885f, 1.0e-04f);
    }

    BOOST_AUTO_TEST_CASE(transform_test)
    {
        Matrix3x3<float> m{5.289934140020225F, 2.165043638879379F, 3.3269406035854874F};
        Vector3<float> v = {-8.11772E6F, 3.01706E6F, 0.0F};

        auto w = m.transform(v);
        BOOST_CHECK_CLOSE(w.get()[0], 1.0e6F, 1.0e-5f);
        BOOST_CHECK_CLOSE(w.get()[1], 5.0e6F, 1.0e-5f);
        BOOST_CHECK_CLOSE(w.get()[2], 7.0e6F, 1.0e-5f);
    }
BOOST_AUTO_TEST_SUITE_END()
