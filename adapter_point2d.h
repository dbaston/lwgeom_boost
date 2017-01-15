#pragma once

#include <boost/geometry.hpp>

extern "C" {
    #include <liblwgeom.h>
}

namespace boost {
    namespace geometry {
        namespace traits {
            // Adapt POINT2D to Boost.Geometry
            template<>
            struct tag<POINT2D> {
                using type= point_tag;
            };

            template<>
            struct coordinate_type<POINT2D> {
                using type= double;
            };

            template<>
            struct coordinate_system<POINT2D> {
                using type= cs::cartesian;
            };

            template<>
            struct dimension<POINT2D> : boost::mpl::int_<2> {};

            template<>
            struct access<POINT2D, 0> {
                static double get(POINT2D const &p) {
                    return p.x;
                }

                static void set(POINT2D &p, double const &value) {
                    p.x = value;
                }
            };

            template<>
            struct access<POINT2D, 1> {
                static double get(POINT2D const &p) {
                    return p.y;
                }

                static void set(POINT2D &p, double const &value) {
                    p.y = value;
                }
            };
        }
    }
}

