//------------------------------------------------------------------------------
//
// File Name:	ColliderPoint.cpp
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

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Constructor for point collider.
ColliderPoint::ColliderPoint() : Collider(ColliderType::Point)
{
}

// Clone an collider and return a pointer to the cloned object.
// Returns:
//   A pointer to a collider.
Component* ColliderPoint::Clone() const
{
	return new ColliderPoint(*this);
}

// Debug drawing for colliders.
void ColliderPoint::Draw()
{
	Beta::DebugDraw& debugDraw = *Beta::EngineCore::GetInstance().GetModule<Beta::DebugDraw>();
	debugDraw.AddCircle(transform->GetTranslation(), 0.1f);
}

// Check for collision between a point and another arbitrary collider.
// Params:
//	 other = Reference to the second point collider component.
// Returns:
//	 Return the results of the collision check.
bool ColliderPoint::IsCollidingWith(const Collider& other) const
{
	if (other.GetType() == ColliderType::Circle)
	{
		PointCircleIntersection(transform->GetTranslation(), 
			Beta::Circle(other.transform->GetTranslation(), dynamic_cast<const ColliderCircle&>(other).GetRadius()));
	}
	else if (other.GetType() == ColliderType::Rectangle)
	{
		PointRectangleIntersection(transform->GetTranslation(),
			Beta::BoundingRectangle(other.transform->GetTranslation(), dynamic_cast<const ColliderRectangle&>(other).GetExtents()));
	}
}