#pragma once

#include "AstroDef.h"
#include "Angle.h"

namespace astro {

  class Trigonometry {
  public:

    // Ecliptic --> Equatorial (For the Sun)
    static angle_type declination(
        angle_type eclipticLongitude,
        angle_type obliquity);

    static angle_type rightAscension(
        angle_type eclipticLongitude,
        angle_type obliquity);

    // Ecliptic --> Equatorial
    static angle_type declination(
        angle_type eclipticLongitude,
        angle_type eclipticLatitude,
        angle_type obliquity);

    static angle_type rightAscension(
        angle_type eclipticLongitude,
        angle_type eclipticLatitude,
        angle_type obliquity);

    // Equatorial --> Horizontal
    // Where latitude is the geographical latitude of the observer.
    static angle_type azimuth(
        angle_type hourAngle,
        angle_type declination,
        angle_type latitude);

    static angle_type altitude(
        angle_type hourAngle,
        angle_type declination,
        angle_type latitude);

    // Hour angle from altitude and declination.
    static angle_type hourAngle(
        angle_type altitude,
        angle_type declination,
        angle_type latitude);
  };

} // namespace astro
