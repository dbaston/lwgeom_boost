#include <iostream>

#include <iterator>

#include <boost/geometry.hpp>

extern "C" {
    #include <liblwgeom.h>
}

#include "adapter_lwpoint.h"
#include "adapter_point2d.h"
#include "adapter_lwline.h"
#include "adapter_lwpoly.h"

int main() {
    std::cout << BOOST_LIB_VERSION << std::endl;

    using boost::geometry::read_wkt;

    using boost_point = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
    boost_point a;
    boost::geometry::model::polygon<boost_point> b;
    read_wkt("POINT (1 2)", a);
    read_wkt("POLYGON ((10 10, 20 10, 2 20, 10 10))", b);

    POINT2D p1 { 3, 5 };
    LWPOINT* p2 = lwpoint_make2d(0, 3.0, 7.0);

    LWLINE* line  = lwgeom_as_lwline(lwgeom_from_wkt("LINESTRING (1 7, 2 9)", LW_PARSER_CHECK_NONE));
    LWLINE* line2 = lwgeom_as_lwline(lwgeom_from_wkt("LINESTRING (9 2, 1 0)", LW_PARSER_CHECK_NONE));

    LWPOLY* poly = lwgeom_as_lwpoly(lwgeom_from_wkt("POLYGON ((0 0, 1 0, 1 1, 0 0))", LW_PARSER_CHECK_NONE));

    // Point-Point Distance
    std::cout << boost::geometry::distance(p1, *p2) << std::endl;

    // Point-Line Distance
    std::cout << boost::geometry::distance(p1, *line) << std::endl;
    std::cout << boost::geometry::distance(*p2, *line) << std::endl;

    // Line-Line Intersection
    std::cout << boost::geometry::intersects(*line, *line2) << std::endl;

    // Line-Line Distance
    std::cout << boost::geometry::distance(*line, *line2) << std::endl;

    // Point-Polygon Distance
    //auto strategy = boost::geometry::strategy::distance::pythagoras<double>();
    //std::cout << boost::geometry::distance(p1, *poly, strategy) << std::endl;
    //std::cout << boost::geometry::distance(*poly, *poly) << std::endl;
    std::cout << boost::geometry::intersects(*poly, *poly) << std::endl;

    //std::cout << boost::geometry::distance(a, b) << std::endl;


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
