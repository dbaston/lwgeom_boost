#include <iostream>

#include <iterator>

#include <boost/geometry.hpp>

extern "C" {
    #include <liblwgeom.h>
}

#include "adapter_lwpoint.h"
#include "adapter_point2d.h"

#include "ptarray_iterator.h"

namespace boost {
    namespace geometry {
        namespace traits {
            // Adapt LWLINE to Boost.Geometry
            template<>
            struct tag<LWLINE> {
                using type= linestring_tag;
            };
        }
    }
}

namespace boost {
    //template<>
    //struct range_iterator<LWLINE> {
    //    using type= ptarray_iterator<POINT2D*>;
    //};

    template<>
    struct range_const_iterator<LWLINE> {
        using type= ptarray_const_iterator<POINT2D>;
    };

    template<>
    struct range_value<LWLINE> {
        using type= POINT2D;
    };
}

template<typename T>
inline ptarray_const_iterator<T> range_begin(LWLINE& lwline) {
    return cbegin<T>(*lwline.points);
}

template<typename T>
inline ptarray_const_iterator<T> range_end(LWLINE& lwline) {
    return cend<T>(*lwline.points);
}

using namespace std;

int main() {
    POINT2D p1 { 3, 5 };
    LWPOINT* p2 = lwpoint_make2d(0, 3.0, 7.0);

    LWLINE* line = lwline_construct_empty(4326, 0, 0);
    lwline_add_lwpoint(line, lwpoint_make2d(0, 4, 9), 0);
    lwline_add_lwpoint(line, lwpoint_make2d(0, 2, 97), 1);

    cout << boost::geometry::distance(p1, *p2) << endl;
    cout << boost::geometry::distance(line, line) << endl;

    POINTARRAY* pta = ptarray_construct_empty(1, 1, 4);
    pta = ptarray_addPoint(pta, (uint8_t*) &p1, 2, 0);
    pta = ptarray_addPoint(pta, (uint8_t*) &p1, 2, 0);
    pta = ptarray_addPoint(pta, (uint8_t*) &p1, 2, 0);

    for (auto it = cbegin<POINT2D>(*pta); it != cend<POINT2D>(*pta); ++it) {
        auto p = *it;
        std::cout << p.x << " " << p.y << std::endl;
    }

    for (auto it = cbegin<POINT4D>(*pta); it != cend<POINT4D>(*pta); ++it) {
        auto p = *it;
        std::cout << p.x << " " << p.y << " " << p.z << " " << p.m << std::endl;
    }

    return 0;
}
