//------------------------------------------------------------------------------
//
// File Name:	myArray.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 6.0.3 EXAM: Midterm (Programming Portion)
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "MyArray.h"

// Default Constructor for class
myArray::myArray()
{
    size = 0;
    capacity = 1;
    numbers = new int[1];
}

// Copy Constructor for class
// Params:
//   other = Other object to copy from
myArray::myArray(const myArray& other)
{
    size = other.size;
    capacity = other.size;

    // Copy values to this array
    numbers = new int[capacity];
    for (int i = 0; i < size; i++)
        numbers[i] = other.numbers[i];
}

// Constructor with set variables.
// Params:
//   numbers_ = array of numbers to assign to the numbers value.
//   size_ = how many values in the array
//   capacity_ = how many values can be stored in the array
myArray::myArray(int* numbers_, int size_, int capacity_)
{
    size = size_;
    capacity = capacity_;
    numbers = numbers_;
}

// Destructor for class
myArray::~myArray()
{
    delete[] numbers;
}

// Returns the capacity of the array
int myArray::get_capacity(void) const
{
    return capacity;
}

// Returns the size of the array
int myArray::get_size(void) const
{
    return size;
}

// Adds a value to the end of the array
// Params:
//   value_ = value to add to array
void myArray::push(int value_)
{
    // Double capacity if full
    if (size == capacity)
    {
        capacity *= 2;
        int* newArray = new int[capacity];
        for (int i = 0; i < size; i++)
            newArray[i] = numbers[i];

        delete[] numbers;
        numbers = newArray;
    }

    numbers[size] = value_;
    size++;
}

// Removes last value from array
void myArray::pop()
{
    if (size > 0)
        size--;
}

// Overloads the assignment operator for this class
// Params:
//   other = the array to assign this arrays values to.
// Return:
//   A pointer to this array object
myArray myArray::operator=(const myArray& other)
{
    if (&other != this)
    {
        delete[] numbers;

        size = other.size;
        capacity = other.capacity;

        // Copy values to this array
        numbers = new int[capacity];
        for (int i = 0; i < size; i++)
            numbers[i] = other.numbers[i];
    }

    return *this;
}

// Overloads the + operator for this class
// Params:
//   other = Array to add to this class
// Return:
//   A pointer to this array object
myArray myArray::operator+(const myArray& other) const
{
    // Determine which capacity is larger
    int capacity_;
    if (capacity < other.capacity)
        capacity_ = other.capacity;
    else
        capacity_ = capacity;

    // Allocate memory for return array
    int* numbers_ = new int[capacity_];

    int count = 0;
    for (; count < size && count < other.size; count++)
        numbers_[count] = numbers[count] + other.numbers[count];

    // Determine which array has leftover elements
    if (count + 1 < size)
    {
        for (; count < size; count++)
            numbers_[count] = numbers[count];
    }
    else if (count + 1 < other.size)
    {
        for (; count < other.size; count++)
            numbers_[count] = other.numbers[count];
    }

    return myArray(numbers_, count, count);
}

// Overloads the += operator for this class
// Params:
//   other = Array to add to this class
// Return:
//   A pointer to this array object
myArray myArray::operator+=(const myArray& other)
{
    // Store values of this numbers array in temporary array
    int* tempNumbers = new int[capacity];
    for (int i = 0; i < size; ++i)
        tempNumbers[i] = numbers[i];

    if (capacity < other.capacity)
        capacity = other.capacity;

    // Reallocate numbers array to fit the new size
    delete[] numbers;
    numbers = new int[capacity];

    int count = 0;
    for (; count < size && count < other.size; count++)
        numbers[count] = tempNumbers[count] + other.numbers[count];

    // Determine which array has leftover elements
    if (count + 1 < size)
    {
        for (; count < size; count++)
            numbers[count] = tempNumbers[count];
    }
    else if (count + 1 < other.size)
    {
        for (; count < other.size; count++)
            numbers[count] = other.numbers[count];
    }

    // Clear allocated array and set the size
    delete[] tempNumbers;
    size = count;

    return *this;
}

// Overloads the << operator for this class
// Params:
//   os = stream to output the array to
//   a_ = array to output
// Return:
//   The stream where the array was output
std::ostream& operator<<(std::ostream& os, const myArray& a_)
{
    for (int i = 0; i < a_.size; i++)
    {
        os << a_.numbers[i] << " ";
    }
    os << std::endl;
    return os;
}