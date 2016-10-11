#include "JulianDate.h"

#include "Math.h"

#include <cmath>

#ifndef ASTRO_NO_BOOST
#  include "boost/date_time/gregorian/gregorian_types.hpp"
#  include "boost/date_time/posix_time/posix_time_types.hpp"
#endif // ASTRO_NO_BOOST

namespace astro {

  static constexpr long unsigned secondsInADay() {
    return 24 * 3600;
  }

  JulianDate::JulianDate(long unsigned julianDay, long unsigned secondsSinceNoon) :
    _day(julianDay),
    _seconds(secondsSinceNoon) {
    fix();
  }

#ifndef ASTRO_NO_BOOST

  JulianDate::JulianDate(const boost::posix_time::ptime &utc) :
    _day(utc.date().julian_day() - 1),
    _seconds(utc.time_of_day().total_seconds() + 12 * 3600) {
    fix();
  }

  boost::posix_time::ptime JulianDate::toPosixTime() const {
    using namespace boost::gregorian;
    using namespace boost::posix_time;
    auto ymd = gregorian_calendar::from_julian_day_number(_day);
    return ptime(date(ymd), seconds(_seconds + 12 * 3600));
  }

#endif // ASTRO_NO_BOOST

  void JulianDate::tick(long unsigned seconds) {
    _seconds += seconds;
    fix();
  }

  float_type JulianDate::decimal() const {
    return static_cast<float_type>(_seconds) /
           static_cast<float_type>(secondsInADay());
  }

  float_type JulianDate::truncated2000() const {
    return static_cast<float_type>(day() - J2000().day()) + decimal();
  }

  JulianDate JulianDate::fromTruncated2000(const float_type value) {
    float_type integral;
    float_type decimal = std::modf(value, &integral);
    auto date = J2000();
    date._day += integral;
    date._seconds += std::lround(decimal * secondsInADay());
    return date;
  }

  void JulianDate::fix() {
    while (_seconds >= secondsInADay()) {
      _seconds -= secondsInADay();
      ++_day;
    }
  }

} // namespace astro
