//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright ? 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;
class GameObject;
typedef void(*CollisionEventHandler)(GameObject& callingObject, GameObject& otherObject);

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

enum class ColliderType
{
	Point,
	Circle,
	Rectangle
};

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Collider class - Detects collisions between objects
class Collider : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Allocate a new collider component.
	// Params:
	//   type = The type of collider (see the ColliderType enum).
	Collider(ColliderType type);

	// Set component pointers.
	void Initialize() override;

	// Draw collision shape
	virtual void Draw() = 0;

	// Check if two objects are colliding and send collision events.
	// Params:
	//	 other = Reference to the second collider component.
	void CheckCollision(const Collider& other);

	// Perform intersection test between two arbitrary colliders.
	// Params:
	//	 other = Reference to the second collider component.
	virtual bool IsCollidingWith(const Collider& other) const = 0;

	// Get the type of this component.
	ColliderType GetType() const;

	// Sets the collision handler function for the collider.
	// Params:
	//   handler = A pointer to the collision handler function.
	void SetCollisionHandler(CollisionEventHandler handler);

	// Component pointers
	// Note: These are PUBLIC to facilitate access 
	// through differing derived classes
	Transform* transform;
	RigidBody* rigidBody;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The type of collider used by this component.
	ColliderType type;

	// Function pointer for collision handler
	CollisionEventHandler handler;
};

//------------------------------------------------------------------------------
