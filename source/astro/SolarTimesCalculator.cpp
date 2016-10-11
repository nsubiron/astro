#include "AstroDef_Impl.h"
#include "SolarTimesCalculator.h"

#include "Constant.h"
#include "Math.h"
#include "Sun.h"
#include "Trigonometry.h"

#include <cmath>

namespace astro {

  using namespace literals;
  using C = Constant;

  template <Planet PLANET>
  static float_type getJulianCycle(const JulianDate &date, angle_type longitudeEast) {
    return std::round(
        (date.truncated2000() - C::get<PLANET, C::J0>()) / C::get<PLANET, C::J3>() +
         longitudeEast / 2_pi_rad);
  }

  template <Planet PLANET>
  SolarTimesCalculator<PLANET>::SolarTimesCalculator(const Sun<PLANET> &sun) :
    _sun(sun),
    _cycle(getJulianCycle<PLANET>(
        _sun._observer.getDate(),
        _sun._observer.getPosition().longitude)),
    _transit(calculateSolarTransit(0_rad)) {}

  template <Planet PLANET>
  SolarTimes SolarTimesCalculator<PLANET>::calculateSunriseAndSunset(
      const bool applyAtmosphericCorrection) const {
    constexpr auto elevation = - C::get<PLANET, C::SolarDisk>() / 2.0;
    if (applyAtmosphericCorrection)
      return calculate(elevation + C::get<PLANET, C::AtmosphericCorrection>());
    return calculate(elevation);
  }

  template <Planet PLANET>
  SolarTimes SolarTimesCalculator<PLANET>::calculate(const angle_type altitude) const {
    const auto &here = _sun._observer.getPosition();
    const auto declination = _sun.getEquatorialCoords().declination;
    const auto hourAngle = Trigonometry::hourAngle(altitude, declination, here.latitude);
    const auto set = calculateSolarTransit(hourAngle);
    const auto rise = JulianDate::fromTruncated2000(2.0 * _transit.truncated2000() - set.truncated2000());
    return {rise, set};
  }

  template <Planet PLANET>
  JulianDate SolarTimesCalculator<PLANET>::calculateSolarTransit(const angle_type hourAngle) const {
    const auto longitudeEast = _sun._observer.getPosition().longitude;
    const auto meanAnomaly = _sun._sun.getMeanAnomaly();
    const auto eclipticLongitudeOfTheSun = _sun.getEclipticalLongitude();

    const auto estimatedTransit =
        C::get<PLANET, C::J0>() +
        C::get<PLANET, C::J3>() * (_cycle + (hourAngle - longitudeEast) / 2_pi_rad);
    const auto transit =
        estimatedTransit +
        C::get<PLANET, C::J1>() * math::Sin(meanAnomaly) +
        C::get<PLANET, C::J2>() * math::Sin(2.0 * eclipticLongitudeOfTheSun);
    // transit -= J3 * H(transit) / 360_deg // @todo repeat to improve precision
    return JulianDate::fromTruncated2000(transit);
  }

  ASTRO_TEMPLATE_CLASS_INSTANTIATE_FOR_EACH_PLANET(SolarTimesCalculator)

} // namespace astro
