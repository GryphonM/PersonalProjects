//------------------------------------------------------------------------------
//
// File Name:	Asteroid.h
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

class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Asteroid : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Asteroid constructor
	// Params:
	//   speedMin = Minimum of range for asteroid movement speed.
	//   speedMax = Maximum of range for asteroid movement speed.
	//   basePointsValue = Point value for largest asteroid.
	//   sizePointsModifier = Multiplicative scale applied to points for smaller asteroids.
	//   spawnScaleModifier = Percentage of original asteroid's scale to use for new asteroids.
	Asteroid(float speedMin = 0.5f, float speedMax = 1.0f, unsigned basePointsValue = 20,
		float sizePointsModifier = 0.5f, float spawnScaleModifier = 0.8f);

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Clone() const override;

	// Initialize this component (happens at object creation).
	void Initialize() override;

	// Get the value of this object for increasing the player's score.
	unsigned GetPointValue() const;

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Collision handler for Asteroid objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	friend void AsteroidCollisionHandler(GameObject& object, GameObject& other);

	// Set position of asteroid based on origin
	void SetPosition();

	// Set velocity based on size
	void SetVelocity();

	// Generate new asteroids based off this asteroid
	void SpawnNewAsteroids();

	//------------------------------------------------------------------------------
	// Private Structures:
	//------------------------------------------------------------------------------

	enum class Size
	{
		Small,
		Medium,
		Large,
	};

	enum class Location
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Properties (save to/load from file)
	float speedMin;
	float speedMax;
	unsigned basePointsValue;
	float sizePointsModifier;
	float spawnScaleModifier;

	// Other variables
	Size size;
	Location location;
	bool spawnedNew;
	mutable bool pointsGiven;

	// Components
	Transform* transform;
	RigidBody* rigidBody;
};

//------------------------------------------------------------------------------
