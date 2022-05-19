//------------------------------------------------------------------------------
//
// File Name:	ColliderRectangle.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Collider.h"
#include <Vector2D.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ColliderRectangle : public Collider
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for rectangle collider.
	// Params:
	//   extents = The rectangle's extents (half-width, half-height).
	ColliderRectangle(const Beta::Vector2D& extents = Beta::Vector2D(0.5f, 0.5f));

	// Clone an collider and return a pointer to the cloned object.
	// Returns:
	//   A pointer to a collider.
	Component* Clone() const;

	// Debug drawing for colliders.
	void Draw() override;

	// Get the rectangle collider's extents (half-width, half-height).
	// Returns:
	//	 The extents of the rectangle.
	const Beta::Vector2D& GetExtents() const;

	// Set the rectangle collider's extents (half-width, half-height).
	// Params:
	//   extents = The new extents of the rectangle.
	void SetExtents(const Beta::Vector2D& extents);

	// Check for collision between a circle and another arbitrary collider.
	// Params:
	//	 other = Reference to the second circle collider component.
	// Returns:
	//	 Return the results of the collision check.
	bool IsCollidingWith(const Collider& other) const override;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Extents of the rectangle collider.
	Beta::Vector2D extents;
};

//------------------------------------------------------------------------------
