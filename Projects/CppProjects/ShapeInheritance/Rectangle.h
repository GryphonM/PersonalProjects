#pragma once
#include "Shape_With_Vertices.h"
class Rectangle : public Shape_With_Vertices
{
private:
	unsigned int width;
	unsigned int height;

public:
	Rectangle(Point center, unsigned int width, unsigned int height);
	virtual ~Rectangle() = default;
	virtual void Draw() const override;
};

