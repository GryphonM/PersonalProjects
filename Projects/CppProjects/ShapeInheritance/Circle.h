//------------------------------------------------------------------------------
//
// File Name:	Circle.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "Shape.h"
class Circle : public Shape
{
private:
	unsigned int radius;

public:

	// Non-default Constructor
	// Params:
	//   center = Point at the center of the shape
	//   radius = radius of the circle
	Circle(Point center_, unsigned int radius);

	// Draws the shape
	virtual void Draw() const override;
};

