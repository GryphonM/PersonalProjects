#include "MyArray.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

myArray::myArray()
{
    size = 0;
    capacity = 1;
    numbers = DBG_NEW int[1];
}

myArray::myArray(const myArray& other)
{
    size = other.size;
    capacity = other.size;

    numbers = DBG_NEW int[capacity];
    for (int i = 0; i < size; i++)
        numbers[i] = other.numbers[i];
}

myArray::~myArray()
{
    delete[] numbers;
}

int myArray::get_capacity(void) const
{
    return capacity;
}

int myArray::get_size(void) const
{
    return size;
}

void myArray::push(int value_)
{
    if (size == capacity)
    {
        capacity *= 2;
        int* newArray = DBG_NEW int[capacity];
        for (int i = 0; i < size; i++)
            newArray[i] = numbers[i];

        numbers = newArray;
        delete[] newArray;
    }

    numbers[size] = value_;
    size++;
}

void myArray::pop()
{
    if (size > 0)
        size--;
}

myArray& myArray::operator=(const myArray& other)
{
    if (&other != this)
    {
        delete[] numbers;

        size = other.size;
        capacity = other.capacity;

        numbers = DBG_NEW int[capacity];
        for (int i = 0; i < size; i++)
            numbers[i] = other.numbers[i];
    }

    return *this;
}

myArray& myArray::operator+(const myArray& other) const
{
    myArray *out = DBG_NEW myArray();

    int count = 0;
    for (; count < size && count < other.size; count++)
        out->push(numbers[count] + other.numbers[count]);

    if (count + 1 < size)
    {
        for (; count < size; count++)
            out->push(numbers[count]);
    }
    else if (count + 1 < other.size)
    {
        for (; count < other.size; count++)
            out->push(other.numbers[count]);
    }

    return *out;
}

std::ostream& operator<<(std::ostream& os, const myArray& a_)
{
    for (int i = 0; i < a_.size; i++)
    {
        os << a_.numbers[i] << " ";
    }
    os << std::endl;
    return os;
}