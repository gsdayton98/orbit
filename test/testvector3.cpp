// -*- mode: c++ -*-
////
// @copyright 2023$
//  Glen Dayton, new account
//
//  Main application entry point
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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#pragma clang diagnostic pop

#include <boost/test/unit_test.hpp>
#include "vector3.hpp"

using numutil::Vector3;

BOOST_AUTO_TEST_SUITE(vector3_suite)

    BOOST_AUTO_TEST_CASE(default_constructor)
    {
        Vector3<float> defaultConstructed;

        BOOST_CHECK_EQUAL(defaultConstructed.size(), 3);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[0], 0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[1], 0);
        BOOST_CHECK_EQUAL(defaultConstructed.get()[2], 0);
    }

    BOOST_AUTO_TEST_CASE(array_constructed)
    {
        Vector3<float> constructed = {1.0F, 2.0F, 3.0F};
        BOOST_CHECK_EQUAL(constructed.size(), 3);
        BOOST_CHECK_EQUAL(constructed.get()[0], 1.0f);
        BOOST_CHECK_EQUAL(constructed.get()[1], 2.0f);
        BOOST_CHECK_EQUAL(constructed.get()[2], 3.0f);
    }

    BOOST_AUTO_TEST_CASE(copy_constructed)
    {
        Vector3<float> constructed = {1.0f, 2.0f, 3.0f};
        Vector3<float> copyConstructed{constructed};
        BOOST_CHECK_EQUAL(copyConstructed.size(), 3);
        BOOST_CHECK_EQUAL(copyConstructed.get()[0], 1.0f);
        BOOST_CHECK_EQUAL(copyConstructed.get()[1], 2.0f);
        BOOST_CHECK_EQUAL(copyConstructed.get()[2], 3.0f);
    }


    BOOST_AUTO_TEST_CASE(assign_plus)
    {
        Vector3<float> left = {1.0f, 2.0f, 3.0f};
        Vector3<float> right = {2.0f, 3.0f, 4.0f};
        left += right;

        BOOST_CHECK_EQUAL(left.get()[0], 3.0f);
        BOOST_CHECK_EQUAL(left.get()[1], 5.0f);
        BOOST_CHECK_EQUAL(left.get()[2], 7.0f);
    }


    BOOST_AUTO_TEST_CASE(assign_minus)
    {
        Vector3<float> left = {1.0f, 2.0f, 3.0f};
        Vector3<float> right = {2.0f, 3.0f, 4.0f};
        left -= right;

        BOOST_CHECK_EQUAL(left.get()[0], -1.0f);
        BOOST_CHECK_EQUAL(left.get()[1], -1.0f);
        BOOST_CHECK_EQUAL(left.get()[2], -1.0f);
    }


    BOOST_AUTO_TEST_CASE(binary_plus)
    {
        constexpr float f[] = {1.0f, 2.0f, 3.0f};
        Vector3<float> left{f};

        constexpr float g[] = {2.0f, 3.0f, 4.0f};
        Vector3<float> right{g};

        auto summand = left + right;

        BOOST_CHECK_EQUAL(summand.get()[0], 3.0f);
        BOOST_CHECK_EQUAL(summand.get()[1], 5.0f);
        BOOST_CHECK_EQUAL(summand.get()[2], 7.0f);
    }


    BOOST_AUTO_TEST_CASE(binary_minus)
    {
        constexpr float f[] = {1.0f, 2.0f, 3.0f};
        Vector3<float> left{f};

        constexpr float g[] = {2.0f, 3.0f, 4.0f};
        Vector3<float> right{g};

        auto summand = left - right;

        BOOST_CHECK_EQUAL(summand.get()[0], -1.0f);
        BOOST_CHECK_EQUAL(summand.get()[1], -1.0f);
        BOOST_CHECK_EQUAL(summand.get()[2], -1.0f);
    }


    BOOST_AUTO_TEST_CASE(assign_scalar_product)
    {
        constexpr float f[] = {1.0f, 2.0f, 3.0f};
        Vector3<float> left{f};

        left *= 2.0f;

        BOOST_CHECK_EQUAL(left.get()[0], 2.0f);
        BOOST_CHECK_EQUAL(left.get()[1], 4.0f);
        BOOST_CHECK_EQUAL(left.get()[2], 6.0f);
    }


    BOOST_AUTO_TEST_CASE(scalar_product)
    {
        constexpr float f[] = {1.0f, 2.0f, 3.0f};
        Vector3<float> v{f};
        float c = 2.0f;

        auto w = v*c;
        auto u = c*v;

        BOOST_CHECK_EQUAL(w.get()[0], 2.0f);
        BOOST_CHECK_EQUAL(w.get()[1], 4.0f);
        BOOST_CHECK_EQUAL(w.get()[2], 6.0f);

        BOOST_CHECK_EQUAL(w.get()[0], u.get()[0]);
        BOOST_CHECK_EQUAL(w.get()[1], u.get()[1]);
        BOOST_CHECK_EQUAL(w.get()[2], u.get()[2]);
    }


    BOOST_AUTO_TEST_CASE(dot_product)
    {
        Vector3<float> u = {1.0f, 2.0f, 3.0f};
        Vector3<float> v = {1.0f, 0.5f, 0.33333333f};
        Vector3<float> w = {-3.0f, 0.0f, 1.0f};

        auto duv = u*v;
        BOOST_CHECK_CLOSE(duv, 3.0f, 1.0e-8f);
        auto duw = u*w;
        BOOST_CHECK_EQUAL(duw, 0.0f);
    }


    BOOST_AUTO_TEST_CASE(norm_test)
    {
        Vector3<float> u = {3.0f, 4.0f, 0.0f};

        auto normV = u.norm();
        BOOST_CHECK_CLOSE(normV, 5.0f, 1.0e-8f);

        auto uUnit = u.unit();
        BOOST_CHECK_CLOSE(uUnit.norm(), 1.0f, 1.0e-08f);
        BOOST_CHECK_CLOSE(uUnit*u, u.norm(), 1.0e-08);
    }


    BOOST_AUTO_TEST_CASE(cross_test)
    {
        Vector3<float> u = {1.0f, 2.0f, 3.0f};
        Vector3<float> v = {0.0f, 1.0f, 0.0f};
        Vector3<float> expected = {-3.0f, 0.0f, 1.0f};

        auto w = Vector3<float>::cross(u, v);

        BOOST_CHECK_CLOSE(u*w, 0.0f, 1.0e-8f);
        BOOST_CHECK_CLOSE(v*w, 0.0f, 1.0e-8f);

        BOOST_CHECK_CLOSE( ((w - expected)*(w-expected)), 0.0f, 1.0e-8f );
    }


    BOOST_AUTO_TEST_CASE(angle_test)
    {
        auto pi = 3.14159265358979F;
        Vector3<float> u = {1.0f, 0.0f, 0.0f};

        for (auto expectedAngle = 0.0f; expectedAngle <= pi; expectedAngle += pi/6.0f)
        {
            Vector3<float> v = {std::cos(expectedAngle), std::sin(expectedAngle), 0.0f};
            auto theta = u.angle(v);
            BOOST_CHECK_CLOSE(theta, expectedAngle, 1.0e-8f);
        }
    }

BOOST_AUTO_TEST_SUITE_END()


