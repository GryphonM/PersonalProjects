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