// -*- mode: c++ -*-
////
// Created by Glen Dayton, new account on 2/28/23.
//
// Specializations for the orbit namespace.
//
#include "orbit.hpp"

template class orbit::StateVector<float>;
template class orbit::StateVector<double>;

template class orbit::KeplerianElements<float>;
template class orbit::KeplerianElements<double>;
