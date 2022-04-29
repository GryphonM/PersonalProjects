//------------------------------------------------------------------------------
//
// File Name:	GameObject.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS170 8.0.1 Assignment: Final Exam
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "Point.h"
#include <string>

class GameObject
{
public:
    // Non-default constructor
    GameObject(std::string name_, Point center_);

    // Provides the default destructor as virtual
    virtual ~GameObject() = default;

    // Makes class abstract
    virtual void Update(void) = 0;

    // Makes class abstract
    virtual void Display(void) = 0;

    // Sets the value of name
    void SetName(std::string name_);

    // Gets the value of name
    std::string GetName() const;

    // Sets the center of the object with a Point object
    void SetCenter(Point center_);

    // Sets the center of the object with x and y coordinates
    void SetCenter(int x, int y);

    // Gets the center of the object
    Point GetCenter() const;

private:
    std::string name;
    Point center;
};