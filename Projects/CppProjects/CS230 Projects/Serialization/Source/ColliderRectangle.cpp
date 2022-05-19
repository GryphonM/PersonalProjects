//------------------------------------------------------------------------------
//
// File Name:	ColliderRectangle.cpp
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
#include "GameObject.h"
#include "Transform.h"
#include "Intersection2D.h"

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Constructor for rectangle collider.
// Params:
//   extents = The rectangle's extents (half-width, half-height).
ColliderRectangle::ColliderRectangle(const Beta::Vector2D& extents_) : 
	extents(extents_), Collider(ColliderType::Rectangle)
{
}

// Clone an collider and return a pointer to the cloned object.
// Returns:
//   A pointer to a collider.
Component* ColliderRectangle::Clone() const
{
	return new ColliderRectangle(*this);
}

// Debug drawing for colliders.
void ColliderRectangle::Draw()
{
	Beta::DebugDraw& debugDraw = *Beta::EngineCore::GetInstance().GetModule<Beta::DebugDraw>();
	debugDraw.AddRectangle(transform->GetTranslation(), extents);
}

// Get the rectangle collider's extents (half-width, half-height).
// Returns:
//	 The extents of the rectangle.
const Beta::Vector2D& ColliderRectangle::GetExtents() const
{
	return extents;
}

// Set the rectangle collider's extents (half-width, half-height).
// Params:
//   extents = The new extents of the rectangle.
void ColliderRectangle::SetExtents(const Beta::Vector2D& extents_)
{
	extents = extents_;
}

// Check for collision between a circle and another arbitrary collider.
// Params:
//	 other = Reference to the second circle collider component.
// Returns:
//	 Return the results of the collision check.
bool ColliderRectangle::IsCollidingWith(const Collider& other) const
{
	if (other.GetType() == ColliderType::Circle)
	{
		return RectangleCircleIntersection(Beta::BoundingRectangle(transform->GetTranslation(), extents),
			Beta::Circle(other.transform->GetTranslation(), dynamic_cast<const ColliderCircle &>(other).GetRadius()));
	}
	else if (other.GetType() == ColliderType::Point)
	{
		return PointRectangleIntersection(other.transform->GetTranslation(), 
			Beta::BoundingRectangle(transform->GetTranslation(), extents));
	}
	else if (other.GetType() == ColliderType::Rectangle)
	{
		return RectangleRectangleIntersection(Beta::BoundingRectangle(transform->GetTranslation(), extents), 
			Beta::BoundingRectangle(other.transform->GetTranslation(), 
				dynamic_cast<const ColliderRectangle &>(other).GetExtents()));
	}
	else if (other.GetType() == ColliderType::Tilemap)
	{
		return other.IsCollidingWith(*this);
	}
	return false;
}