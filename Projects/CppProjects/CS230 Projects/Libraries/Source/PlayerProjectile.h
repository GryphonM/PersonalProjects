//------------------------------------------------------------------------------
//
// File Name:	PlayerProjectile.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class PlayerShip;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class PlayerProjectile : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Default constructor
	PlayerProjectile();

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Clone() const override;

	// Initialize this component (happens at object creation).
	void Initialize() override;

	// Set the object that spawned this object
	void SetSpawner(PlayerShip* player);

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Collision handler for PlayerProjectile objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	friend void PlayerProjectileCollisionHandler(GameObject& object, GameObject& other);

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Who spawned this object?
	PlayerShip* player;
};

//------------------------------------------------------------------------------
