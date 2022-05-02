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
class PlayerShip;
class Sprite;
class ColliderCircle;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------
class Bomb : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Default Constructor
	// Params:
	//   explosionRadius_ = The radius the bomb explodes with
	Bomb(float explosionRadius_ = 1.0f);

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

	// Gettor for exploding
	// Returns:
	//   the value of exploding
	bool IsExploding();
private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Collision handler for Bomb objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	friend void BombCollisionHandler(GameObject& object, GameObject& other);

	// Handles the start of the explosion
	void StartExplosion();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------
	float explosionRadius;
	float waitDuration;
	float waitTimer;
	float explosionDuration;
	float explosionTimer;
	bool exploding;

	float blinkDuration;
	float blinkTime;
	bool blink;
	Beta::Color normalColor;
	Beta::Color blinkColor;

	Transform* transform;
	PlayerShip* player;
	ColliderCircle* collider;
	Sprite* sprite;
};