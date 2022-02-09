#pragma once
#include "Shape.h"
class Circle : public Shape
{
private:
	unsigned int radius;

public:
	Circle(Point center_, unsigned int radius);
	virtual void Draw() const override;
};

