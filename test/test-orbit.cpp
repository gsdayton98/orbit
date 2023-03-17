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


    BOOST_AUTO_TEST_CASE(stateVector_constructor_test) {
        vector3 position {1.2915326E+06F, 8.4505435E+06F, -2.033574E+06F}; // Meters
        vector3 velocity {-3289.3377F, 2493.4338F, -7662.0529F}; // Meters/seconds

        StateVector state{position, velocity};
        BOOST_CHECK_CLOSE(state.r[0], 1.2915326E+06F, 1.0e-05F);
        BOOST_CHECK_CLOSE(state.r[1], 8.4505435E+06F, 1.0e-05F);
        BOOST_CHECK_CLOSE(state.r[2], -2.033574E+06F, 1.0e-05F);
        BOOST_CHECK_CLOSE(state.v[0], -3289.3377F, 1.0e-05F);
        BOOST_CHECK_CLOSE(state.v[1], 2493.4338F, 1.0e-05F);
        BOOST_CHECK_CLOSE(state.v[2], -7662.0529F, 1.0e-05F);

        StateVector state2{ {position[0], position[1], position[2]},
                            {velocity[0], velocity[1], velocity[2]}};
        BOOST_CHECK_CLOSE( (state.r - state2.r)*(state.r - state2.r), 0.0F, 1.0e-05F);
        BOOST_CHECK_CLOSE( (state.v - state2.v)*(state.v - state2.v), 0.0F, 1.0e-05F);
    }


    BOOST_AUTO_TEST_CASE(kepler_to_state_vector_test) {
        auto a = 26.61027E6F; // meters
        auto e = 0.74F;
        auto i = 1.1065387F; // radians (63.4 degrees)
        auto argPeriapsis = 2.3561945F; // radians
        auto rightAscensionAscendingNode = 4.4413224F; // radians
        auto trueAnomaly = 1.0471976F; // radians

        KeplerianElements elements{a, e, i, rightAscensionAscendingNode, argPeriapsis, trueAnomaly,
                                   static_cast<float>(orbit::muEarth)};
        StateVector state{elements};

        vector3 position {1.2915326E+06F, 8.4505435E+06F, -2.033574E+06F}; // Meters
        vector3 velocity {-3289.3377f, 2493.4338f, -7662.0529f}; // Meters/seconds

        BOOST_CHECK_CLOSE(state.r[0], position[0], 1.0e-04F);
        BOOST_CHECK_CLOSE(state.r[1], position[1], 1.0e-04F);
        BOOST_CHECK_CLOSE(state.r[2], position[2], 1.0e-04F);
        BOOST_CHECK_CLOSE(state.v[0], velocity[0], 5.0e-03F);
        BOOST_CHECK_CLOSE(state.v[1], velocity[1], 5.0e-03F);
        BOOST_CHECK_CLOSE(state.v[2], velocity[2], 5.0e-03F);
    }


    BOOST_AUTO_TEST_CASE(state_vector_methods_test) {
        StateVector state{{1.2915326E+06F, 8.4505435E+06F, -2.033574E+06F},
                          {-3289.3377f, 2493.4338f, -7662.0529f}};

        auto rVelocity = state.radialVelocity();
        BOOST_CHECK_CLOSE_FRACTION(rVelocity, 3687.62256F, 1.0E-3F);

        auto momentum = state.angularMomentum();
        vector3 expected {-5.96779e+10F, 1.65849e+10F, 3.1017e+10F};
        auto dif = momentum - expected;
        auto metric = dif*dif;
        // Single precision renders this test meaningless.
        BOOST_CHECK(metric < 1.0e10f);

        auto specMomentum = state.specificAngularMomentum();
        auto expectedSpecificMomentum = std::sqrt(momentum*momentum);
        BOOST_CHECK_CLOSE(specMomentum, expectedSpecificMomentum, 1.0F);
    }

BOOST_AUTO_TEST_SUITE_END()

