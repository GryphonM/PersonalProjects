//------------------------------------------------------------------------------
//
// File Name:	Vector.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 5.6.8 Assignment - Tic-Tac-Toe
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
    if (size_ == capacity_)
        grow();

    for (unsigned i = size_; i > 0; i--)
        array_[i] = array_[i - 1];
    size_++;
    array_[0] = value;
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