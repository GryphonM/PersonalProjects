//------------------------------------------------------------------------------
//
// File Name:	Hero.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 8.0.1 Assignment: Final Exam
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "GameObject.h"

class Hero : public GameObject
{
public:
    // Non-Default Constructor
    Hero(std::string name_, Point center_, int maxItems);

    // Copy Constructor
    Hero(const Hero& other);

    // Destructor
    virtual ~Hero();

    // Overloads the assignment operator
    // Params:
    //   other = the other object to copy
    // Return:
    //   reference to this object
    Hero& operator=(const Hero& other);

    // Increments the item of the given index
    // Params:
    //   index_ = the index to place the item at
    void IncrementItem(int index_);

    // Updates the object
    virtual void Update() override;

    // Displays the object
    virtual void Display() override;

private:
    int *items;
    int items_count;
};