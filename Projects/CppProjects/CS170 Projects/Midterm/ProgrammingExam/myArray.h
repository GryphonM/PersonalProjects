//------------------------------------------------------------------------------
//
// File Name:	myArray.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 6.0.3 EXAM: Midterm (Programming Portion)
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include <iostream>

class myArray
{
public:
    // Default Constructor for class
    myArray(void);

    // Copy Constructor for class
    // Params:
    //   other = Other object to copy from
    myArray(const myArray& other);

    // Constructor with set variables.
    // Params:
    //   numbers_ = array of numbers to assign to the numbers value.
    //   size_ = how many values in the array
    //   capacity_ = how many values can be stored in the array
    myArray(int* numbers_, int size_, int capacity_);

    // Destructor for class
    ~myArray(void);


    // Returns the capacity of the array
    int get_capacity(void) const;

    // Returns the size of the array
    int get_size(void) const;

    // Adds a value to the end of the array
    // Params:
    //   value_ = value to add to array
    void push(int value_);

    // Removes last value from array
    void pop();

    // Overloads the assignment operator for this class
    // Params:
    //   other = the array to assign this arrays values to.
    // Return:
    //   A pointer to this array object
    myArray operator=(const myArray& other);

    // Overloads the + operator for this class
    // Params:
    //   other = Array to add to this class
    // Return:
    //   A pointer to this array object
    myArray operator+(const myArray& other) const;

    // Overloads the += operator for this class
    // Params:
    //   other = Array to add to this class
    // Return:
    //   A pointer to this array object
    myArray operator+=(const myArray& other);


    // Overloads the << operator for this class
    // Params:
    //   os = stream to output the array to
    //   a_ = array to output
    // Return:
    //   The stream where the array was output
    friend std::ostream& operator<<(std::ostream& os, const myArray& a_);

private:
    int *numbers;
    int size;
    int capacity;
};
