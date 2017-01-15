#pragma once

#include <boost/geometry.hpp>

extern "C" {
#include <liblwgeom.h>
}

namespace boost {
    namespace geometry {
        namespace traits {
            // Adapt LWPOINT to Boost.Geometry
            template<>
            struct tag<LWPOINT> {
                using type= point_tag;
            };

            template<>
            struct dimension<LWPOINT> : boost::mpl::int_<2> {};

            template<>
            struct coordinate_type<LWPOINT> {
                using type= double;
            };

            template<>
            struct coordinate_system<LWPOINT> {
                using type= cs::cartesian;
            };

            template<>
            struct access<LWPOINT, 0> {
                static double get(LWPOINT const &p) {
                    return lwpoint_get_x(&p);
                }
            };

            template<>
            struct access<LWPOINT, 1> {
                static double get(LWPOINT const &p) {
                    return lwpoint_get_y(&p);
                }
            };
        }
    }
}
