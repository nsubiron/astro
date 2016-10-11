#pragma once

#include "AstroDef.h"
#include "Angle.h"
#include "JulianDate.h"

namespace astro {

  template <Planet PLANET>
  class Sun;

  /// Rise and set times for a given altitude of the Sun.
  struct SolarTimes {
    JulianDate rise;
    JulianDate set;
  };

  template <Planet PLANET>
  class SolarTimesCalculator {
  public:

    explicit SolarTimesCalculator(const Sun<PLANET> &sun);

    const JulianDate &getTransit() const {
      return _transit;
    }

    SolarTimes calculateSunriseAndSunset(bool applyAtmosphericCorrection = true) const;

    SolarTimes calculate(angle_type altitude) const;

  private:

    JulianDate calculateSolarTransit(angle_type hourAngle) const;

    const Sun<PLANET> &_sun;

    float_type _cycle;

    JulianDate _transit; // solar noon
  };

} // namespace astro
