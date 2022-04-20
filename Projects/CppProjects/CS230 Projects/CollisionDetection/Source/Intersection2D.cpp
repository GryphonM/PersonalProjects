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