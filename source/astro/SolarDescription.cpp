#include "AstroDef_Impl.h"
#include "SolarDescription.h"

#include "Constant.h"
#include "JulianDate.h"
#include "Math.h"
#include "Trigonometry.h"

namespace astro {

  using namespace astro::literals;
  using namespace astro::math;
  using C = Constant;

  template <Planet PLANET>
  SolarDescription<PLANET>::SolarDescription(const JulianDate &date) {
    // M = M0 + M1 (J - J2000)
    _meanAnomaly = C::get<PLANET, C::M0>() + C::get<PLANET, C::M1>() * date.truncated2000();
    // C ~ C1 sin(M) + C2 sin(2M) + C3 sin(3M) + C4 sin(4M) + C5 sin(5M) + C6 sin(6M)
    _equationOfTheCenter = C::get<PLANET, C::C1>() * Sin(_meanAnomaly) +
                           C::get<PLANET, C::C2>() * Sin(2.0 * _meanAnomaly) +
                           C::get<PLANET, C::C3>() * Sin(3.0 * _meanAnomaly) +
                           C::get<PLANET, C::C4>() * Sin(4.0 * _meanAnomaly) +
                           C::get<PLANET, C::C5>() * Sin(5.0 * _meanAnomaly) +
                           C::get<PLANET, C::C6>() * Sin(6.0 * _meanAnomaly);
    // l = M + C + Perihelion + 180
    _eclipticalLongitude = _meanAnomaly + _equationOfTheCenter + C::get<PLANET, C::Perihelion>() + 1_pi_rad;
  }

  template <Planet PLANET>
  angle_type SolarDescription<PLANET>::getDeclination() const {
    return Trigonometry::declination(_eclipticalLongitude, C::get<PLANET, C::Obliquity>());
  }

  template <Planet PLANET>
  angle_type SolarDescription<PLANET>::getRightAscension() const {
    return Trigonometry::rightAscension(_eclipticalLongitude, C::get<PLANET, C::Obliquity>());
  }

  ASTRO_TEMPLATE_CLASS_INSTANTIATE_FOR_EACH_PLANET(SolarDescription);

} // namespace astro
