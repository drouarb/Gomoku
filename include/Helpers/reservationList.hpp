#ifndef RESERV_LIST_HPP_
#define RESERV_LIST_HPP_

#include <stdlib.h>

/**
 * T is the type that the reservation list will contain.
 * reservSize is the number of elements to reserve. Must be greater than 1.
 * No mutex. Multithreading will break.
 * No freeing. Only make static/global instances of this class, otherwise memory will leak.
 */
template <typename T>
class reservList
{
    struct element
    {
        /**
         *  /!\ Don't change the order of the fields. /!\
         */
        T value;
        element *   next;
        //element *   prev;
    };

public:
    reservList(int reservationSize);
    ~reservList();

    T *             take();
    void            giveBack(T *);

private:
    element *       first;
    int             reservSize;

    /**
     * Call only when there are no more elements in the list (first must be null).
     */
    void            expand();
};

template<typename T>
reservList<T>::reservList(int reservationSize)
{
    reservSize = reservationSize;
    first = NULL;
    expand();
}

template<typename T>
reservList<T>::~reservList()
{
    //No freeing.
}

template<typename T>
T * reservList<T>::take()
{
    if (first == NULL)
        expand();
    element * elem = first;
    first = first->next;
    //first->prev = NULL;
    return (reinterpret_cast<T*>(elem));
}

template<typename T>
void reservList<T>::giveBack(T * value)
{
    element * elem = reinterpret_cast<element*>(value);
    //elem->prev = NULL;
    elem->next = first;
    //if (first)
        //first->prev = elem;
    first = elem;
}

template<typename T>
void reservList<T>::expand()
{
    element * block = reinterpret_cast<element *>(malloc(reservSize * sizeof(element)));
    for (int /*i = 1*/ i = 0; i < reservSize - 1; ++i)
    {
        //block[i].prev = &block[i - 1];
        block[i].next = &block[i + 1];
    }
    //block[reservSize - 1].prev = &block[reservSize - 2];
    block[reservSize - 1].next = NULL;
    //block[0].prev = NULL;
    //block[0].next = &block[1];
    first = &block[0];
}

#endif
