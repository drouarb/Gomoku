#ifndef FASTLIST_HH_
#define FASTLIST_HH_

#include "reservationList.hpp"
#include <string>
#include <iostream>

template <typename T, size_t reservSize>
class fastList
{
public:

    struct iterator;
    typedef iterator const_iterator;

    struct element
    {
        element();
        ~element();

        T value;
        iterator next;
        iterator prev;
    };

    struct iterator
    {
        iterator();
        iterator(element *);
        ~iterator();

        void        operator++();
        void        operator--();
        bool        operator==(iterator) const;
        bool        operator!=(iterator) const;
        T &         operator*();
        T *         operator->();

        element *   elem;
    };

public:
    fastList();
    fastList(const fastList<T, reservSize> &);
    ~fastList();

    fastList &      operator=(const fastList &);

    const iterator  begin() const;
    iterator        begin();
    const iterator  end() const;

    void            create_elem();
    void	    push_front(const T & value);
    void    	    pop_front();
    iterator	    erase(iterator element);
    bool            empty() const ;
    T &             front();
    int             size() const;
    void            clear();
    bool            isEmpty();

private:
    element *       first;
    reservList<element> elemReservList;

    void            rec_copy(element * elem);
    void            del_elem(element * elem);
    element*        new_elem();

public:
    void            dump() const;
};



/*
 * Element
 */

template<typename T, size_t reservSize>
fastList<T, reservSize>::element::element()
{ }

template<typename T, size_t reservSize>
fastList<T, reservSize>::element::~element()
{ }



/*
 * Iterator
 */

template<typename T, size_t reservSize>
fastList<T, reservSize>::iterator::iterator()
{ }

template<typename T, size_t reservSize>
fastList<T, reservSize>::iterator::iterator(element * elem)
{
    this->elem = elem;
}

template<typename T, size_t reservSize>
fastList<T, reservSize>::iterator::~iterator()
{ }

template<typename T, size_t reservSize>
void fastList<T, reservSize>::iterator::operator++()
{
    elem = elem->next.elem;
}

template<typename T, size_t reservSize>
void fastList<T, reservSize>::iterator::operator--()
{
    elem = elem->prev.elem;
}

template<typename T, size_t reservSize>
bool fastList<T, reservSize>::iterator::operator==(iterator other) const
{
    return (elem == other.elem);
}

template<typename T, size_t reservSize>
bool fastList<T, reservSize>::iterator::operator!=(iterator other) const
{
    return (elem != other.elem);
}

template <typename T, size_t reservSize>
T & fastList<T, reservSize>::iterator::operator*()
{
    return (this->elem->value);
}

template <typename T, size_t reservSize>
T * fastList<T, reservSize>::iterator::operator->()
{
    return (&this->elem->value);
}



/*
 * fastList<T, reservSize>
 */

template<typename T, size_t reservSize>
fastList<T, reservSize>::fastList() : elemReservList(reservSize)
{
    first = NULL;
}

template<typename T, size_t reservSize>
fastList<T, reservSize>::fastList(const fastList<T, reservSize> & other) : elemReservList(reservSize)
{
    first = NULL;
    rec_copy(other.first);
}

template<typename T, size_t reservSize>
fastList<T, reservSize>::~fastList()
{
    clear();
}

template<typename T, size_t reservSize>
fastList<T, reservSize> & fastList<T, reservSize>::operator=(const fastList & other)
{
    clear();
    rec_copy(other.first);
}

template<typename T, size_t reservSize>
const typename fastList<T, reservSize>::iterator fastList<T, reservSize>::begin() const
{
    return (iterator(first));
}

template<typename T, size_t reservSize>
typename fastList<T, reservSize>::iterator fastList<T, reservSize>::begin()
{
    return (iterator(first));
}

template<typename T, size_t reservSize>
const typename fastList<T, reservSize>::iterator fastList<T, reservSize>::end() const
{
    return (iterator((element*)NULL));
}

template<typename T, size_t reservSize>
void fastList<T, reservSize>::create_elem()
{
    element * newelem = new_elem();
    if (first)
        first->prev.elem = newelem;
    newelem->next.elem = first;
    newelem->prev.elem = NULL;
    first = newelem;
}

template<typename T, size_t reservSize>
void fastList<T, reservSize>::push_front(const T &value)
{
    create_elem();
    first->value = value;
}

template<typename T, size_t reservSize>
void fastList<T, reservSize>::pop_front()
{
    element * front = first;
    first = first->next.elem;
    if (first)
    {
        first->prev.elem = NULL;
    }
    del_elem(front);
}

template<typename T, size_t reservSize>
typename fastList<T, reservSize>::iterator fastList<T, reservSize>::erase(iterator it)
{
    if (it.elem == first)
    {
        pop_front();
        return (iterator(first));
    }
    else
    {
        iterator prev = it.elem->prev;
        prev.elem->next = it.elem->next;
        if (it.elem->next.elem)
            it.elem->next.elem->prev = it.elem->prev;
        del_elem(it.elem);
        return (prev);
    }
}

template<typename T, size_t reservSize>
bool fastList<T, reservSize>::empty() const
{
    return (first == NULL);
}

template<typename T, size_t reservSize>
T & fastList<T, reservSize>::front()
{
    if (first == NULL)
        throw std::out_of_range("Empty fastList");
    return (first->value);
}

template<typename T, size_t reservSize>
int fastList<T, reservSize>::size() const
{
    int i = 0;
    auto it = begin();
    while (it != end())
    {
        ++i;
        ++it;
    }
    return (i);
}

template<typename T, size_t reservSize>
void fastList<T, reservSize>::clear()
{
    if (first)
    {
        element *elem = first;
        while (elem->next.elem)
            elem = elem->next.elem;
        element *prev;
        while (elem)
        {
            prev = elem->prev.elem;
            del_elem(elem);
            elem = prev;
        }
        first = NULL;
    }
}

template<typename T, size_t reservSize>
void fastList<T, reservSize>::rec_copy(element *elem)
{
    if (elem)
    {
        rec_copy(elem->next.elem);
        push_front(elem->value);
    }
}

template<typename T, size_t reservSize>
void fastList<T, reservSize>::del_elem(element * element)
{
    elemReservList.giveBack(element);
}

template<typename T, size_t reservSize>
typename fastList<T, reservSize>::element * fastList<T, reservSize>::new_elem()
{
    return (elemReservList.take());
}


template<typename T, size_t reservSize>
void fastList<T, reservSize>::dump() const
{
    std::cout << "# LIST DUMP" << std::endl;
    for (auto it = begin(); it != end(); ++it)
    {
        std::cout << (void*)it.elem << "\t" << (void*)it.elem->prev.elem << "\t" << (void*)it.elem->next.elem << std::endl;
        if (it.elem->next.elem == it.elem)
        {
            std::cout << "NOOOOOOOOOO" << std::endl;
            break;
        }
    }
}

template<typename T, size_t reservSize>
bool fastList<T, reservSize>::isEmpty()
{
    return (first == NULL);
}

#endif
