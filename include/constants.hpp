// -*- mode: c++ -*-
////
// Created by Glen Dayton, new account on 2/27/23.
//
// Some astrodynamic constants;=,

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef ORBIT_CONSTANTS_HPP
#define ORBIT_CONSTANTS_HPP

namespace orbit {
    static const auto bigG = 6.67430e-11; // N*m^2/kg^2
    static const auto earthMass = 5.972168e24; // kg
    static const auto muEarth = bigG*earthMass;
    static const auto earthRadius = 6371.0e3; // m
    static const auto earthEquatorialRadius = 6378.137e3; // m
    static const auto earthPolarRadius = 6356.752e3; // m
    static const auto earthFlattening = 1.0/298.257222101;

    // Canonical Units (mu = 1)
    static const auto CDU = earthRadius;
    static const auto VDU = 7.910e3; // m/s circular orbit speed at surface
    static const auto TDU = 805.5; // seconds period of orbit at surface

    // Earth J2000 Osculating Elements
    // Unix time is loosely based on UTC(NIST) but without leap seconds.  UTC = Unix Time + leap seconds
    // "Atomic time" is generally taken to be TAI (International Atomic Time).
    //  UTC = TAI + leap seconds.
    //  Most computer systems do not present leap seconds. Your computer's time gets adjusted every time a leap second
    //  is added, so it appears every once in a while your computer repeats a second.
    //  Serious astrometry should refer to the Standards of Fundamental Astronomy https://www.iausofa.org/
    //  J2000 is an offset from UT1 (aka UT) astronomical time.
    //  for conversions between the various co-ordinate systems and time standards.
    static const auto J2000 = 946728000.0; // Unix time at Sat Jan 01 2000 12:00:00 GMT+0000
    static const auto JD200 = 2451545.0; // Terrestrial Time (TT) at J2000
    static const auto J200TAI = 3.725E-04; // Offset between TAI and J2000. (January 1, 2000, 11:59:27.816 TAI)
    static const auto J2000UTC = 7.428704E-04; // Offset between UTC and J200 (January 1, 2000, 11:58:55.816 UTC)
    static const auto GPStoTAI = 18.0; // Seconds TAI is always 18 seconds ahead of GPS time

    // Leap seconds (June 30, Dec 31) 1972 to 2023
    static const int leapSeconds[][2] = {
            {1, 1}, // 1972
            {0, 1},
            {0, 1},
            {0, 1}, // 1975
            {0, 1},
            {0, 1},
            {0, 1},
            {0, 1}, // 1979
            {0, 0}, // 1980
            {1, 0},
            {1, 0},
            {1, 0},
            {0,0}, // 1984
            {1, 0}, // 1985
            {0,0},
            {0, 1},
            {0, 0}, // 1988
            {0, 1},
            {0, 1}, // 1990
            {0, 0},
            {1, 0},
            {1, 0},
            {1, 0},
            {0, 1}, // 1995
            {0, 0},
            {1, 0},
            {0, 1},
            {0, 0},
            {0,0}, // 2000
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 1}, // 2005
            {0, 0},
            {0, 0},
            {0, 1},
            {0, 0},
            {0, 0},
            {0, 0}, // 2010
            {0, 0},
            {1, 0},
            {0, 0},
            {0, 0},
            {1, 0}, // 2015
            {0, 1},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0}, // 2020
            {0, 0},
            {0, 0},
            {0, 0} //2023
    };
}

#endif //ORBIT_CONSTANTS_HPP

#pragma clang diagnostic pop