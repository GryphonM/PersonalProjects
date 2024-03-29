//------------------------------------------------------------------------------
//
// File Name:	Intersection2D.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Project 7
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Shapes2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Check whether a point and circle intersect.
// Params:
//  point = The point in the intersection.
//  circle = The circle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointCircleIntersection(const Beta::Vector2D& point, const Beta::Circle& circle);

// Check whether a point and rectangle intersect.
// Params:
//  point = The point in the intersection.
//  rect  = The rectangle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointRectangleIntersection(const Beta::Vector2D& point, const Beta::BoundingRectangle& rect);

// Check whether two circles intersect.
// Params:
//  circle1 = The first circle.
//  circle2 = The second circle.
// Returns:
//   True if intersection, false otherwise.
bool CircleCircleIntersection(const Beta::Circle& circle1, const Beta::Circle& circle2);

// Check whether two rectangles intersect.
// Params:
//  rect1 = The first rectangle.
//	rect2 = The second rectangle.
// Returns:
//   True if intersection, false otherwise.
bool RectangleRectangleIntersection(const Beta::BoundingRectangle& rect1, const Beta::BoundingRectangle& rect2);

// Check whether a rectangle and circle intersect.
// Params:
//  rect = The rectangle.
//  circle  = The circle.
// Returns:
//   True if intersection, false otherwise.
bool RectangleCircleIntersection(const Beta::BoundingRectangle& rect, const Beta::Circle& circle);

// Check whether a moving point and line intersect.
// Params:
//  staticLine   = Start and end of first line segment.
//  movingPoint = Start and end of second line segment (usually a moving point).
//  intersection = Intersection point, if any.
//  t = The t value from the intersection calculation.
// Returns:
//   True if intersection, false otherwise.
bool MovingPointLineIntersection(const Beta::LineSegment& staticLine, const Beta::LineSegment& movingPoint, Beta::Vector2D& intersection, float& t);

// Modifies object's position, velocity, and rotation using simple point-line reflection.
// Params:
//  transform = Transform of the object that is being reflected.
//  rigidBody   = RigidBody of the object being reflected.
//  staticLine   = Start and end of first line segment.
//  movingPoint = Start and end of second line segment (usually a moving point).
//  intersection = Intersection point of the line and circle. 
void MovingPointLineReflection(Transform& transform, RigidBody& rigidBody, const Beta::LineSegment& staticLine, const Beta::LineSegment& movingPoint, const Beta::Vector2D& intersection);

// Checks whether a point is between two parallel lines.
// Params:
//   point = The point in question.
//   firstLine = A point on the first line.
//   secondLine = A point on the second line.
//   normal = Normal vector to the two lines.
// Returns:
//   True if the point is between the two lines, false otherwise.
bool PointIsBetweenLines(const Beta::Vector2D& point, const Beta::Vector2D& firstLine, const Beta::Vector2D& secondLine, const Beta::Vector2D& normal);

// Reflects a point over a line.
// Params:
//   point = The point being reflected.
//   line = The line the point will be reflected over.
// Returns:
//   The reflected point.
Beta::Vector2D ReflectPointOverLine(const Beta::Vector2D& point, const Beta::LineSegment& line);

//------------------------------------------------------------------------------
