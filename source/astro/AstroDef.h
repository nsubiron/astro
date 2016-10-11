#pragma once

#include <cstddef>
#include <type_traits>

namespace astro {

#ifdef ASTRO_FLOAT_PRECISION
  using float_type = float;
#elif defined ASTRO_DOUBLE_PRECISION
  using float_type = double;
#elif defined ASTRO_LONG_DOUBLE_PRECISION
  using float_type = long double;
#else
#  error You must define the float type. Either ASTRO_FLOAT_PRECISION, ASTRO_DOUBLE_PRECISION or ASTRO_LONG_DOUBLE_PRECISION
#endif

  static_assert(
      std::is_floating_point<astro::float_type>::value,
      "float_type must be of floating point type");

  enum Planet {
    Mercury,
    Venus,
    Earth,
    Mars,
    Jupiter,
    Saturn,
    Uranus,
    Neptune,
    Pluto,   // Pluto is a planet!

    NUMBER_OF_PLANETS
  };

} // namespace astro
