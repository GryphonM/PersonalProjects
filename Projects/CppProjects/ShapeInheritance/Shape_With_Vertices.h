//------------------------------------------------------------------------------
//
// File Name:	Shape_With_Vertices.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "Shape.h"
class Shape_With_Vertices : public Shape
{
protected:
	Point* vertices;
	unsigned int number_of_vertices;
public:
	// Non-default Constructor
	// Params:
	//   center_ = Point at the center of the shape
	//   int = Number of vertices
	Shape_With_Vertices(Point center_, unsigned int);

	// Copy Constructor
	// Params:
	//   copy = Object to copy
	Shape_With_Vertices(Shape_With_Vertices& copy);

	// Destructor
	virtual ~Shape_With_Vertices();

	// Resets the center point
	// Params:
	//   x_ = x position
	//   y_ = y position
	virtual void SetCenter(float x_, float y_) override;
};

