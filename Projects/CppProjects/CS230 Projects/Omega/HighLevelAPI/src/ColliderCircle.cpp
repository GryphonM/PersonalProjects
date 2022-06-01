//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.cpp
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
#include "ColliderPoint.h"
#include "ColliderCircle.h"
#include "ColliderRectangle.h"
#include "Transform.h"
#include "Intersection2D.h"
#include "FileStream.h"

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Constructor for circle collider.
// Params:
//   radius = The radius of the circle.
ColliderCircle::ColliderCircle(float radius_) : radius(radius_), Collider(ColliderType::Circle)
{
}

// Clone an collider and return a pointer to the cloned object.
// Returns:
//   A pointer to a collider.
Component* ColliderCircle::Clone() const
{
	return new ColliderCircle(*this);
}

// Debug drawing for colliders.
void ColliderCircle::Draw()
{
	Beta::DebugDraw& debugDraw = *Beta::EngineCore::GetInstance().GetModule<Beta::DebugDraw>();
	debugDraw.AddCircle(transform->GetTranslation(), radius);
}

// Get the circle collider's radius.
// Returns:
//	 The circle collider's radius.
float ColliderCircle::GetRadius() const
{
	return radius;
}

// Set the circle collider's radius.
// Params:
//   radius = The circle collider's new radius.
void ColliderCircle::SetRadius(float radius_)
{
	radius = radius_;
}

// Check for collision between a circle and another arbitrary collider.
// Params:
//	 other = Reference to the second circle collider component.
// Returns:
//	 Return the results of the collision check.
bool ColliderCircle::IsCollidingWith(const Collider& other) const
{
	if (other.GetType() == ColliderType::Circle)
	{
		return CircleCircleIntersection(Beta::Circle(transform->GetTranslation(), radius),
			Beta::Circle(other.transform->GetTranslation(), dynamic_cast<const ColliderCircle&>(other).radius));
	}
	else if (other.GetType() == ColliderType::Point)
	{
		return PointCircleIntersection(other.transform->GetTranslation(),
			Beta::Circle(transform->GetTranslation(), radius));
	}
	else if (other.GetType() == ColliderType::Rectangle)
	{
		return RectangleCircleIntersection(Beta::BoundingRectangle(other.transform->GetTranslation(), 
			dynamic_cast<const ColliderRectangle&>(other).GetExtents()),
			Beta::Circle(transform->GetTranslation(), radius));
	}
	else
	{
		return other.IsCollidingWith(*this);
	}
	return false;
}

// Loads object data from a file.
// Params:
//   stream = The stream for the file we want to read from.
void ColliderCircle::Deserialize(FileStream& stream)
{
	stream.ReadVariable("radius", radius);
}

// Saves object data to a file.
// Params:
//   stream = The stream for the file we want to write to.
void ColliderCircle::Serialize(FileStream& stream) const
{
	stream.WriteVariable("radius", radius);
}