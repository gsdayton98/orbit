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

        static auto semimajorAxis(ScalarType perigee, ScalarType apogee) -> auto { return (perigee + apogee)/ static_cast<ScalarType>(2.0); };
        static auto eccentricityFromPeriApoapsis(ScalarType perigee, ScalarType apogee) -> auto { return (apogee - perigee) / (apogee + perigee); };
        static auto period(ScalarType a, ScalarType mu = orbit::muEarth) -> auto {
            return static_cast<ScalarType>(2.0*std::numbers::pi*std::sqrt(a*a*a/mu));
        }
        static auto semimajorAxisFromPeriod(ScalarType period, ScalarType mu = orbit::muEarth) -> auto {
            auto t = 0.5*period/std::numbers::pi;
            return std::cbrt(mu*t*t);
        }
    private:
        // Because of numerical imprecision return 1 if argument exceeds 1, and -1 if argument is below -1.
        auto clamp(auto arg) -> auto {
            auto result = arg;
            if (result > 1.0) result = 1.0;
            if (result < -1.0) result = -1.0;
            return result;
        }

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
        numutil::Vector3<ScalarType> perifocalPosition {
                perifocalRadius * csTrueAnomaly.real(),
                perifocalRadius * csTrueAnomaly.imag(),
                0.0F};
        numutil::Vector3<ScalarType> perifocalVelocity {
                -csTrueAnomaly.imag(),
                kepler.eccentricity + csTrueAnomaly.real(),
                0.0F};
        perifocalVelocity *= kepler.gravitationalConstant()/specificMomentum;

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
        if (n > 0.0) {
            rightAscensionAscendingNode = std::acos(clamp(nodeVector[0] / n));
        }
        else {
            rightAscensionAscendingNode = 0.0;
        }
        if (nodeVector[1] < 0) {
            rightAscensionAscendingNode = 2.0f*std::numbers::pi - rightAscensionAscendingNode;
        }
        argumentOfPeriapsis = std::acos(clamp(e.dot(nodeVector)/(eccentricity*n)));
        if (e[2] < 0.0f) {
            argumentOfPeriapsis = 2.0f*std::numbers::pi - argumentOfPeriapsis;
        }

        auto rUnit = state.r.unit();
        if (eccentricity > 0.0) {
            trueAnomaly = std::acos(clamp(e.dot(rUnit) / eccentricity));
            if (state.v.dot(rUnit) < 0.0f) {
                trueAnomaly = 2.0f*std::numbers::pi - trueAnomaly;
            }
        } else if (inclination > 0.0 || inclination < 0.0) {
            trueAnomaly = std::acos(clamp(nodeVector.dot(rUnit) / n));
            if (state.r[2] < 0) {
                trueAnomaly = 2.0f*std::numbers::pi - trueAnomaly;
            }
        } else {
            trueAnomaly = std::acos(clamp(state.r[0]/ state.r.norm()));
            if (state.v[0] > 0.0) {
                trueAnomaly = 2.0f*std::numbers::pi - trueAnomaly;
            }
        }
    }

}

#endif //ORBIT_ORBIT_HPP
#pragma clang diagnostic pop