#pragma once

#include "AstroDef.h"
#include "Angle.h"

namespace astro {

  struct EquatorialCoords {
    angle_type declination;
    angle_type rightAscension;
  };

  struct HorizontalCoords {
    angle_type azimuth;
    angle_type altitude;
  };

  struct GeographicalCoords {
    angle_type latitude;
    angle_type longitude;
  };

} // namespace astro
