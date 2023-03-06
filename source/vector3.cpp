// -*- mode: c++ -*-
////
// Created by Glen Dayton, new account on 2/18/23.
//
// Specializations for the vector class.
//
#include "vector3.hpp"

template class numutil::Vector3<float>;
template class numutil::Vector3<double>;

template auto numutil::operator+(const Vector3<float>& left, const Vector3<float>& right) -> Vector3<float>;
template auto numutil::operator+(const Vector3<double>& left, const Vector3<double>& right) -> Vector3<double>;
template auto numutil::operator*(const Vector3<float>& left, float c) -> Vector3<float>;

template auto numutil::operator*(const Vector3<double>& left, double c) -> Vector3<double>;
template auto numutil::operator*(float c, const Vector3<float>& left) -> Vector3<float>;
template auto numutil::operator*(double c, const Vector3<double>& left) -> Vector3<double>;
