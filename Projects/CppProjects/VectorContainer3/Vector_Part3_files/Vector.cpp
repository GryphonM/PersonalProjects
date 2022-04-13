//------------------------------------------------------------------------------
//
// File Name:	Vector.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 8.1.6 Assignment - Vector Container Class Part 3
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include <iostream>  // cout
#include <cstdlib>   // abort
#include "Vector.h"

namespace CS170
{

// Default constructor
template <typename T>
Vector<T>::Vector(void) : array_(0), size_(0), capacity_(0), allocs_(0)
{
}

// Constructor to create a Vector from an array
template <typename T>
Vector<T>::Vector(const T array[], unsigned size) : size_(size), capacity_(size), allocs_(1)
{
    array_ = new T[capacity_];
    for (unsigned i = 0; i < size; i++)
        array_[i] = array[i];
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs) : size_(rhs.size_), capacity_(rhs.size_), allocs_(1)
{
    array_ = new T[capacity_];
    for (unsigned i = 0; i < size_; i++)
        array_[i] = rhs[i];
}

// Destructor
template <typename T>
Vector<T>::~Vector()
{
    delete[] array_;
}

// Adds a node to the back of the array. If there is
// not enough room in the array, it will be grown to
// handle more items.
template <typename T>
void Vector<T>::push_back(T value)
{
    if (size_ == capacity_)
        grow();
    array_[size_] = value;
    size_++;
}

// Adds a node to the front of the array. If there is
// not enough room in the array, it will be grown to
// handle more items. All items to the right must be
// shifted over one element to the right.
template <typename T>
void Vector<T>::push_front(T value)
{
    insert(value, 0);
}

// Removes the last element. Does nothing if empty.
template <typename T>
void Vector<T>::pop_back(void)
{
    if (array_ != nullptr)
        size_--;
}

// Removes the first element. Does nothing if empty.
template <typename T>
void Vector<T>::pop_front(void)
{
    if (array_ != nullptr)
    {
        size_--;
        for (unsigned i = 0; i < size_; i++)
            array_[i] = array_[i + 1];
    }
}

// Inserts a new node at the specified position. Causes an
// abort() if the position is invalid. (Calls check_bounds)
template <typename T>
void Vector<T>::insert(T value, unsigned position)
{
    if (array_ == nullptr)
        push_back(value);
    else
    {
        if (size_ == capacity_)
            grow();

        check_bounds(position);
        for (unsigned i = size_; i > position; i--)
            array_[i] = array_[i - 1];

        size_++;
        array_[position] = value;
    }
}

// Removes an element with the specified value (first occurrence)
template <typename T>
void Vector<T>::remove(T value)
{
    bool foundValue = false;
    for (unsigned i = 0; i < size_; i++)
    {
        if (!foundValue)
        {
            if (array_[i] == value)
            {
                foundValue = true;
                size_--;
                if (i < size_)
                    array_[i] = array_[i + 1];
            }
        }
        else
            array_[i] = array_[i + 1];
    }
}

// Subscript operators for const and non-const
template <typename T>
T Vector<T>::operator[](unsigned index) const
{
    check_bounds(index);
    return array_[index];
}

template <typename T>
T& Vector<T>::operator[](unsigned index)
{
    check_bounds(index);
    return array_[index];
}

// Deletes the underlying array and sets size_ to 0
template <typename T>
void Vector<T>::clear(void)
{
    delete[] array_;
    array_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

// Return true if the vector is empty, otherwise, false
template <typename T>
bool Vector<T>::empty(void) const
{
  return size_ == 0;
}

// Assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
    if (this != &rhs)
    {
        size_ = rhs.size_;
        if (capacity_ <= size_)
        {
            capacity_ = rhs.size_;
            delete[] array_;
            array_ = new T[capacity_];
            allocs_++;
        }
        for (unsigned i = 0; i < size_; i++)
            array_[i] = rhs.array_[i];
    }

    return *this;
}

// Concatenates a vector onto the end of this vector.
template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector& rhs)
{
    unsigned size = rhs.size_;
    for (unsigned i = 0; i < size; i++)
        push_back(rhs[i]);

    return *this;
}

// Concatenates two Vectors.
template <typename T>
Vector<T> Vector<T>::operator+(const Vector& rhs) const
{
    Vector sum = *this;
    sum += rhs;
    return sum;
}

// Returns the number of elements in the vector
template <typename T>
unsigned Vector<T>::size(void) const
{
  return size_;
}

// Returns the size of the underlying array
template <typename T>
unsigned Vector<T>::capacity(void) const
{
  return capacity_;
}

// The number of memory allocations that have occurred
template <typename T>
unsigned Vector<T>::allocations(void) const
{
  return allocs_;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// private 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T>
void Vector<T>::check_bounds(unsigned index) const
{
    // Don't have to check for < 0 because index is unsigned
  if (index >= size_)
  {
    std::cout << "Attempting to access index " << index << ".";
    std::cout << " The size of the array is " << size_ << ". Aborting...\n";
    std::abort();
  }
}

template <typename T>
void Vector<T>::grow(void)
{
  // Double the capacity
  capacity_ = (capacity_) ? capacity_ * 2 : 1;

  // Create an array with the doubled size
  T* newArray = new T[capacity_];
  allocs_++;

  // Copy array values
  for (unsigned i = 0; i < size_; i++)
      newArray[i] = array_[i];

  if (array_ != nullptr)
    delete[] array_;
  array_ = newArray;
}

} // namespace CS170