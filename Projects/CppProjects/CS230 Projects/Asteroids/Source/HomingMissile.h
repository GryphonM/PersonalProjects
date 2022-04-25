//------------------------------------------------------------------------------
//
// File Name:	HomingMissile
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.1.7 Assignment: Asteroids
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // inheritance

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;
class PlayerShip;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------
class HomingMissile : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Default Constructor
	// Params:
	//   speed_ = The speed at which the missile approaches asteroids
	HomingMissile(float speed_ = 3.0f);

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Clone() const override;

	// Initialize this component (happens at object creation).
	void Initialize() override;

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void Update(float dt) override;

	// Set the object that spawned this object
	// Params:
	//   player_ = the object to set the spawner to
	void SetSpawner(PlayerShip* player_);
private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Collision handler for PlayerProjectile objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	friend void MissileCollisionHandler(GameObject& object, GameObject& other);

	// Starts the explosion sequence
	void Explode();

	// Finds the nearest Asteroid and sets it as the target
	void SetTarget();

	// Find the direction toward the target and move that way
	void Move();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------
	PlayerShip* player;
	GameObject* target;

	float speed;
	float explosionRadius;
	Transform* transform;
	RigidBody* rigidBody;
};