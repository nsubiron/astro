Astro
=====

C++14 library for astronomical calculations.

Still in an early phase of development, but here some samples of what it does so
far

### Noon, sunrise and sunset.
```cpp
using namespace astro;
using namespace astro::literals;

namespace bpt = boost::posix_time;
bpt::ptime utc(bpt::second_clock::universal_time());
auto timeZone = bpt::hours(9) + bpt::minutes(30);

constexpr auto position = GeographicalCoords{
                -(25_deg + 20_arcmin + 42_arcsec),
                 131_deg +  2_arcmin + 10_arcsec};

Observer<Earth> observer(JulianDate(utc), position);
Sun<Earth> sun(observer);

auto solarTimes = sun.getSolarTimesCalculator();
auto sunriseAndSunset = solarTimes.calculateSunriseAndSunset();

auto getLocalTime = [&timeZone](const JulianDate &date) {
  return date.toPosixTime() + timeZone;
};

std::cout << "Noon    = " << getLocalTime(solarTimes.getTransit()) << '\n';
std::cout << "Sunrise = " << getLocalTime(sunriseAndSunset.rise) << '\n';
std::cout << "Sunset  = " << getLocalTime(sunriseAndSunset.set) << '\n';
```

### Astronomical dusk and dawn.
```cpp
auto duskAndDawn = solarTimes.calculate(-18_deg);

std::cout << "Astronomical Dawn = " << getLocalTime(duskAndDawn.rise) << '\n';
std::cout << "Astronomical Dusk = " << getLocalTime(duskAndDawn.set) << '\n';
```

### Altitude of the Sun in Mars.
```cpp
Observer<Mars> observer(JulianDate(utc), {39.662_deg, -0.226_deg});
Sun<Mars> sun(observer);

std::cout << sun.getAltitude().deg() << '\n';
```
