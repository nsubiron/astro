#pragma once

#include "AstroDef.h"

namespace astro {

namespace angle {

  constexpr float_type pi() {
    return 3.1415926535897932;
  }

  struct radians {
    constexpr explicit radians(float_type v) : value(v) {}
    float_type value;
  };

  struct degrees {
    constexpr explicit degrees(float_type v) : value(v) {}
    float_type value;
  };

  constexpr radians to_radians(float_type degrees) {
    return radians(degrees * pi() / 180.0);
  }

  constexpr degrees to_degrees(float_type radians) {
    return degrees(radians * 180.0 / pi());
  }

}; // namespace angle

  class angle_type {
  public:

    constexpr angle_type() : _radians(0.0) {}

    constexpr angle_type(angle::radians rad) : _radians(rad) {}

    constexpr angle_type(angle::degrees deg) : _radians(angle::to_radians(deg.value)) {}

    constexpr float_type rad() const {
      return _radians.value;
    }

    constexpr float_type deg() const {
      return angle::to_degrees(_radians.value).value;
    }

    constexpr angle_type operator-() const {
      return angle::radians(-_radians.value);
    }

    constexpr angle_type &operator+=(angle_type rhs) {
      _radians.value += rhs._radians.value;
      return *this;
    }

    constexpr angle_type &operator-=(angle_type rhs) {
      _radians.value -= rhs._radians.value;
      return *this;
    }

    constexpr angle_type operator*=(float_type x) {
      _radians.value *= x;
      return *this;
    }

    constexpr angle_type operator/=(float_type x) {
      _radians.value /= x;
      return *this;
    }

    constexpr friend angle_type operator+(angle_type lhs, angle_type rhs) {
      lhs += rhs;
      return lhs;
    }

    constexpr friend angle_type operator-(angle_type lhs, angle_type rhs) {
      lhs -= rhs;
      return lhs;
    }

    constexpr friend angle_type operator*(angle_type lhs, float_type x) {
      lhs *= x;
      return lhs;
    }

    constexpr friend angle_type operator*(float_type x, angle_type lhs) {
      lhs *= x;
      return lhs;
    }

    // Omitted the symmetric of this one because the result won't be an angle.
    constexpr friend angle_type operator/(angle_type lhs, float_type x) {
      lhs /= x;
      return lhs;
    }

    constexpr friend float_type operator/(angle_type lhs, angle_type rhs) {
      return lhs.rad() / rhs.rad();
    }

  private:

    angle::radians _radians;
  };

namespace literals {

  constexpr angle_type operator"" _rad(long double rad) {
    return angle::radians(rad);
  }

  constexpr angle_type operator"" _rad(unsigned long long rad) {
    return angle::radians(rad);
  }

  constexpr angle_type operator"" _pi_rad(long double rad) {
    return angle::radians(angle::pi() * rad);
  }

  constexpr angle_type operator"" _pi_rad(unsigned long long rad) {
    return angle::radians(angle::pi() * rad);
  }

  constexpr angle_type operator"" _deg(long double deg) {
    return angle::degrees(deg);
  }

  constexpr angle_type operator"" _deg(unsigned long long deg) {
    return angle::degrees(deg);
  }

  constexpr angle_type operator"" _arcmin(long double arcmin) {
    return angle::degrees(arcmin / 60.0);
  }

  constexpr angle_type operator"" _arcmin(unsigned long long arcmin) {
    return angle::degrees(arcmin / 60.0);
  }

  constexpr angle_type operator"" _arcsec(long double arcsec) {
    return angle::degrees(arcsec / 3600.0);
  }

  constexpr angle_type operator"" _arcsec(unsigned long long arcsec) {
    return angle::degrees(arcsec / 3600.0);
  }

} // namespace literals

} // namespace astro
