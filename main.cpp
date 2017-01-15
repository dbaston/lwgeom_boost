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

    cout << boost::geometry::distance(p1, *p2) << endl;

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
