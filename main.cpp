#include <iostream>

#include <iterator>

#include <boost/geometry.hpp>

extern "C" {
    #include <liblwgeom.h>
}

#include "ptarray_iterator.h"

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
            struct dimension<POINT2D> : boost::mpl::int_<2> {
            };

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

            // Adapt LWPOINT to Boost.Geometry
            template<>
            struct tag<LWPOINT> {
                typedef point_tag type;
            };

            template<>
            struct dimension<LWPOINT> : boost::mpl::int_<2> {};

            template<>
            struct coordinate_type<LWPOINT> {
                typedef double type;
            };

            template<>
            struct coordinate_system<LWPOINT> {
                typedef cs::cartesian type;
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

            // Adapt LWLINE to Boost.Geometry
            //template<>
            //struct tag<LWLINE>
            //{
            //    typedef linestring_tag type;
            //};

            //template<>
            //struct range_iterator<LWLINE>
            //{
            //    typedef std::vector<LWPOINT*>::iterator type;
            //};
        }
    }
}

using namespace std;

int main() {
    POINT2D p1 { 3, 5 };
    LWPOINT* p2 = lwpoint_make2d(0, 3.0, 7.0);

    //cout << boost::geometry::distance(p1, *p2) << endl;

    POINTARRAY* pta = ptarray_construct_empty(1, 1, 4);
    pta = ptarray_addPoint(pta, (uint8_t*) &p1, 2, 0);
    pta = ptarray_addPoint(pta, (uint8_t*) &p1, 2, 0);
    pta = ptarray_addPoint(pta, (uint8_t*) &p1, 2, 0);

    for (ptarray_iterator<POINT2D*> it = begin<POINT2D*>(*pta); it != end<POINT2D*>(*pta); ++it) {
        POINT2D* p = *it;
        std::cout << p->x << " " << p->y << std::endl;
    }

    for (ptarray_iterator<POINT4D*> it = begin<POINT4D*>(*pta); it != end<POINT4D*>(*pta); ++it) {
        POINT4D* p = *it;
        std::cout << p->x << " " << p->y << " " << p->z << " " << p-> m << std::endl;
    }

    return 0;
}
