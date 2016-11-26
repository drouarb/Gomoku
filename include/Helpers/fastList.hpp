#ifndef FASTLIST_HH_
#define FASTLIST_HH_

#include "reservationList.hpp"
#include <string>
#include <iostream>

template <typename T>
class fastList
{
public:

    struct iterator;

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
    fastList(const fastList<T> &);
    ~fastList();

    fastList &      operator=(const fastList &);

    const iterator  begin() const;
    iterator        begin();
    const iterator  end() const;

    void            create_elem();
    void		    push_front(const T & value);
    void    	    pop_front();
    iterator	    erase(iterator element);
    bool            empty();
    T &             front();
    int             size() const;
    void            clear();
    bool            isEmpty();

private:
    element *       first;
    static reservList<element> elemReservList;

    void            rec_copy(element * elem);
    void            del_elem(element * elem);
    element*        new_elem();

public:
    void            dump() const;
};

template <typename T>
reservList<typename fastList<T>::element> fastList<T>::elemReservList = reservList<fastList<T>::element>(1024);





/*
 * Element
 */

template<typename T>
fastList<T>::element::element()
{ }

template<typename T>
fastList<T>::element::~element()
{ }



/*
 * Iterator
 */

template<typename T>
fastList<T>::iterator::iterator()
{ }

template<typename T>
fastList<T>::iterator::iterator(element * elem)
{
    this->elem = elem;
}

template<typename T>
fastList<T>::iterator::~iterator()
{ }

template<typename T>
void fastList<T>::iterator::operator++()
{
    elem = elem->next.elem;
}

template<typename T>
void fastList<T>::iterator::operator--()
{
    elem = elem->prev.elem;
}

template<typename T>
bool fastList<T>::iterator::operator==(iterator other) const
{
    return (elem == other.elem);
}

template<typename T>
bool fastList<T>::iterator::operator!=(iterator other) const
{
    return (elem != other.elem);
}

template <typename T>
T & fastList<T>::iterator::operator*()
{
    return (this->elem->value);
}

template <typename T>
T * fastList<T>::iterator::operator->()
{
    return (&this->elem->value);
}



/*
 * fastList<T>
 */

template<typename T>
fastList<T>::fastList()
{
    first = NULL;
}

template<typename T>
fastList<T>::fastList(const fastList<T> & other)
{
    first = NULL;
    rec_copy(other.first);
}

template<typename T>
fastList<T>::~fastList()
{
    clear();
}

template<typename T>
fastList<T> & fastList<T>::operator=(const fastList & other)
{
    clear();
    rec_copy(other.first);
}

template<typename T>
const typename fastList<T>::iterator fastList<T>::begin() const
{
    return (iterator(first));
}

template<typename T>
typename fastList<T>::iterator fastList<T>::begin()
{
    return (iterator(first));
}

template<typename T>
const typename fastList<T>::iterator fastList<T>::end() const
{
    return (iterator((element*)NULL));
}

template<typename T>
void fastList<T>::create_elem()
{
    element * newelem = new_elem();
    if (first)
        first->prev.elem = newelem;
    newelem->next.elem = first;
    newelem->prev.elem = NULL;
    first = newelem;
}

template<typename T>
void fastList<T>::push_front(const T &value)
{
    create_elem();
    first->value = value;
}

template<typename T>
void fastList<T>::pop_front()
{
    element * front = first;
    first = first->next.elem;
    if (first)
    {
        first->prev.elem = NULL;
    }
    del_elem(front);
}

template<typename T>
typename fastList<T>::iterator fastList<T>::erase(iterator it)
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

template<typename T>
bool fastList<T>::empty()
{
    return (first == NULL);
}

template<typename T>
T & fastList<T>::front()
{
    if (first == NULL)
        throw std::out_of_range("Empty fastList");
    return (first->value);
}

template<typename T>
int fastList<T>::size() const
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

template<typename T>
void fastList<T>::clear()
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

template<typename T>
void fastList<T>::rec_copy(element *elem)
{
    if (elem)
    {
        rec_copy(elem->next.elem);
        push_front(elem->value);
    }
}

template<typename T>
void fastList<T>::del_elem(element * element)
{
    elemReservList.giveBack(element);
}

template<typename T>
typename fastList<T>::element * fastList<T>::new_elem()
{
    return (elemReservList.take());
}


template<typename T>
void fastList<T>::dump() const
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

template<typename T>
bool fastList<T>::isEmpty()
{
    return (first == NULL);
}

#endif
