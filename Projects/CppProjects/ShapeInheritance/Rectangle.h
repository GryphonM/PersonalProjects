//------------------------------------------------------------------------------
//
// File Name:	Rectangle.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "Shape_With_Vertices.h"
class Rectangle : public Shape_With_Vertices
{
private:
	unsigned int width;
	unsigned int height;

public:

	// Non-default Constructor
	// Params:
	//   center = Point at the center of the shape
	//   width = how wide to build the rectangle
	//   height = how high to build the rectangle
	Rectangle(Point center, unsigned int width, unsigned int height);

	// Destructor
	virtual ~Rectangle() = default;

	// Draw the shape
	virtual void Draw() const override;
};

