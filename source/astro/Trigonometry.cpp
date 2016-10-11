#include "Trigonometry.h"

#include "Math.h"

namespace astro {

  using namespace astro::math;

  angle_type Trigonometry::declination(angle_type l, angle_type e) {
    return ASin(Sin(e) * Sin(l));
  }

  angle_type Trigonometry::rightAscension(angle_type l, angle_type e) {
    return ATan2(Sin(l) * Cos(e), Cos(l));
  }

  angle_type Trigonometry::declination(angle_type l, angle_type b, angle_type e) {
    return ASin(Sin(b) * Cos(e) + Cos(b) * Sin(e) * Sin(l));
  }

  angle_type Trigonometry::rightAscension(angle_type l, angle_type b, angle_type e) {
    return ATan2(Sin(l) * Cos(e) - Tan(b) * Sin(e), Cos(l));
  }

  angle_type Trigonometry::azimuth(angle_type h, angle_type decl, angle_type lat) {
    return ATan2(Sin(h), Cos(h) * Sin(lat) - Tan(decl) * Cos(lat));
  }

  angle_type Trigonometry::altitude(angle_type h, angle_type decl, angle_type lat) {
    return ASin(Cos(h) * Cos(decl) * Cos(lat) + Sin(decl) * Sin(lat));
  }

  angle_type Trigonometry::hourAngle(angle_type alt, angle_type dec, angle_type lat) {
    return ACos((Sin(alt) - Sin(dec) * Sin(lat)) / (Cos(dec) * Cos(lat)));
  }

} // namespace astro
