// -*- mode: c++ -*-
//
// Created by Glen Dayton, new account on 2/18/23.
//

#ifndef ORBIT_VECTOR3_HPP
#define ORBIT_VECTOR3_HPP
#include <algorithm>
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <stdexcept>

namespace numutil {
    /**
     * Provide basic vector arithmetic operations.
     * @tparam ScalarType Type of vector element. Should support addition, subtraction, scalar multiplication.
     * @tparam length Number of elements in the vectors.
     */
    template<typename ScalarType>
    class Vector3 {
    public:
        static const auto length = 3;
        typedef ScalarType vector_type[length];
        using elementType [[maybe_unused]] = ScalarType;
        using vectorType  [[maybe_unused]] = Vector3<ScalarType>;

        Vector3();
        explicit Vector3(const ScalarType *start);
        Vector3(std::initializer_list<ScalarType> l);

        auto operator+=(const Vector3<ScalarType>&) -> Vector3<ScalarType>&;
        auto operator-=(const Vector3<ScalarType>&) -> Vector3<ScalarType>&;

        /// Scalar*Vector3 product
        /// \return Vector3
        auto operator*=(ScalarType) -> Vector3<ScalarType>&;

        /// sqrt(v*v)
        auto norm() const -> ScalarType;

        /// Unit vector lying in the same direction as the vector.
        /// \return
        [[maybe_unused]]
        auto unit() const -> Vector3<ScalarType>;

        auto get() -> auto { return v; }

        auto size() const -> auto { return 3; }

        [[maybe_unused]]
        static auto cross(const Vector3<ScalarType>&, const Vector3<ScalarType>&) -> Vector3<ScalarType>;

        [[maybe_unused]]
        static auto dot(const Vector3<ScalarType>&, const Vector3<ScalarType>&) -> ScalarType;

        // binary operators can't be static member functions.
        static auto add(const Vector3<ScalarType>&, const Vector3<ScalarType>&) -> Vector3<ScalarType>;
        static auto sub(const Vector3<ScalarType>&, const Vector3<ScalarType>&) -> Vector3<ScalarType>;

        static auto multiply(ScalarType, const Vector3<ScalarType>&) -> Vector3<ScalarType>;

    private:
        vector_type v;
    };


    template<typename ScalarType> [[maybe_unused]]
    Vector3<ScalarType>::Vector3() { std::memset(&v, 0, 3*sizeof(ScalarType)); }


    template<typename ScalarType> [[maybe_unused]]
    Vector3<ScalarType>::Vector3(const ScalarType *start)
    {
        std::memcpy(&v, start, 3*sizeof(ScalarType) );
    }


    template<typename ScalarType> [[maybe_unused]]
    Vector3<ScalarType>::Vector3(std::initializer_list<ScalarType> l)
    { std::copy(l.begin(), l.end(), v); }


    template<typename ScalarType> [[maybe_unused]]
    auto Vector3<ScalarType>::operator+=(const Vector3<ScalarType>& right) -> Vector3<ScalarType>&
    {
        for (auto k = 0; k < length; ++k) v[k] += right.v[k];
        return *this;
    }


    template<typename ScalarType> [[maybe_unused]]
    auto Vector3<ScalarType>::operator-=(const Vector3<ScalarType>& right) -> Vector3<ScalarType>&
    {
        for (auto k = 0; k < length; ++k) v[k] -= right.v[k];
        return *this;
    }


    template<typename ScalarType> [[maybe_unused]]
    auto Vector3<ScalarType>::operator*=(const ScalarType c) -> Vector3&
    {
        for (auto &vk: v) vk *= c;
        return *this;
    }


    template<typename ScalarType> [[maybe_unused]]
    auto Vector3<ScalarType>::norm() const -> ScalarType {
        return std::sqrt(*this* *this);
    }


    template<typename ScalarType> [[maybe_unused]]
    auto Vector3<ScalarType>::unit() const -> Vector3<ScalarType> {
        auto result {*this};
        auto magnitude = result.norm();
        if (magnitude > 0.0) magnitude = 1.0/magnitude;
        result *= magnitude;
        return result;
    }


    template<typename ScalarType> [[maybe_unused]]
    auto Vector3<ScalarType>::add(const Vector3<ScalarType>& left, const Vector3<ScalarType>& right) -> Vector3<ScalarType>
    {
        Vector3<ScalarType> result;
        for (auto k=0; k < Vector3<ScalarType>::length; ++k) result.v[k] = left.v[k] + right.v[k];
        return result;
    }


    template<typename ScalarType> [[maybe_unused]]
    auto Vector3<ScalarType>::sub(const Vector3<ScalarType>& left, const Vector3<ScalarType>& right) -> Vector3<ScalarType>
    {
        Vector3<ScalarType> result;
        for (auto k=0; k < Vector3<ScalarType>::length; ++k) result.v[k] = left.v[k] - right.v[k];
        return result;
    }


    template<typename ScalarType> [[maybe_unused]]
    auto operator+(const Vector3<ScalarType>& left, const Vector3<ScalarType>& right) -> Vector3<ScalarType>
    {
        return Vector3<ScalarType>::add(left, right);
    }


    template<typename ScalarType> [[maybe_unused]]
    auto operator-(const Vector3<ScalarType>& left, const Vector3<ScalarType>& right) -> Vector3<ScalarType>
    {
        return Vector3<ScalarType>::sub(left, right);
    }

    template<typename ScalarType>
    auto Vector3<ScalarType>::multiply(ScalarType c, const Vector3<ScalarType>& right) -> Vector3<ScalarType>
    {
        Vector3<ScalarType> result;
        for (auto k=0; k < Vector3<ScalarType>::length; ++k) result.v[k] = c*right.v[k];
        return result;
    }


    template<typename ScalarType>
    auto operator*(ScalarType c, const Vector3<ScalarType>& right) -> Vector3<ScalarType>
    {
        return Vector3<ScalarType>::multiply(c, right);
    }


    template<typename ScalarType>
    auto operator*(const Vector3<ScalarType>& left, ScalarType c) -> Vector3<ScalarType>
    {
        return Vector3<ScalarType>::multiply(c, left);
    }


    template<typename ScalarType>
    auto Vector3<ScalarType>::dot(const Vector3<ScalarType>&left, const Vector3<ScalarType>&right) -> ScalarType
    {
        ScalarType result = 0.0;
        for (auto k=0; k < Vector3<ScalarType>::length; ++k) result += left.v[k]*right.v[k];
        return result;
    }


    template<typename ScalarType>
    auto operator*(const Vector3<ScalarType>&left, const Vector3<ScalarType>&right) -> ScalarType
    {
        return Vector3<ScalarType>::dot(left, right);
    }


    template<typename ScalarType> [[maybe_unused]]
    auto Vector3<ScalarType>::cross(const Vector3<ScalarType> &left, const Vector3<ScalarType> &right) -> Vector3<ScalarType>
    {
        Vector3<ScalarType> result;
        result.v[0] = left.v[1]*right.v[2] - left.v[2]*right.v[1];
        result.v[1] = left.v[2]*right.v[0] - left.v[0]*right.v[2];
        result.v[2] = left.v[0]*right.v[1] - left.v[1]*right.v[0];
        return result;
    }
}
#endif //ORBIT_VECTOR3_HPP
