#pragma once

#include <boost/geometry.hpp>
#include "ptarray_iterator.h"

extern "C" {
    #include <liblwgeom.h>
}

namespace boost {

    template<>
    struct range_iterator<LWLINE> {
        using type= ptarray_const_iterator<POINT2D>;
    };

    namespace geometry {
        namespace traits {
            template<>
            struct tag<LWLINE> {
                using type= linestring_tag;
            };

#if 0
            //template<>
            struct clear<LWLINE> {
                static inline void apply(typename rvalue_type<LWLINE>::type range) {
                    std::cout << "clear" << std::endl;
                }
            };

           template<>
           struct resize<LWLINE> {
                static inline void apply(typename rvalue_type<LWLINE>::type range, std::size_t mr_t) {
                    // NOP
                }
           };

            template<>
            struct push_back<LWLINE> {
                static inline void apply(typename rvalue_type<LWLINE>::type range, POINT2D const & item) {
                    lwline_add_lwpoint(&range, lwpoint_make2d(range.srid, item.x, item.y), range.points->npoints);
                }
            };
#endif
        }
    }
}

namespace boost {
    template<>
    struct range_const_iterator<LWLINE> {
        using type= ptarray_const_iterator<POINT2D>;
    };

    template<>
    struct range_value<LWLINE> {
        using type= POINT2D;
    };

    template<>
    struct range_difference<LWLINE> {
        using type= int;
    };

    std::size_t size(const LWLINE& lwline) {
        return lwline.points->npoints;
    }

}

ptarray_const_iterator<POINT2D> range_begin(const LWLINE & lwline) {
    return cbegin<POINT2D>(*lwline.points);
}

ptarray_const_iterator<POINT2D> range_end(const LWLINE & lwline) {
    return cend<POINT2D>(*lwline.points);
}

// TODO fetch mutable iterator
ptarray_const_iterator<POINT2D> range_begin(LWLINE & lwline) {
    return cbegin<POINT2D>(*lwline.points);
}

// TODO fetch mutable iterator
ptarray_const_iterator<POINT2D> range_end(LWLINE & lwline) {
    return cend<POINT2D>(*lwline.points);
}
