#include <iostream>

#include <iterator>

#include <boost/geometry.hpp>

extern "C" {
    #include <liblwgeom.h>
}

#include "adapter_lwpoint.h"
#include "adapter_point2d.h"
#include "adapter_lwline.h"
#include "ptarray_iterator.h"

int main() {
    std::cout << BOOST_LIB_VERSION << std::endl;

    POINT2D p1 { 3, 5 };
    LWPOINT* p2 = lwpoint_make2d(0, 3.0, 7.0);

    LWLINE* line = lwline_construct_empty(0, 0, 0);
    lwline_add_lwpoint(line, lwpoint_make2d(0, 4, 9), 0);
    lwline_add_lwpoint(line, lwpoint_make2d(0, 2, 97), 1);

    LWLINE* line2 = lwline_construct_empty(0, 0, 0);
    lwline_add_lwpoint(line2, lwpoint_make2d(0, 108, 14), 0);
    lwline_add_lwpoint(line2, lwpoint_make2d(0, 100, 28), 1);

    // Point-Point Distance
    std::cout << boost::geometry::distance(p1, *p2) << std::endl;

    // Point-Line Distance
    std::cout << boost::geometry::distance(p1, *line) << std::endl;
    std::cout << boost::geometry::distance(*p2, *line) << std::endl;

    // Line-Line Intersection
    std::cout << boost::geometry::intersects(*line, *line2) << std::endl;

    // Line-Line Distance
    std::cout << boost::geometry::distance(*line, *line2) << std::endl;

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
