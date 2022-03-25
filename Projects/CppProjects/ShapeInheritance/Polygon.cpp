//------------------------------------------------------------------------------
//
// File Name:	Polygon.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Polygon.h"

Polygon::Polygon(Point center_, unsigned int vertices)
	: Shape_With_Vertices{center_, vertices} {
}

Polygon::Polygon(Point center_, const Point* points, unsigned int number_of_vertices_)
	: Shape_With_Vertices{center_, number_of_vertices_}
{
	for (unsigned int i = 0; i < number_of_vertices; i++)
	{
		vertices[i].x = points[i].x + center_.x;
		vertices[i].y = points[i].y + center_.y;
	}
}

void Polygon::SetVertex(unsigned int vertexIdx_, float x_, float y_)
{
	if (vertexIdx_ >= number_of_vertices)
	{
		std::cout << "Bad vertex index provided" << std::endl;
		return;
	}
	
	vertices[vertexIdx_].x = x_ + GetCenter().x;
	vertices[vertexIdx_].y = y_ + GetCenter().y;
}

void Polygon::Draw() const
{
	std::cout << "Drawing a polygon at x = " << GetCenter().x << " y = " << GetCenter().y << std::endl;

	for (unsigned int i = 0; i < number_of_vertices; i++)
	{
		std::cout << "Vertex " << i << " (" << vertices[i].x << ", " << vertices[i].y << ")" << std::endl;
	}

	std::cout << std::endl;
}