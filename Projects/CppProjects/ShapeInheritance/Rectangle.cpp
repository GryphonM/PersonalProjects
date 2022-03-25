//------------------------------------------------------------------------------
//
// File Name:	Rectangle.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Rectangle.h"

Rectangle::Rectangle(Point center_, unsigned int width_, unsigned int height_)
	: Shape_With_Vertices{ center_, 4 }, width{ width_ }, height{ height_ }
{
	float halfWidth = width / 2.f;
	float halfHeight = height / 2.f;
	
	vertices[0].x = center_.x - halfWidth;
	vertices[0].y = center_.y + halfHeight;

	vertices[1].x = center_.x + halfWidth;
	vertices[1].y = center_.y + halfHeight;

	vertices[2].x = center_.x + halfWidth;
	vertices[2].y = center_.y - halfHeight;

	vertices[3].x = center_.x - halfWidth;
	vertices[3].y = center_.y - halfHeight;
}

void Rectangle::Draw() const
{
	std::cout << "Drawing a rectangle at x = " << GetCenter().x << " y = " << GetCenter().y << 
		" with width = " << width << " and height = " << height << std::endl;
	std::cout << "Vertex 0 (" << vertices[0].x << ", " << vertices[0].y << ")" << std::endl;
	std::cout << "Vertex 1 (" << vertices[1].x << ", " << vertices[1].y << ")" << std::endl;
	std::cout << "Vertex 2 (" << vertices[2].x << ", " << vertices[2].y << ")" << std::endl;
	std::cout << "Vertex 3 (" << vertices[3].x << ", " << vertices[3].y << ")" << std::endl;
	std::cout << std::endl;
}