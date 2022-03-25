//------------------------------------------------------------------------------
//
// File Name:	Shape_With_Vertices.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Shape_With_Vertices.h"

Shape_With_Vertices::Shape_With_Vertices(Point center_, unsigned int vertices_)
	: Shape(center_), number_of_vertices(vertices_)
{
	vertices = new Point[number_of_vertices];
}

Shape_With_Vertices::Shape_With_Vertices(Shape_With_Vertices& copy)
	: Shape(copy.GetCenter()), number_of_vertices(copy.number_of_vertices)
{
	vertices = new Point[number_of_vertices];
	for (unsigned int i = 0; i < number_of_vertices; i++)
	{
		vertices[i] = copy.vertices[i];
	}
}

Shape_With_Vertices::~Shape_With_Vertices()
{
	delete[] vertices;
}

void Shape_With_Vertices::SetCenter(float x_, float y_)
{
	Point difference = Point(x_ - GetCenter().x, y_ - GetCenter().y);
	Shape::SetCenter(x_, y_);

	for (unsigned int i = 0; i < number_of_vertices; i++)
	{
		vertices[i].x += difference.x;
		vertices[i].y += difference.y;
	}
}