
#include "VectoredList.h"

#include <utility>

VectoredList::Bucket::Bucket() : prev(nullptr), next(nullptr), elemCount(0), data(std::array<T, BLOCK_SIZE>{})
{

}

void VectoredList::Bucket::push_back(T elem)
{
    this->data[elemCount] = std::move(elem);
    this->elemCount += 1;
}

T &VectoredList::Bucket::operator[](int i)
{
    return data.at(i);
}


void VectoredList::push_back(std::string elem)
{
    if (capacity_ - size_ <= 0)
    {
        this->add_bucket();
    }

    this->tail->push_back(std::move(elem));
    this->size_ += 1;
}

void VectoredList::add_bucket()
{
    auto *b = new Bucket();

    if (this->tail == nullptr && this->head == nullptr)
    {
        this->head = b;
        this->tail = b;
    } else
    {
        this->tail->next = b;
        b->prev = this->tail;
        this->tail = b;
    }

    this->capacity_ += BLOCK_SIZE;
}

T &VectoredList::operator[](int i) const
{
    std::size_t bucket_index = i / BLOCK_SIZE;
    std::size_t index = i % BLOCK_SIZE;
    auto *b = this->head;

    for (int j = 0; j < bucket_index; j++)
    {
        b = b->next;
    }

    return b->data[index];
}

VectoredList &VectoredList::operator=(const VectoredList &fraction)
{
    clearBuckets();

    auto copiedBuckets = new Bucket();
    this->head = copiedBuckets;
    this->tail = copiedBuckets;
    this->capacity_ = BLOCK_SIZE;

    for (auto &elem: fraction)
    {
        this->push_back(elem);
    }

    this->size_ = fraction.size_;


    return *this;
}

void VectoredList::clearBuckets()
{
    auto bucket = head;
    do
    {
        auto next = bucket->next;
        delete bucket;
        bucket = next;
    } while (bucket != nullptr);

    head = nullptr;
    tail = nullptr;
    this->capacity_ = 0;
    this->size_ = 0;
}

VectoredList::~VectoredList()
{
    this->clearBuckets();
}

void VectoredList::erase(VectoredList::Iterator &iter)
{
    auto end = Iterator(iter);
    ++end;
    return this->erase(iter, end);
}

void VectoredList::erase(VectoredList::Iterator rangeBegin, VectoredList::Iterator rangeEnd)
{
    auto endCopy = Iterator(rangeEnd);

    auto v = VectoredList();


    while (endCopy != this->end())
    {
        v.push_back(*endCopy);
        ++endCopy;
    }

    auto beginCopy = Iterator(rangeBegin);


    for (int i = 0; i < (this->size_ - v.size_); i++)
    {
        this->pop_back();
    }

    for (int i = 0; i < (this->size_ - v.size_); i++)
    {
        this->push_back(v[i]);
    }

    this->size_ -= (this->size_ - v.size_);

    std::cout << "ASD";
}

void VectoredList::pop_back()
{
    if (this->tail->elemCount == 1)
    {
        auto newTail = this->tail->prev;
        delete this->tail;
        this->tail = newTail;
    } else
    {
        this->tail->data[this->tail->elemCount] = std::string("");
        this->tail->elemCount -= 1;
    }
}


std::ostream &operator<<(std::ostream &os, const VectoredList &v)
{
    for (const auto &elem: v)
    {
        os << elem << std::endl;
    }
    return os;
}

