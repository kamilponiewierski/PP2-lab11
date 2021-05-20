
#ifndef LAB_11_VECTOREDLIST_H
#define LAB_11_VECTOREDLIST_H

#include <string>
#include <array>
#include <iostream>

#define BLOCK_SIZE 10
#define T std::string

class VectoredList
{
public:

private:
    class Bucket
    {
    public:
        Bucket *prev;
        Bucket *next;
        int elemCount;
        std::array<T, BLOCK_SIZE> data;

    public:
        void push_back(T elem);

        Bucket();

        ~Bucket() = default;

        T &operator[](int i);
    };

    class Iterator
    {
    public:
        Iterator &operator++()
        {
            elementIndex++;
            if (elementIndex == BLOCK_SIZE)
            {
                m_ptr = m_ptr->next;
                elementIndex = 0;
            }

            return *this;
        }


        T &operator*() const
        {
            return (*m_ptr)[elementIndex];
        }

        friend bool operator==(const Iterator &a, const Iterator &b)
        { return !(a != b); };

        friend bool operator!=(const Iterator &a, const Iterator &b)
        { return a.m_ptr != b.m_ptr || a.elementIndex != b.elementIndex; };

    public:
        explicit Iterator(Bucket *ptr) : m_ptr(ptr), elementIndex(0)
        {}

        Iterator(Bucket *ptr, int elementIndex) : m_ptr(ptr), elementIndex(elementIndex)
        {}

    public:
        Bucket *m_ptr;
        int elementIndex;
    };

private:
    Bucket *head;
    Bucket *tail;

    int size_;
    int capacity_;

    void add_bucket();

public:
    void push_back(T elem);

    void pop_back();

    T &operator[](int i) const;

    VectoredList &operator=(const VectoredList &fraction);

    Iterator begin() const
    {
        return Iterator(this->head);
    }

    Iterator end() const
    {
        return Iterator(this->tail, size_ % BLOCK_SIZE);
    }

    void erase(Iterator &iter);

    void erase(Iterator rangeBegin, Iterator rangeEnd);


    ~VectoredList();

    void clearBuckets();
};

std::ostream &operator<<(std::ostream &os, const VectoredList &v);


#endif //LAB_11_VECTOREDLIST_H
