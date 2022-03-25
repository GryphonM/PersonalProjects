//------------------------------------------------------------------------------
//
// File Name:	Circle.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Circle.h"

Circle::Circle(Point center_, unsigned int radius_)
	: Shape{ center_ }, radius(radius_) {
}

void Circle::Draw() const
{
	std::cout << "Drawing a circle at x = " << GetCenter().x << " y = " << GetCenter().y << " and radius " << radius << "\n" << std::endl;
}