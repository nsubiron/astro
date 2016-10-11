#pragma once

#include "AstroDef.h"

#include <ratio>

namespace astro {

namespace length {

  template <typename RATIO>
  struct length {
    using ratio = RATIO;

    constexpr explicit length(float_type v) : value(v) {}

    template <typename R>
    constexpr explicit length(length<R> d) :
      value(d.value * std::ratio_divide<RATIO, R>::type::den /
                      std::ratio_divide<RATIO, R>::type::num) {}

    float_type value;
  };

  using meter     = length<std::ratio<1>>;
  using kilometer = length<std::kilo>;
  using au        = length<std::ratio<149597870700>>;

  using inch = length<std::ratio<254, 10000>>;
  using foot = length<std::ratio_multiply<std::ratio<12>, inch::ratio>::type>;
  using mile = length<std::ratio_multiply<std::ratio<5280>, foot::ratio>::type>;

} // namespace lenght

  class distance_type {
  public:

    constexpr distance_type() : _kilometers(0.0) {}

    template <typename RATIO>
    constexpr distance_type(length::length<RATIO> l) : _kilometers(l) {}

    template <typename LENGTH>
    constexpr float_type count() const {
      return LENGTH(_kilometers).value;
    }

    constexpr float_type m() const {
      return count<length::meter>();
    }

    constexpr float_type km() const {
      return _kilometers.value;
    }

    constexpr float_type au() const {
      return count<length::au>();
    }

    constexpr distance_type operator-() const {
      return length::kilometer(-_kilometers.value);
    }

    constexpr distance_type &operator+=(distance_type rhs) {
      _kilometers.value += rhs._kilometers.value;
      return *this;
    }

    constexpr distance_type &operator-=(distance_type rhs) {
      _kilometers.value -= rhs._kilometers.value;
      return *this;
    }

    constexpr distance_type operator*=(float_type x) {
      _kilometers.value *= x;
      return *this;
    }

    constexpr distance_type operator/=(float_type x) {
      _kilometers.value /= x;
      return *this;
    }

    constexpr friend distance_type operator+(distance_type lhs, const distance_type& rhs) {
      lhs += rhs;
      return lhs;
    }

    constexpr friend distance_type operator-(distance_type lhs, const distance_type& rhs) {
      lhs -= rhs;
      return lhs;
    }

    constexpr friend distance_type operator*(distance_type lhs, float_type x) {
      lhs *= x;
      return lhs;
    }

    constexpr friend distance_type operator*(float_type x, distance_type lhs) {
      lhs *= x;
      return lhs;
    }

    // Omitted the symmetric of this one because the result won't be a distance.
    constexpr friend distance_type operator/(distance_type lhs, float_type x) {
      lhs /= x;
      return lhs;
    }

  private:

    length::kilometer _kilometers;
  };

namespace literals {

  constexpr distance_type operator"" _m(long double rad) {
    return length::meter(rad);
  }

  constexpr distance_type operator"" _m(unsigned long long rad) {
    return length::meter(rad);
  }

  constexpr distance_type operator"" _km(long double rad) {
    return length::kilometer(rad);
  }

  constexpr distance_type operator"" _km(unsigned long long rad) {
    return length::kilometer(rad);
  }

  constexpr distance_type operator"" _au(long double rad) {
    return length::au(rad);
  }

  constexpr distance_type operator"" _au(unsigned long long rad) {
    return length::au(rad);
  }

} // namespace literals

} // namespace astro

