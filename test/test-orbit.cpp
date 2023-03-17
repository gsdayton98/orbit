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
#include <numbers>
#include "constants.hpp"
#include "orbit.hpp"
#include "vector3.hpp"

using vector3 = numutil::Vector3<double>;
using namespace orbit;
using namespace std::numbers;


BOOST_AUTO_TEST_SUITE(orbit_suite)

    BOOST_AUTO_TEST_CASE(kepler_constructor_test) {
        auto a = 26.61027E6; // meters
        auto e = 0.74;
        auto i = (63.4/180.0)*pi; // radians (63.4 degrees)
        auto argPeriapsis = 3.0*pi/4.0; // radians
        auto rightAscensionAscendingNode = 4.4413224; // radians
        auto trueAnomaly = 1.0471976; // radians

        KeplerianElements elements{a, e, i, rightAscensionAscendingNode, argPeriapsis, trueAnomaly};
        BOOST_CHECK_CLOSE(elements.semiMajorAxis, a, 1.0e-15);
        BOOST_CHECK_CLOSE(elements.eccentricity, e, 1.0e-15);
        BOOST_CHECK_CLOSE(elements.inclination, i, 1.0e-15);
        BOOST_CHECK_CLOSE(elements.rightAscensionAscendingNode, rightAscensionAscendingNode, 1.0e-15);
        BOOST_CHECK_CLOSE(elements.argumentOfPeriapsis, argPeriapsis, 1.0e-15);
        BOOST_CHECK_CLOSE(elements.trueAnomaly, trueAnomaly, 1.0e-15);
        BOOST_CHECK_CLOSE(elements.gravitationalConstant(), orbit::muEarth, 1.0e-15);
    }


    BOOST_AUTO_TEST_CASE(stateVector_constructor_test) {
        vector3 position {1.2915326E+06, 8.4505435E+06, -2.033574E+06}; // Meters
        vector3 velocity {-3289.3377, 2493.4338, -7662.0529}; // Meters/seconds

        StateVector state{position, velocity};
        BOOST_CHECK_CLOSE(state.r[0], 1.2915326E+06, 1.0e-15);
        BOOST_CHECK_CLOSE(state.r[1], 8.4505435E+06, 1.0e-15);
        BOOST_CHECK_CLOSE(state.r[2], -2.033574E+06, 1.0e-15);
        BOOST_CHECK_CLOSE(state.v[0], -3289.3377, 1.0e-15);
        BOOST_CHECK_CLOSE(state.v[1], 2493.4338, 1.0e-15);
        BOOST_CHECK_CLOSE(state.v[2], -7662.0529, 1.0e-15);

        StateVector state2{ {position[0], position[1], position[2]},
                            {velocity[0], velocity[1], velocity[2]}};
        BOOST_CHECK_CLOSE( (state.r - state2.r)*(state.r - state2.r), 0.0, 1.0e-15);
        BOOST_CHECK_CLOSE( (state.v - state2.v)*(state.v - state2.v), 0.0, 1.0e-15);
    }


    BOOST_AUTO_TEST_CASE(kepler_to_state_vector_test) {
        auto a = 26.61027E6; // meters
        auto e = 0.74;
        auto i = (63.4/180.0)*pi; // radians (63.4 degrees)
        auto argPeriapsis = 3.0*pi/4.0; // radians
        auto rightAscensionAscendingNode = 4.4413224; // radians
        auto trueAnomaly = 1.0471976; // radians

        KeplerianElements elements{a, e, i, rightAscensionAscendingNode, argPeriapsis, trueAnomaly, orbit::muEarth};
        StateVector state{elements};

        vector3 position {1291532.0426354893, 8450543.8627347574, -2033574.4116763086}; // Meters
        vector3 velocity {-3289.3289675154929, 2493.4266454481167, -7662.0322206791934}; // Meters/seconds

        BOOST_CHECK_CLOSE(state.r[0], position[0], 1.0e-15);
        BOOST_CHECK_CLOSE(state.r[1], position[1], 1.0e-15);
        BOOST_CHECK_CLOSE(state.r[2], position[2], 1.0e-15);
        BOOST_CHECK_CLOSE(state.v[0], velocity[0], 5.0e-15);
        BOOST_CHECK_CLOSE(state.v[1], velocity[1], 5.0e-15);
        BOOST_CHECK_CLOSE(state.v[2], velocity[2], 5.0e-15);
    }


    BOOST_AUTO_TEST_CASE(state_vector_methods_test) {
        StateVector state{{1.2915326E+06, 8.4505435E+06, -2.033574E+06},
                          {-3289.3377, 2493.4338, -7662.0529}};

        auto rVelocity = state.radialVelocity();
        BOOST_CHECK_CLOSE_FRACTION(rVelocity, 3687.62256, 1.0E-3);

        auto momentum = state.angularMomentum();
        vector3 expected {-5.96779e+10, 1.65849e+10, 3.1017e+10};
        auto dif = momentum - expected;
        auto metric = dif*dif;
        // Single precision renders this test meaningless.
        BOOST_CHECK(metric < 1.0e10);

        auto specMomentum = state.specificAngularMomentum();
        auto expectedSpecificMomentum = std::sqrt(momentum*momentum);
        BOOST_CHECK_CLOSE(specMomentum, expectedSpecificMomentum, 1.0);
    }

BOOST_AUTO_TEST_SUITE_END()

