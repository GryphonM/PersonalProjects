#include "Point.h"
#include <iostream>

#pragma once
class Shape
{
private:
	Point center;

public:
	Shape(Point center_);
	virtual ~Shape() = default;
	virtual Point GetCenter() const;
	virtual void SetCenter(float x_, float y_);
	virtual void Draw() const = 0;
};

