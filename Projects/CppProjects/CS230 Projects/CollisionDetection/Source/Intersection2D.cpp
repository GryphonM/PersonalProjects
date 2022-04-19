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