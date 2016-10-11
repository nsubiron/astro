#pragma once

#include "AstroDef.h"

#ifndef ASTRO_NO_BOOST
// Forward declare boost::posix_time::ptime.
namespace boost { namespace posix_time { class ptime; }}
#endif // ASTRO_NO_BOOST

namespace astro {

  /// A Julian date up to seconds precision.
  class JulianDate {
  public:

    /// Julian day at 2000/1/1 noon.
    static constexpr JulianDate J2000() {
      return JulianDate(2451545);
    }

    static JulianDate fromTruncated2000(float_type value);

    /// Just day, i.e. at noon.
    constexpr explicit JulianDate(long unsigned julianDay) :
      _day(julianDay),
      _seconds(0u) {}

    explicit JulianDate(long unsigned julianDay, long unsigned secondsSinceNoon);

#ifndef ASTRO_NO_BOOST

    /// Initialize from UTC.
    explicit JulianDate(const boost::posix_time::ptime &utc);

    /// Return the UTC time for the given Julian day.
    boost::posix_time::ptime toPosixTime() const;

#endif // ASTRO_NO_BOOST

    constexpr long unsigned day() const {
      return _day;
    }

    constexpr long unsigned secondsSinceNoon() const {
      return _seconds;
    }

    void tick(long unsigned seconds);

    /// Return the decimal part of the Julian date, i.e. the fraction of the day
    /// between [0.0, 1.0[, being zero at noon.
    float_type decimal() const;

    float_type truncated2000() const;

  private:

    void fix();

    long unsigned _day;

    long unsigned _seconds;
  };

} // namespace astro
