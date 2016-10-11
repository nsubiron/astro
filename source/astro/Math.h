#pragma once

#include "AstroDef.h"
#include "Angle.h"

#include <cmath>

namespace astro {
namespace math {

  inline float_type Cos(angle_type a) {
    return std::cos(a.rad());
  }

  inline float_type Sin(angle_type a) {
    return std::sin(a.rad());
  }

  inline float_type Tan(angle_type a) {
    return std::tan(a.rad());
  }

  inline angle_type ACos(float_type x) {
    return angle::radians(std::acos(x));
  }

  inline angle_type ASin(float_type x) {
    return angle::radians(std::asin(x));
  }

  inline angle_type ATan(float_type x) {
    return angle::radians(std::atan(x));
  }

  inline angle_type ATan2(float_type y, float_type x) {
    return angle::radians(std::atan2(y, x));
  }

} // namespace math
} // namespace astro
