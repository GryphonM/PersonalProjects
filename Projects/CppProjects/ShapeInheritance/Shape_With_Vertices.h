#pragma once
#include "Shape.h"
class Shape_With_Vertices : public Shape
{
protected:
	Point* vertices;
	unsigned int number_of_vertices;
public:
	Shape_With_Vertices(Point center_, unsigned int);
	Shape_With_Vertices(Shape_With_Vertices& copy);
	virtual ~Shape_With_Vertices();
	virtual void SetCenter(float x_, float y_) override;
};

