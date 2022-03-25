//------------------------------------------------------------------------------
//
// File Name:	Polygon.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once
#include "Shape_With_Vertices.h"
class Polygon : public Shape_With_Vertices
{
public:

	// Non-default Constructor
	// Params:
	//   center_ = Point at the center of the shape
	//   vertices = number if vertices
	Polygon(Point center_, unsigned int vertices);

	// Non-default Constructor
	// Params:
	//   center_ = Point at the center of the shape
	//   points = where the points of the shape are
	//   number_of_vertices = how many points there are
	Polygon(Point center_, const Point* points, unsigned int number_of_vertices_);

	// Sets one of the vertices
	// Params:
	//   vertexIdx_ = Vertex to set
	//   x_ = x position
	//   y_ = y position
	virtual void SetVertex(unsigned int vertexIdx_, float x_, float y_);

	// Draws the shape
	virtual void Draw() const override;
};