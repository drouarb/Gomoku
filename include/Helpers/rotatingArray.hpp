//
// Created by lewis_e on 09/12/16.
//

#ifndef GOMOKU_ROTATINGARRAY_HPP
#define GOMOKU_ROTATINGARRAY_HPP

#include <boost/container/static_vector.hpp>

template <typename T, size_t ss>
class rotatingArray : public boost::container::static_vector<T, ss>
{
private:
    typedef boost::container::static_vector<T, ss> base;

public:

    T & front()
    {
        return (base::back());
    }

    void push_front(const T & val)
    {
        base::push_back(val);
    }

    typename base::iterator erase(typename base::iterator p)
    {
        if (p == base::end())
        {
            return (base::erase(p));
        }

        *p = base::back();
        base::pop_back();
        return (p);
    }

    typename base::const_iterator erase(typename base::const_iterator p)
    {
        if (p == base::end())
        {
            return (base::erase(p));
        }

        *p = base::back();
        base::pop_back();
        return (p);
    }




    /*typedef boost::container::static_vector<T, ss> vecttype;
    typedef typename vecttype::iterator iterator;
    typedef typename vecttype::const_iterator const_iterator;

    rotatingArray() : stvect()
    { }
    rotatingArray(const rotatingArray & other) : stvect(other.stvect)
    { }
    ~rotatingArray()
    { }

    rotatingArray & operator=(const rotatingArray & other)
    {
        stvect = other.stvect;
    }

    T &operator[](size_t index)
    {
        return (stvect.operator[](index));
    }

    void push_front(const T & val)
    {
        stvect.push_back(val);
    }

    void push_back(const T & val)
    {
        stvect.push_back(val);
    }

    T & front()
    {
        return (stvect.back());
    }

    T & back()
    {
        return (stvect.back());
    }

    iterator begin()
    {
        return (stvect.begin());
    }

    const_iterator begin() const
    {
        return (stvect.begin());
    }

    iterator end()
    {
        return (stvect.end());
    }

    const_iterator end() const
    {
        return (stvect.end());
    }

    iterator erase(iterator p)
    {
        if (p == stvect.end())
        {
            return (stvect.erase(p));
        }

        *p = back();
        stvect.pop_back();
        return (p);
    }

    bool empty() const
    {
        return (stvect.empty());
    }

    void clear()
    {
        stvect.clear();
    }

    size_t size() const
    {
        return (stvect.size());
    }

private:
    vecttype stvect;*/
};

#endif //GOMOKU_ROTATINGARRAY_HPP
