#pragma once

#include "AstroDef.h"
#include "Angle.h"
#include "Coordinates.h"

namespace astro {

  class JulianDate;

  /// Parameters for the Sun at a given Julian date as seen from a PLANET.
  template <Planet PLANET>
  class SolarDescription {
  public:

    explicit SolarDescription(const JulianDate &date);

    angle_type getMeanAnomaly() const {
      return _meanAnomaly;
    }

    angle_type getTrueAnomaly() const {
      return _meanAnomaly + _equationOfTheCenter;
    }

    angle_type getEquationOfTheCenter() const {
      return _equationOfTheCenter;
    }

    angle_type getEclipticalLongitude() const {
      return _eclipticalLongitude;
    }

    angle_type getDeclination() const;

    angle_type getRightAscension() const;

    EquatorialCoords getEquatorialCoords() const {
      EquatorialCoords coords;
      coords.declination = getDeclination();
      coords.rightAscension = getRightAscension();
      return coords;
    }

  private:

    angle_type _meanAnomaly;

    angle_type _equationOfTheCenter;

    angle_type _eclipticalLongitude;
  };

} // namespace astro
