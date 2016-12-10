#ifndef RESERV_LIST_HPP_
#define RESERV_LIST_HPP_

#include <stdlib.h>
#include <mutex>

/**
 * T is the type that the reservation list will contain.
 * reservSize is the number of elements to reserve each time there are no more elements left. Must be greater than 1.
 * All elements are freed when and only when the reservation list is destroyed.
 * No mutex. Multithreading will break.
 */
template <typename T>
class reservList
{
    struct          element
    {
        /**
         *  /!\ Don't change the order of the fields. /!\
         */
        T value;
        element *   next;
    };

public:
    reservList(int reservationSize);
    reservList(const reservList<T> &);
    ~reservList();

    reservList<T> &operator=(const reservList<T> &);

    /**
     * Gives you a new unused, uninitialized, pre-alloc'd T. Replaces the "new" keyword.
     */
    T *             take();
    /**
     * "Frees" the given T to re-enable it for further use. Replaces the "delete" keyword.
     * Warning : as opposed to usual freeing, giveBack does not call any destructor method.
     */
    void            giveBack(T *);

private:
    struct          blockHeader
    {
        blockHeader* next;
    };

    std::mutex      mutex;
    element *       first;
    int             reservSize;
    blockHeader *   blockHeaderList;
    
    /**
     * Call only when there are no more elements in the list (first must be null).
     */
    void            expand();
    /**
     * Recursive freeing of the memory blocks.
     */
    void            recFree(blockHeader * elem);
};

template<typename T>
reservList<T>::reservList(int reservationSize)
{
    mutex.lock();
    reservSize = reservationSize;
    first = NULL;
    blockHeaderList = NULL;
    expand();
    mutex.unlock();
}

template<typename T>
reservList<T>::reservList(const reservList<T> & other)
{
    //should I copy first and blockHeaderList?
    mutex.lock();
    reservSize = other.reservSize;
    first = NULL;
    blockHeaderList = NULL;
    expand();
    mutex.unlock();
}

template<typename T>
reservList<T> & reservList<T>::operator=(const reservList<T> & other)
{
    //should I copy first and blockHeaderList?
    reservSize = other.reservSize;
    return *this;
}

template<typename T>
reservList<T>::~reservList()
{
    recFree(blockHeaderList);
}

template<typename T>
T * reservList<T>::take()
{
    if (first == NULL)
        expand();
    element * elem = first;
    new (&elem->value) T ();
    first = first->next;
    return (reinterpret_cast<T*>(elem));
}

template<typename T>
void reservList<T>::giveBack(T * value)
{
    element * elem = reinterpret_cast<element*>(value);
    elem->value.~T();
    elem->next = first;
    first = elem;
}

template<typename T>
void reservList<T>::expand()
{
    void * block = malloc(reservSize * sizeof(element) + sizeof(blockHeader));

    //memory pointer list element
    blockHeader * ptr = reinterpret_cast<blockHeader *>(block);
    ptr->next = blockHeaderList;
    blockHeaderList = ptr;
    
    //reservation list elements
    element * elemBlock = reinterpret_cast<element *>((int8_t*)block + sizeof(blockHeader));
    int max = reservSize - 1;
    for (int i = 0; i < max; ++i)
    {
        elemBlock[i].next = elemBlock + (i + 1);
    }
    elemBlock[max].next = NULL;
    first = elemBlock + (0);
}

template<typename T>
void reservList<T>::recFree(blockHeader *elem)
{
    if (elem)
    {
        recFree(elem->next);
        free(elem);
    }
}

#endif
