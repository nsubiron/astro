#pragma once

#include "AstroDef.h"
#include "Angle.h"
#include "Coordinates.h"
#include "JulianDate.h"

namespace astro {

  /// An observer at a given Julian date on the given geographical coordinates
  /// on a PLANET.
  template <Planet PLANET>
  class Observer {
  public:

    explicit Observer(const JulianDate &date, const GeographicalCoords &position);

    const JulianDate &getDate() const {
      return _date;
    }

    const GeographicalCoords &getPosition() const {
      return _position;
    }

    angle_type getSiderealTime() const {
      return _siderealTime;
    }

    angle_type convertToHourAngle(angle_type rightAscension) const {
      return _siderealTime - rightAscension;
    }

    HorizontalCoords convertToHorizontalCoords(const EquatorialCoords &coords) const;

  private:

    JulianDate _date;

    GeographicalCoords _position;

    angle_type _siderealTime;
  };

} // namespace astro
