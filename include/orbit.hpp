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

#include <cmath>
#include <complex>
#include <numbers>
#include "constants.hpp"
#include "matrix3x3.hpp"
#include "vector3.hpp"

namespace orbit {
    template<typename ScalarType>
    class KeplerianElements;

    template<typename ScalarType>
    class StateVector {
    public:
        typedef numutil::Vector3<ScalarType> vector3;

        vector3 r;
        vector3 v;

        StateVector(const vector3 &r0, const vector3 &v0) : r{r0}, v{v0} {}

        StateVector(const std::initializer_list<ScalarType> &r0, const std::initializer_list<ScalarType> &v0)
                : r{r0},
                  v{v0} {}

        explicit StateVector(const KeplerianElements<ScalarType> &);

        auto radialVelocity() const -> ScalarType { return v * r.unit(); }

        auto angularMomentum() const -> auto { return r.cross(v); }

        auto specificAngularMomentum() const -> ScalarType { return angularMomentum().norm(); }
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

        auto gravitationalConstant() const { return mu; }

        KeplerianElements(ScalarType a, ScalarType e, ScalarType i, ScalarType bigOmega, ScalarType littleOmega,
                          ScalarType nu, ScalarType mu0 = orbit::muEarth)
                : semiMajorAxis{a},
                  eccentricity{e},
                  inclination{i},
                  rightAscensionAscendingNode{bigOmega},
                  argumentOfPeriapsis{littleOmega},
                  trueAnomaly{nu},
                  mu{mu0} {}

        explicit KeplerianElements(const StateVector<ScalarType> &, ScalarType mu0 = orbit::muEarth);;


    private:
        const ScalarType mu;
    };


    template<typename ScalarType>
    StateVector<ScalarType>::StateVector(const KeplerianElements<ScalarType> &kepler) {
        auto specificMomentum = std::sqrt(kepler.gravitationalConstant() * kepler.semiMajorAxis *
                                          (1.0F - kepler.eccentricity * kepler.eccentricity));
        std::complex<ScalarType> complexTrueAnomaly{0.0F, kepler.trueAnomaly};
        auto csTrueAnomaly = std::exp(complexTrueAnomaly);
        auto perifocalRadius = ((specificMomentum * specificMomentum) / kepler.gravitationalConstant()) /
                               (1.0F + kepler.eccentricity * csTrueAnomaly.real());
        numutil::Vector3<ScalarType> perifocalPosition{
                perifocalRadius * csTrueAnomaly.real(),
                perifocalRadius * csTrueAnomaly.imag(),
                0.0F};
        numutil::Vector3<ScalarType> perifocalVelocity{
                -csTrueAnomaly.imag(),
                kepler.eccentricity + csTrueAnomaly.real(),
                0.0F};

        numutil::Matrix3x3<ScalarType> toInertial{kepler.argumentOfPeriapsis,
                                                  kepler.inclination,
                                                  kepler.rightAscensionAscendingNode};

        r = toInertial.transform(perifocalPosition);
        v = toInertial.transform(perifocalVelocity);
    }

    template<typename ScalarType>
    KeplerianElements<ScalarType>::KeplerianElements(const StateVector<ScalarType> &state, ScalarType mu0) : mu{mu0}
    {
        auto angularMomentum = state.angularMomentum();
        auto hUnit = angularMomentum.unit();
        auto h = angularMomentum.norm();
        auto e = state.v.cross(angularMomentum) - state.r.unit();
        numutil::Vector3<ScalarType> nodeVector{-hUnit[1], hUnit[0], 0.0f};
        auto n = nodeVector.norm();
        eccentricity = e.norm();
        semiMajorAxis = h*h/(mu0*(1 - eccentricity*eccentricity));
        inclination = std::acos(angularMomentum[3]/h);
        rightAscensionAscendingNode = std::acos(nodeVector[0]/n);
        if (nodeVector[1] < 0) {
            rightAscensionAscendingNode = 2.0f*std::numbers::pi - rightAscensionAscendingNode;
        }
        argumentOfPeriapsis = std::acos(e.dot(nodeVector)/(eccentricity*n));
        if (e[2] < 0.0f) {
            argumentOfPeriapsis = 2.0f*std::numbers::pi - argumentOfPeriapsis;
        }
        auto rUnit = state.r.unit();
        trueAnomaly = std::acos(e.dot(rUnit)/(eccentricity));
        if (state.v.dot(rUnit) < 0.0f) {
            trueAnomaly = 2.0f*std::numbers::pi - trueAnomaly;
        }
    }

}

#endif //ORBIT_ORBIT_HPP
#pragma clang diagnostic pop