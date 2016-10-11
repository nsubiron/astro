#pragma once

#include "AstroDef.h"
#include "Angle.h"

#include <tuple>

namespace astro {

  class Constant {
  public:

    enum Coefficient {
      M0, M1,                   // Mean anomaly.
      C1, C2, C3, C4, C5, C6,   // Equation of the Center.
      Perihelion,
      Obliquity,                // Obliquity of the Equator.
      Theta0, Theta1,           // Sidereal Time.
      J0, J1, J2, J3,           // Solar transit.
      SolarDisk,                // Angular diameter of the Sun.
      AtmosphericCorrection,

      NUMBER_OF_COEFS
    };

    template <Planet PLANET, Coefficient C>
    static constexpr auto get() {
      using namespace literals;
#define Mt std::make_tuple
      constexpr auto THE_TABLE = Mt(
// Planet               M0              M1           C1          C2          C3          C4          C5          C6       Perihelion   Obliquity     Theta0            Theta1         J0       J1       J2         J3      SolarDisk  Atm.Correction
/* Mercury */ Mt( 174.7948_deg, 4.09233445_deg, 23.4400_deg, 2.9818_deg, 0.5255_deg, 0.1058_deg, 0.0241_deg, 0.0055_deg, 111.5943_deg,  0.02_deg,  13.5964_deg,    6.1385025_deg,  45.3495, 11.4556,       0,  175.9386,    1.38_deg,   0.0_deg),
/* Venus   */ Mt(  50.4161_deg, 1.60213034_deg,  0.7758_deg, 0.0033_deg,      0_deg,      0_deg,      0_deg,      0_deg,  73.9519_deg,  2.64_deg, 215.2995_deg,   -1.4813688_deg,  87.8650, -0.2516,  0.0099, -116.7505,    0.74_deg,   0.0_deg),
/* Earth   */ Mt( 357.5291_deg, 0.98560028_deg,  1.9148_deg, 0.0200_deg, 0.0003_deg,      0_deg,      0_deg,      0_deg, 102.9372_deg, 23.45_deg, 280.1600_deg,  360.9856235_deg,   0.0009,  0.0053, -0.0069,    1.0000000, 0.534_deg, -0.566_deg),
/* Mars    */ Mt(  19.3730_deg, 0.52402068_deg, 10.6912_deg, 0.6228_deg, 0.0503_deg, 0.0046_deg, 0.0005_deg,      0_deg,  70.9812_deg, 25.19_deg, 313.4803_deg,  350.89198226_deg,  0.9044,  0.0305, -0.0082,    1.027491,  0.35_deg,   0.0_deg),
/* Jupiter */ Mt(  20.0202_deg, 0.08308529_deg,  5.5549_deg, 0.1683_deg, 0.0071_deg, 0.0003_deg,      0_deg,      0_deg, 237.2074_deg,  3.12_deg, 146.0727_deg,  870.5366420_deg,   0.3345,  0.0064,       0,    0.4135775, 0.10_deg,   0.0_deg),
/* Saturn  */ Mt( 317.0207_deg, 0.03344414_deg,  6.3585_deg, 0.2204_deg, 0.0106_deg, 0.0006_deg,      0_deg,      0_deg,  99.4571_deg, 26.74_deg, 174.3479_deg,  810.7939024_deg,   0.0766,  0.0078, -0.0040,    0.4440276, 0.06_deg,   0.0_deg),
/* Uranus  */ Mt( 141.0498_deg, 0.01172834_deg,  5.3042_deg, 0.1534_deg, 0.0062_deg, 0.0003_deg,      0_deg,      0_deg,   5.4639_deg, 82.22_deg,  17.9705_deg, -501.1600928_deg,   0.1027, -0.0106,  0.0849,   -0.7183165, 0.03_deg,   0.0_deg),
/* Neptune */ Mt( 256.2250_deg, 0.00598103_deg,  1.0302_deg, 0.0058_deg,      0_deg,      0_deg,      0_deg,      0_deg, 182.1957_deg, 27.84_deg,  52.3996_deg,  536.3128492_deg,   0.3841,  0.0019, -0.0066,    0.6712575, 0.02_deg,   0.0_deg),
/* Pluto   */ Mt(  14.8820_deg, 0.00396_deg   , 28.3150_deg, 4.3408_deg, 0.9214_deg, 0.2235_deg, 0.0627_deg, 0.0174_deg,   4.5433_deg, 57.46_deg,  56.3183_deg,  -56.3623195_deg,   3.8479, -0.5023,  0.3045,   -6.386797,  0.01_deg,   0.0_deg)
      );
#undef Mt
      return std::get<C>(std::get<PLANET>(THE_TABLE));
    }
  };

} // namespace astro
