#pragma once
#include "Shape_With_Vertices.h"
class Polygon : public Shape_With_Vertices
{
public:
	Polygon(Point center_, unsigned int vertices);
	Polygon(Point center_, const Point* points, unsigned int number_of_vertices_);
	virtual void SetVertex(unsigned int vertexIdx_, float x_, float y_);
	virtual void Draw() const override;
};