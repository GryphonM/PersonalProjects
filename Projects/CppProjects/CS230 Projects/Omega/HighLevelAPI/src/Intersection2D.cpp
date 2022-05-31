//------------------------------------------------------------------------------
//
// File Name:	Intersection2D.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.1.6 Assignment: Collision Detection
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Intersection2D.h"
#include "Transform.h"
#include "RigidBody.h"

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Check whether a point and circle intersect.
// Params:
//  point = The point in the intersection.
//  circle = The circle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointCircleIntersection(const Beta::Vector2D& point, const Beta::Circle& circle)
{
	float dist = point.DistanceSquared(circle.center);
	if (dist < (circle.radius * circle.radius))
		return true;
	else
		return false;
}

// Check whether a point and rectangle intersect.
// Params:
//  point = The point in the intersection.
//  rect  = The rectangle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointRectangleIntersection(const Beta::Vector2D& point, const Beta::BoundingRectangle& rect)
{
	if (point.x < rect.right && point.x > rect.left&& point.y < rect.top && point.y > rect.bottom)
		return true;
	else
		return false;
}

// Check whether two circles intersect.
// Params:
//  circle1 = The first circle.
//  circle2 = The second circle.
// Returns:
//   True if intersection, false otherwise.
bool CircleCircleIntersection(const Beta::Circle& circle1, const Beta::Circle& circle2)
{
	float dist = circle1.center.DistanceSquared(circle2.center);
	float radiiSqr = (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
	if (dist < radiiSqr)
		return true;
	else
		return false;
}

// Check whether two rectangles intersect.
// Params:
//  rect1 = The first rectangle.
//	rect2 = The second rectangle.
// Returns:
//   True if intersection, false otherwise.
bool RectangleRectangleIntersection(const Beta::BoundingRectangle& rect1, const Beta::BoundingRectangle& rect2)
{
	if (rect1.left > rect2.right)
		return false;
	if (rect1.right < rect2.left)
		return false;
	if (rect1.bottom > rect2.top)
		return false;
	if (rect1.top < rect2.bottom)
		return false;
	return true;
}

// Check whether a rectangle and circle intersect.
// Params:
//  rect = The rectangle.
//  circle  = The circle.
// Returns:
//   True if intersection, false otherwise.
bool RectangleCircleIntersection(const Beta::BoundingRectangle& rect, const Beta::Circle& circle)
{
	Beta::Vector2D clampPoint = circle.center;
	if (clampPoint.x > rect.right)
		clampPoint.x = rect.right;
	else if (clampPoint.x < rect.left)
		clampPoint.x = rect.left;

	if (clampPoint.y > rect.top)
		clampPoint.y = rect.top;
	else if (clampPoint.y < rect.bottom)
		clampPoint.y = rect.bottom;

	return clampPoint.DistanceSquared(circle.center) < (circle.radius * circle.radius);
}

// Check whether a moving point and line intersect.
// Params:
//  staticLine   = Start and end of first line segment.
//  movingPoint = Start and end of second line segment (usually a moving point).
//  intersection = Intersection point, if any.
//  t = The t value from the intersection calculation.
// Returns:
//   True if intersection, false otherwise.
bool MovingPointLineIntersection(const Beta::LineSegment& staticLine, const Beta::LineSegment& movingPoint, Beta::Vector2D& intersection, float& t)
{
	Beta::Vector2D velocity = movingPoint.end - movingPoint.start;
	if (velocity.DotProduct(staticLine.normal) == 0)
		return false;

	float intersectTime = (staticLine.normal.DotProduct(staticLine.start) - staticLine.normal.DotProduct(movingPoint.start)) / staticLine.normal.DotProduct(velocity);
	if (t < 0 || t > 1)
		return false;

	Beta::Vector2D intersectPoint = movingPoint.start + (velocity * intersectTime);
	if (!PointIsBetweenLines(intersectPoint, staticLine.start, staticLine.end, staticLine.normal))
		return false;
	return true;
}

// Modifies object's position, velocity, and rotation using simple point-line reflection.
// Params:
//  transform = Transform of the object that is being reflected.
//  rigidBody   = RigidBody of the object being reflected.
//  staticLine   = Start and end of first line segment.
//  movingPoint = Start and end of second line segment (usually a moving point).
//  intersection = Intersection point of the line and circle. 
void MovingPointLineReflection(Transform& transform, RigidBody& rigidBody, const Beta::LineSegment& staticLine, const Beta::LineSegment& movingPoint, const Beta::Vector2D& intersection)
{
	Beta::Vector2D reflectedPos = ReflectPointOverLine(movingPoint.end, staticLine);
	transform.SetTranslation(reflectedPos);

	Beta::Vector2D reflectedVel = (reflectedPos - intersection).Normalized();
	rigidBody.SetVelocity(reflectedVel * rigidBody.GetVelocity().Magnitude());

	float reflectedRot = atan2(reflectedVel.x, reflectedVel.y);
	transform.SetRotation(reflectedRot);
}

// Checks whether a point is between two parallel lines.
// Params:
//   point = The point in question.
//   firstLine = A point on the first line.
//   secondLine = A point on the second line.
//   normal = Normal vector to the two lines.
// Returns:
//   True if the point is between the two lines, false otherwise.
bool PointIsBetweenLines(const Beta::Vector2D& point, const Beta::Vector2D& firstLine, const Beta::Vector2D& secondLine, const Beta::Vector2D& normal)
{
	float distToStart = normal.DotProduct(firstLine);
	float distToEnd = normal.DotProduct(secondLine);
	float distToPoint = normal.DotProduct(point);

	if (distToPoint < distToStart && distToPoint < distToEnd)
		return false;
	if (distToPoint > distToStart && distToPoint > distToEnd)
		return false;
	return true;
}

// Reflects a point over a line.
// Params:
//   point = The point being reflected.
//   line = The line the point will be reflected over.
// Returns:
//   The reflected point.
Beta::Vector2D ReflectPointOverLine(const Beta::Vector2D& point, const Beta::LineSegment& line)
{
	Beta::Vector2D reflectedPoint = point - line.start;
	reflectedPoint = reflectedPoint - 2 * (reflectedPoint.DotProduct(line.normal)) * line.normal;
	return reflectedPoint + line.start;
}