// -*- mode: c++ -*-
////
// @copyright 2023$
//  Glen Dayton, new account
//
// Test orbit::
//
// Part of the orbit test suite
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define BOOST_TEST_DYN_LINK
#pragma clang diagnostic pop

#include <boost/test/unit_test.hpp>
#include "constants.hpp"
#include "orbit.hpp"
#include "vector3.hpp"

using vector3 = numutil::Vector3<float>;
using namespace orbit;

BOOST_AUTO_TEST_SUITE(orbit_suite)

    BOOST_AUTO_TEST_CASE(kepler_constructor_test) {
        auto a = 26.61027E6F; // meters
        auto e = 0.74F;
        auto i = 1.1065387F; // radians (63.4 degrees)
        auto argPeriapsis = 2.3561945F; // radians
        auto rightAscensionAscendingNode = 4.4413224F; // radians
        auto trueAnomaly = 1.0471976F; // radians

        KeplerianElements elements{a, e, i, rightAscensionAscendingNode, argPeriapsis, trueAnomaly};
        BOOST_CHECK_CLOSE(elements.semiMajorAxis, a, 1.0e-05f);
        BOOST_CHECK_CLOSE(elements.eccentricity, e, 1.0e-05f);
        BOOST_CHECK_CLOSE(elements.inclination, i, 1.0e-05f);
        BOOST_CHECK_CLOSE(elements.rightAscensionAscendingNode, rightAscensionAscendingNode, 1.0e-05f);
        BOOST_CHECK_CLOSE(elements.argumentOfPeriapsis, argPeriapsis, 1.0e-5f);
        BOOST_CHECK_CLOSE(elements.trueAnomaly, trueAnomaly, 1.0e-05f);
        BOOST_CHECK_CLOSE(elements.gravitationalConstant(), static_cast<float>(orbit::muEarth), 1.0e-05f);
    }

BOOST_AUTO_TEST_SUITE_END()

