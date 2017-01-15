#ifndef LWGEOM_BOOST_PTARRAY_ITERATOR_H
#define LWGEOM_BOOST_PTARRAY_ITERATOR_H

extern "C" {
#include <liblwgeom.h>
}

template<typename T>
class ptarray_iterator
{
public:
    using iterator_category= std::random_access_iterator_tag;
    using difference_type= int;
    using value_type= T;

private:
    POINTARRAY* m_pta;
    difference_type m_pos;


public:
    ptarray_iterator(POINTARRAY* pta) : m_pta{pta}, m_pos{0} {}
    ptarray_iterator(POINTARRAY* pta, difference_type pos) : m_pta{pta}, m_pos{pos} {}

    value_type operator*() const;

    ptarray_iterator& operator++() {
        ++m_pos;
        return *this;
    }

    ptarray_iterator& operator+=(difference_type n) {
        m_pos += n;
        return *this;
    }

    ptarray_iterator& operator-=(difference_type n) {
        return *this += -n;
    }

    ptarray_iterator operator+(difference_type n) const {
        return ptarray_iterator(m_pta, m_pos + n);
    }

    ptarray_iterator operator-(difference_type n) const {
        return ptarray_iterator(m_pta, m_pos - n);
    }

    difference_type operator-(ptarray_iterator & other) {
        return m_pos - other.m_pos;
    }

    bool operator==(const ptarray_iterator & other) const {
        return m_pta == other.m_pta && m_pos == other.m_pos;
    }

    bool operator!=(const ptarray_iterator & other) const {
        return !(*this == other);
    }

    bool operator>(const ptarray_iterator & other) const {
        return m_pos > other.m_pos;
    }

    bool operator>=(const ptarray_iterator & other) const {
        return m_pos >= other.m_pos;
    }

    bool operator<(const ptarray_iterator & other) const {
        return m_pos < other.m_pos;
    }

    bool operator<=(const ptarray_iterator & other) const {
        return m_pos <= other.m_pos;
    }
};

template<>
POINT2D* ptarray_iterator<POINT2D*>::operator*() const {
    // TODO don't cast like this
    return (POINT2D*) getPoint2d_cp(m_pta, m_pos);
}

template<>
POINT3DZ* ptarray_iterator<POINT3DZ*>::operator*() const {
    // TODO don't cast like this
    return (POINT3DZ*) getPoint3dz_cp(m_pta, m_pos);
}

template<>
POINT4D* ptarray_iterator<POINT4D*>::operator*() const {
    // TODO don't cast like this
    return (POINT4D*) getPoint4d_cp(m_pta, m_pos);
}

template<typename T>
ptarray_iterator<T> begin(POINTARRAY & pta) {
    return ptarray_iterator<T>(&pta);
}

template<typename T>
ptarray_iterator<T> end(POINTARRAY & pta) {
    return ptarray_iterator<T>(&pta, pta.npoints);
}


#endif //LWGEOM_BOOST_PTARRAY_ITERATOR_H
