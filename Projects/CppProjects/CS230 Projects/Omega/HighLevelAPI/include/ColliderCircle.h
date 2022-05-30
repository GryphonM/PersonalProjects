//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.h
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

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ColliderCircle : public Collider
{
public:
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for circle collider.
	// Params:
	//   radius = The radius of the circle.
	ColliderCircle(float radius = 0.5f);

	// Clone an collider and return a pointer to the cloned object.
	// Returns:
	//   A pointer to a collider.
	Component* Clone() const;

	// Debug drawing for colliders.
	void Draw() override;

	// Get the circle collider's radius.
	// Returns:
	//	 The circle collider's radius.
	float GetRadius() const;

	// Set the circle collider's radius.
	// Params:
	//   radius = The circle collider's new radius.
	void SetRadius(float radius);

	// Check for collision between a circle and another arbitrary collider.
	// Params:
	//	 other = Reference to the second circle collider component.
	// Returns:
	//	 Return the results of the collision check.
	bool IsCollidingWith(const Collider& other) const override;

	// Loads object data from a file.
	// Params:
	//   stream = The stream for the file we want to read from.
	virtual void Deserialize(FileStream& stream) override;

	// Saves object data to a file.
	// Params:
	//   stream = The stream for the file we want to write to.
	virtual void Serialize(FileStream& stream) const override;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Radius of the circle collider.
	float radius;
};

//------------------------------------------------------------------------------
