//------------------------------------------------------------------------------
//
// File Name:	Shape.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.11 Assignment: Inheritance with Shapes
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Shape.h"

Shape:: Shape(Point center_)
	: center(center_){
}

Point Shape::GetCenter() const
{
	return center;
}

void Shape::SetCenter(float x_, float y_)
{
	center.x = x_;
	center.y = y_;
}