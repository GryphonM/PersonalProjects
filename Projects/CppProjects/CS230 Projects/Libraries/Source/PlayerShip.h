//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.h
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

#include "Component.h" // inheritance

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class PlayerShip : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Non-default constructor
	// Params:
	//   forwardThrust = Amount of force added to the ship when thrusters are activated.
	//   maximumSpeed  = Maximum attainable speed of the ship.
	//   rotationSpeed = Speed at which the ship rotates.
	//   bulletSpeed   = Speed at which bullets move when fired by ship.
	//   deathDuration = The amount of time the death "animation" will last.
	PlayerShip(float forwardThrust = 3.0f, float maximumSpeed = 2.0f, float rotationSpeed = 3.14159f,
		float bulletSpeed = 4.0f, float deathDuration = 2.0f);

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

	// Return the player's current score.
	unsigned GetScore() const;

	// Increase the player's score by the given amount.
	void IncreaseScore(unsigned amount);

	// Enables the Missile
	void EnableMissile();

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Move forward when up arrow is pressed
	void Move() const;

	// Rotate when left or right arrow key is pressed
	void Rotate() const;

	// Shoot projectiles when space is pressed
	void Shoot();

	// Handles the missile firing
	void MissileFire(float dt);

	// Lays a bomb when the down key is pressed
	void LayBomb();

	// Play death "animation"
	void DeathSequence(float dt);

	// Collision handler for PlayerShip objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	friend void PlayerShipCollisionHandler(GameObject& object, GameObject& other);

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Movement properties
	float forwardThrust;
	float maximumSpeed;
	float rotationSpeed;
	float bulletSpeed;

	// Bullet archetype
	GameObject* bulletArchetype;

	// Homing Missile
	GameObject* missileArchetype;
	bool hasMissile;
	float missileWait;
	float missileTimer;
	Beta::Color readyColor;
	Beta::Color normalColor;
	float flashDuration;
	float flashTimer;

	// Bomb
	GameObject* bombArchetype;

	// Components
	Transform* transform;
	RigidBody* rigidBody;

	// Scoring
	unsigned score;

	// Death
	float deathDuration;
	float timer;
	float blinkDuration;
	float blinkTimer;
	Beta::Color deadColor;
	float spinSpeed;
	bool blinkOn;
	bool isDying;
};

//------------------------------------------------------------------------------
