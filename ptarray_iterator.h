#ifndef LWGEOM_BOOST_PTARRAY_ITERATOR_H
#define LWGEOM_BOOST_PTARRAY_ITERATOR_H

extern "C" {
#include <liblwgeom.h>
}

template<typename T>
class ptarray_const_iterator
{
public:
    using iterator_category= std::random_access_iterator_tag;
    using difference_type= int;
    using value_type= T;
    using pointer= decltype(std::declval<T>());
    //using const_type= typename std::add_const<value_type>::type;
    using reference= const value_type&;

private:
    const POINTARRAY* m_pta;
    difference_type m_pos;

public:
    ptarray_const_iterator() : m_pta{nullptr}, m_pos{0} {}
    ptarray_const_iterator(const POINTARRAY* pta) : m_pta{pta}, m_pos{0} {}
    ptarray_const_iterator(const POINTARRAY* pta, difference_type pos) : m_pta{pta}, m_pos{pos} {}

    reference operator*() const;

    ptarray_const_iterator& operator++() {
        ++m_pos;
        return *this;
    }

    ptarray_const_iterator operator++(int junk) {
        return ptarray_const_iterator(m_pta, m_pos++);
    }

    ptarray_const_iterator& operator+=(difference_type n) {
        m_pos += n;
        return *this;
    }

    ptarray_const_iterator& operator-=(difference_type n) {
        return *this += -n;
    }

    ptarray_const_iterator operator+(difference_type n) const {
        return ptarray_const_iterator(m_pta, m_pos + n);
    }

    ptarray_const_iterator operator-(difference_type n) const {
        return ptarray_const_iterator(m_pta, m_pos - n);
    }

    difference_type operator-(const ptarray_const_iterator & other) const {
        return m_pos - other.m_pos;
    }

    bool operator==(const ptarray_const_iterator & other) const {
        return m_pta == other.m_pta && m_pos == other.m_pos;
    }

    bool operator!=(const ptarray_const_iterator & other) const {
        return !(*this == other);
    }

    bool operator>(const ptarray_const_iterator & other) const {
        return m_pos > other.m_pos;
    }

    bool operator>=(const ptarray_const_iterator & other) const {
        return m_pos >= other.m_pos;
    }

    bool operator<(const ptarray_const_iterator & other) const {
        return m_pos < other.m_pos;
    }

    bool operator<=(const ptarray_const_iterator & other) const {
        return m_pos <= other.m_pos;
    }
};

template<>
const POINT2D & ptarray_const_iterator<POINT2D>::operator*() const {
    return *((POINT2D*) getPoint2d_cp(m_pta, m_pos));
}

template<>
const POINT3DZ & ptarray_const_iterator<POINT3DZ>::operator*() const {
    return *((POINT3DZ*) getPoint3dz_cp(m_pta, m_pos));
}

template<>
const POINT4D & ptarray_const_iterator<POINT4D>::operator*() const {
    return *((POINT4D*) getPoint4d_cp(m_pta, m_pos));
}

template<typename T>
ptarray_const_iterator<T> cbegin(const POINTARRAY & pta) {
    return ptarray_const_iterator<T>(&pta);
}

template<typename T>
ptarray_const_iterator<T> cend(const POINTARRAY & pta) {
    return ptarray_const_iterator<T>(&pta, pta.npoints);
}


#endif //LWGEOM_BOOST_PTARRAY_ITERATOR_H
