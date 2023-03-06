// -*- mode: c++ -*-
////
// Created by Glen Dayton, new account on 2/28/23.
//
// StateVector and KeplerianElements classes for representing an orbit and determining the Keplerian elements and
// converting to and from a state vector of inertial position and velocity.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef ORBIT_ORBIT_HPP
#define ORBIT_ORBIT_HPP

#include "constants.hpp"
#include "vector3.hpp"

namespace orbit {
    template<typename ScalarType>
    class StateVector {
    public:
        typedef numutil::Vector3<ScalarType> vector3;

        vector3 r;
        vector3 v;

        StateVector(const vector3 &r0, const vector3 &v0) : r{r0}, v{v0}
        {}

        StateVector(const std::initializer_list<ScalarType> &r0, const std::initializer_list<ScalarType> &v0)
                : r{r0},
                  v{v0}
        {}

        auto radialVelocity() const -> ScalarType
        { return v*r.unit(); }

        auto angularMomentum() const -> auto
        { return r.cross(v); }

        auto specificAngularMomentum() const -> ScalarType
        { angularMomentum().norm(); }
    };

    template<typename ScalarType>
    class KeplerianElements {
    public:
        ScalarType semiMajorAxis;   // In dimension derived from mu;
        ScalarType eccentricity;    // dimensionless
        ScalarType inclination;     // radians
        ScalarType rightAscensionAscendingNode; // radians
        ScalarType argumentOfPeriapsis; // radians
        ScalarType trueAnomaly; // radians

        KeplerianElements(ScalarType a, ScalarType e, ScalarType i, ScalarType bigOmega, ScalarType littleOmega,
                          ScalarType nu, ScalarType mu0 = orbit::muEarth)
                :   semiMajorAxis{a},
                    eccentricity{e},
                    inclination{i},
                    rightAscensionAscendingNode{bigOmega},
                    argumentOfPeriapsis{littleOmega},
                    trueAnomaly{nu},
                    mu{mu0}
        {}

    private:
        const ScalarType mu;
    };
}

#endif //ORBIT_ORBIT_HPP
#pragma clang diagnostic pop