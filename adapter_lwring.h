#pragma once

#include <boost/geometry.hpp>
#include "ptarray_iterator.h"

extern "C" {
    #include <liblwgeom.h>
}

using LWRING= POINTARRAY;

namespace boost {

    template<>
    struct range_iterator<LWRING> {
        using type= ptarray_const_iterator<POINT2D>;
    };

    namespace geometry {
        namespace traits {
            template<>
            struct tag<LWRING> {
                using type= ring_tag;
            };
        }
    }
}

namespace boost {
    template<>
    struct range_const_iterator<LWRING> {
        using type= ptarray_const_iterator<POINT2D>;
    };

    template<>
    struct range_value<LWRING> {
        using type= POINT2D;
    };

    //template<>
    //struct range_difference<LWLINE> {
    //    using type= int;
    //};

    //std::size_t size(const LWLINE& lwline) {
    //    return lwline.points->npoints;
    //}

}

ptarray_const_iterator<POINT2D> range_begin(const LWRING & lwring) {
    return cbegin<POINT2D>(lwring);
}

ptarray_const_iterator<POINT2D> range_end(const LWRING & lwring) {
    return cend<POINT2D>(lwring);
}

// TODO fetch mutable iterator
ptarray_const_iterator<POINT2D> range_begin(LWRING & lwring) {
    return cbegin<POINT2D>(lwring);
}

// TODO fetch mutable iterator
ptarray_const_iterator<POINT2D> range_end(LWRING & lwring) {
    return cend<POINT2D>(lwring);
}
