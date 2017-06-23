#pragma once

#include <boost/geometry.hpp>
#include "ptarray_iterator.h"
#include "adapter_lwring.h"

extern "C" {
    #include <liblwgeom.h>
}

// Polygon must provide a range of interior Rings
// Ring must be a range of points

template<typename T>
class PointerRange {

public:
    PointerRange(T* start, T* end)
            : m_start{start}, m_end{end} {}

    T* begin() {
        return m_start;
    }

    T* end() {
        return m_end;
    }

private:
    T* m_start;
    T* m_end;
};

class RingRange {

public:
    RingRange(LWRING** start, unsigned num_rings) :
            m_start{start}, m_num_rings{num_rings} {}

    LWRING** begin() {
        return m_start;
    }

    LWRING** end() {
        return m_start + m_num_rings;
    }

private:
    LWRING** m_start;
    unsigned m_num_rings;
};

class ConstRingRange {

public:
    ConstRingRange(const LWRING** start, unsigned num_rings) :
            m_start{start}, m_num_rings{num_rings} {}

    const LWRING** cbegin() const {
        return m_start;
    }

    const LWRING** cend() const {
        return m_start + m_num_rings;
    }

private:
    const LWRING** m_start;
    unsigned m_num_rings;
};

//namespace std {
//    template<>
//    struct iterator_traits<const POINTARRAY> {
//        using iterator_category= random_access_iterator_tag;
//        using difference_type= size_t;
//        using value_type=
//    };
//}

namespace boost {

    ptarray_const_iterator<POINT2D> begin(RingRange &r) {
        return begin(r);
    }

    ptarray_const_iterator<POINT2D> end(RingRange &r) {
        return end(r);
    }

    ptarray_const_iterator<POINT2D> begin(ConstRingRange &r) {
        return cbegin(r);
    }

    ptarray_const_iterator<POINT2D> end(ConstRingRange &r) {
        return cend(r);
    }
}

namespace boost {
    namespace geometry {
        namespace traits {
//            template<>
//            struct point_type<LWPOLY> {
//                using type= LWPOINT;
//            };

            template<>
            struct tag<LWPOLY> {
                using type= polygon_tag;
            };

            template<>
            struct ring_const_type<LWPOLY> {
                using type= const LWRING;
            };

            template<>
            struct ring_mutable_type<LWPOLY> {
                using type= LWRING;
            };

            template<>
            struct interior_const_type<LWPOLY> {
                using type= iterator_range<const LWRING>;
            };

            template<>
            struct interior_mutable_type<LWPOLY> {
                using type= iterator_range<LWRING>;
            };

            template<>
            struct exterior_ring<LWPOLY> {

                static LWRING & get(LWPOLY & lwpoly) {
                    return *lwpoly.rings[0];
                }

                static const LWRING & get(const LWPOLY & lwpoly) {
                    return *lwpoly.rings[0];
                }

            };

            template<>
            struct interior_rings<LWPOLY> {

                static RingRange get(LWPOLY & lwpoly) {
                    if (lwpoly.nrings > 1)
                        return RingRange(&(lwpoly.rings[1]), lwpoly.nrings - 1);
                    else
                        return RingRange(nullptr, 0);
                }

                static const ConstRingRange get(const LWPOLY & lwpoly) {
                    if (lwpoly.nrings > 1)
                        return ConstRingRange((const POINTARRAY**) &(lwpoly.rings[1]), lwpoly.nrings - 1);
                    else
                        return ConstRingRange(nullptr, 0);
                }
            };
        }
    }
}

