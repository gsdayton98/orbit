// -*- mode: c++ -*-
////
//
// Created by Glen Dayton, new account on 3/5/23.
//
//  3x3 Matrix class implemented solely for perifocal to inertial co-ordinate conversion.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "OCUnusedTypeAliasInspection"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef ORBIT_MATRIX3X3_HPP
#define ORBIT_MATRIX3X3_HPP
#include <complex>
#include "vector3.hpp"

namespace numutil {
    template<typename ScalarType>
    class Matrix3x3 {
    public:
        static const auto numberRows = 3;
        static const auto numberColumns = 3;

        /// Array equivalent of this type
        using matrix3x3type = ScalarType[numberRows][numberColumns];

        /// Element type of this instance
        using elementType = ScalarType;

        /// Alias for this Vector3<ScalarType> instance
        using Matrix3x3Type = Matrix3x3<ScalarType>;

        /// Default constructor produces identity matrix
        Matrix3x3();

        /// Generate Euler matrix for the 3-rotation angles
        Matrix3x3(ScalarType littleOmega, ScalarType inclination, ScalarType bigOmega);

        /// Mostly used for testing purposes
        auto get() -> auto { return m; }

        auto transform(const numutil::Vector3<ScalarType>&) const -> numutil::Vector3<ScalarType>;

    private:
        matrix3x3type m;
    };

    template <typename ScalarType>
    Matrix3x3<ScalarType>::Matrix3x3() : m { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} } {}

    template <typename ScalarType>
    Matrix3x3<ScalarType>::Matrix3x3(ScalarType littleOmega, ScalarType inclination, ScalarType bigOmega)
    {
        std::complex<ScalarType> angle = {0.0, littleOmega};
        std::complex<ScalarType> csLittleOmega = std::exp(angle);
        angle = {0.0, inclination};
        std::complex<ScalarType> csInclination = std::exp(angle);
        angle = {0.0, bigOmega};
        std::complex<ScalarType> csBigOmega = std::exp(angle);

        m[0][0] = csLittleOmega.real()*csBigOmega.real() - csInclination.real()*csLittleOmega.imag()*csBigOmega.imag();
        m[0][1] = csInclination.real()*csBigOmega.real()*csLittleOmega.imag() + csLittleOmega.real()*csBigOmega.imag();
        m[0][2] = csInclination.imag()*csLittleOmega.imag();

        m[1][0] = -csBigOmega.real()*csLittleOmega.imag()- csInclination.real()*csLittleOmega.real()*csBigOmega.imag();
        m[1][1] = csInclination.real()*csLittleOmega.real()*csBigOmega.real() - csLittleOmega.imag()*csBigOmega.imag();
        m[1][2] = csLittleOmega.real()*csInclination.imag();

        m[2][0] = csInclination.imag()*csBigOmega.imag();
        m[2][1] = -csBigOmega.real()*csInclination.imag();
        m[2][2] = csInclination.real();
    }

    template <typename ScalarType>
    auto Matrix3x3<ScalarType>::transform(const numutil::Vector3<ScalarType>& v) const -> numutil::Vector3<ScalarType>
    {
        numutil::Vector3<ScalarType> result;

        result[0] = m[0][0]*v[0] + m[1][0]*v[1] + m[2][0]*v[2];
        result[1] = m[0][1]*v[0] + m[1][1]*v[1] + m[2][1]*v[2];
        result[2] = m[0][2]*v[0] + m[1][2]*v[1] + m[2][2]*v[2];

        return result;
    }


} // numutil
#endif //ORBIT_MATRIX3X3_HPP
#pragma clang diagnostic pop
