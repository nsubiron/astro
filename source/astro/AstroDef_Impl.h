#include "AstroDef.h"

#define ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, tmpl) template class cls<tmpl>;

#define ASTRO_TEMPLATE_CLASS_INSTANTIATE_FOR_EACH_PLANET(cls) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Mercury) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Venus) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Earth) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Mars) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Jupiter) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Saturn) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Uranus) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Neptune) \
            ASTRO_TEMPLATE_CLASS_INSTANTIATE(cls, astro::Pluto)
