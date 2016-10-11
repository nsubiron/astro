#pragma once

#include "AstroDef.h"
#include "Angle.h"
#include "Observer.h"
#include "SolarDescription.h"
#include "SolarTimesCalculator.h"

namespace astro {

  template <Planet PLANET>
  class Sun {
  public:

    explicit Sun(const Observer<PLANET> &observer) :
      _observer(observer),
      _sun(observer.getDate()) {}

    angle_type getEclipticalLongitude() const {
      return _sun.getEclipticalLongitude();
    }

    angle_type getDeclination() const {
      return _sun.getDeclination();
    }

    angle_type getRightAscension() const {
      return _sun.getRightAscension();
    }

    angle_type getAltitude() const {
      return getHorizontalCoords().altitude;
    }

    angle_type getAzimuth() const {
      return getHorizontalCoords().azimuth;
    }

    angle_type getHourAngle() const {
      return _observer.convertToHourAngle(getRightAscension());
    }

    EquatorialCoords getEquatorialCoords() const {
      return _sun.getEquatorialCoords();
    }

    HorizontalCoords getHorizontalCoords() const {
      return _observer.convertToHorizontalCoords(getEquatorialCoords());
    }

    /// Should never outlive this.
    SolarTimesCalculator<PLANET> getSolarTimesCalculator() const {
      return SolarTimesCalculator<PLANET>(*this);
    }

  private:

    friend class SolarTimesCalculator<PLANET>;

    Observer<PLANET> _observer;

    SolarDescription<PLANET> _sun;
  };

} // namespace astro
