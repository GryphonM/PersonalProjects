//------------------------------------------------------------------------------
//
// File Name:	Vector.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 8.1.4 Assignment - Vector Container Class Part 2
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
Vector::Vector(void) : array_(0), size_(0), capacity_(0), allocs_(0)
{
}

// Constructor to create a Vector from an array
Vector::Vector(const int array[], unsigned size) : size_(size), capacity_(size), allocs_(1)
{
    array_ = new int[capacity_];
    for (unsigned i = 0; i < size; i++)
        array_[i] = array[i];
}

// Copy constructor
Vector::Vector(const Vector& rhs) : size_(rhs.size_), capacity_(rhs.size_), allocs_(1)
{
    array_ = new int[capacity_];
    for (unsigned i = 0; i < size_; i++)
        array_[i] = rhs[i];
}

// Destructor
Vector::~Vector()
{
    delete[] array_;
}

// Adds a node to the back of the array. If there is
// not enough room in the array, it will be grown to
// handle more items.
void Vector::push_back(int value)
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
void Vector::push_front(int value)
{
    insert(value, 0);
}

// Removes the last element. Does nothing if empty.
void Vector::pop_back(void)
{
    if (array_ != nullptr)
        size_--;
}

// Removes the first element. Does nothing if empty.
void Vector::pop_front(void)
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
void Vector::insert(int value, unsigned position)
{
    check_bounds(position);
    if (size_ == capacity_)
        grow();

    for (unsigned i = size_; i > position; i--)
        array_[i] = array_[i - 1];

    array_[position] = value;
}

// Removes an element with the specified value (first occurrence)
void Vector::remove(int value)
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
int Vector::operator[](unsigned index) const
{
    check_bounds(index);
    return array_[index];
}

int& Vector::operator[](unsigned index)
{
    check_bounds(index);
    return array_[index];
}

// Deletes the underlying array and sets size_ to 0
void Vector::clear(void)
{
    delete[] array_;
    array_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

// Return true if the vector is empty, otherwise, false
bool Vector::empty(void) const
{
  return size_ == 0;
}

// Assignment operator
Vector& Vector::operator=(const Vector& rhs)
{
    if (this != &rhs)
    {
        size_ = rhs.size_;
        for (unsigned i = 0; i < size_; i++)
            array_[i] = rhs.array_[i];
    }

    return *this;
}

// Concatenates a vector onto the end of this vector.
Vector& Vector::operator+=(const Vector& rhs)
{
    for (unsigned i = 0; i < rhs.size_; i++)
        push_back(rhs[i]);

    return *this;
}

// Concatenates two Vectors.
Vector Vector::operator+(const Vector& rhs) const
{
    Vector sum = *this;
    sum += rhs;
    return sum;
}

// Returns the number of elements in the vector
unsigned Vector::size(void) const
{
  return size_;
}

// Returns the size of the underlying array
unsigned Vector::capacity(void) const
{
  return capacity_;
}

// The number of memory allocations that have occurred
unsigned Vector::allocations(void) const
{
  return allocs_;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// private 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Vector::check_bounds(unsigned index) const
{
    // Don't have to check for < 0 because index is unsigned
  if (index >= size_)
  {
    std::cout << "Attempting to access index " << index << ".";
    std::cout << " The size of the array is " << size_ << ". Aborting...\n";
    std::abort();
  }
}

void Vector::grow(void)
{
  // Double the capacity
  capacity_ = (capacity_) ? capacity_ * 2 : 1;

  // Create an array with the doubled size
  int* newArray = new int[capacity_];
  allocs_++;

  // Copy array values
  for (unsigned i = 0; i < size_; i++)
      newArray[i] = array_[i];

  if (array_ != nullptr)
    delete[] array_;
  array_ = newArray;
}

} // namespace CS170