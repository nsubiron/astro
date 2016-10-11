#include "AstroDef_Impl.h"
#include "Observer.h"

#include "Constant.h"
#include "Coordinates.h"
#include "JulianDate.h"
#include "Trigonometry.h"

namespace astro {

  template <Planet PLANET>
  static angle_type getSiderealTime(const JulianDate &date, angle_type longitudeEast) {
    using C = Constant;
    // Theta = Theta0 + Theta1 (J - J2000) - l_west
    return C::get<PLANET, C::Theta0>() +
           C::get<PLANET, C::Theta1>() * date.truncated2000() +
           longitudeEast;
  }

  template <Planet PLANET>
  Observer<PLANET>::Observer(const JulianDate &date, const GeographicalCoords &position) :
    _date(date),
    _position(position),
    _siderealTime(astro::getSiderealTime<PLANET>(_date, _position.longitude)) {}

  template <Planet PLANET>
  HorizontalCoords Observer<PLANET>::convertToHorizontalCoords(const EquatorialCoords &ec) const {
    HorizontalCoords hc;
    auto hourAngle = convertToHourAngle(ec.rightAscension);
    hc.azimuth = Trigonometry::azimuth(hourAngle, ec.declination, _position.latitude);
    hc.altitude = Trigonometry::altitude(hourAngle, ec.declination, _position.latitude);
    return hc;
  }

  ASTRO_TEMPLATE_CLASS_INSTANTIATE_FOR_EACH_PLANET(Observer);

} // namespace astro
