//------------------------------------------------------------------------------
//
// File Name:	Shape.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Point.h"
#include <iostream>

#pragma once
class Shape
{
private:
	Point center;

public:

	// Non-default Constructor
	// Params:
	//   center_ = Point at the center of the shape
	Shape(Point center_);

	// Destructor
	virtual ~Shape() = default;

	// Returns the center point
	virtual Point GetCenter() const;

	// Sets the center point
	// Params:
	//   x_ = x position
	//   y_ = y position
	virtual void SetCenter(float x_, float y_);

	// Draws the shape
	virtual void Draw() const = 0;
};

