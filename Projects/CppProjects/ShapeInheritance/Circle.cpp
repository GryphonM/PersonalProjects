#include "Circle.h"

Circle::Circle(Point center_, unsigned int radius_)
	: Shape{ center_ }, radius(radius_) {
}

void Circle::Draw() const
{
	std::cout << "Drawing a circle at x = " << GetCenter().x << " y = " << GetCenter().y << " and radius " << radius << "\n" << std::endl;
}