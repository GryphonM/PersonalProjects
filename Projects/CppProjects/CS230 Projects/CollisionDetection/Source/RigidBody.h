//------------------------------------------------------------------------------
//
// File Name:	RigidBody.h
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

#include "Component.h"	// inheritance
#include <Vector2D.h>	// Beta::Vector2D

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Transform;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class RigidBody : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	RigidBody();

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Clone() const override;

	// Initialize this component, grab pointers to other components from owner.
	void Initialize() override;

	// Reset acceleration.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt);

	// Update velocity and translation.
	// Params:
	//	 dt = Change in time (in seconds) since the last fixed update.
	void FixedUpdate(float dt);

	// Set the velocity of a rigid body.
	// Params:
	//	 velocity = Pointer to a velocity vector.
	void SetVelocity(const Beta::Vector2D& velocity);

	// Get the velocity of a rigid body.
	// Returns:
	//		A reference to the component's velocity structure.
	const Beta::Vector2D& GetVelocity() const;

	// Set the angular velocity of a rigid body.
	// Params:
	//	 velocity = New value for the rotational velocity.
	void SetAngularVelocity(float velocity);

	// Get the angular velocity of a rigid body.
	// Returns:
	//	 A float representing the new angular velocity.
	float GetAngularVelocity() const;

	// Set the mass of the rigid body.
	// Params:
	//   mass = The new mass of the rigid body.
	void SetMass(float mass);

	// Add a force to the object.
	// Params:
	//	 force = A force vector with direction and magnitude.
	void AddForce(const Beta::Vector2D& force);

	// Get the acceleration of a rigid body.
	// Returns:
	//	 A reference to the component's acceleration structure.
	const Beta::Vector2D& GetAcceleration() const;

	// Get the old translation (position) of a rigid body.
	// Returns: 
	//   A reference to the component's oldTranslation structure,
	const Beta::Vector2D& GetOldTranslation() const;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Velocity may be stored as a direction vector and speed scalar, instead.
	Beta::Vector2D	velocity;

	// Angular velocity, the speed and direction that the object rotates.
	float		angularVelocity;

	// Used when calculating acceleration due to forces.
	float		inverseMass;

	// The sum of all forces acting on an object
	Beta::Vector2D	forcesSum;

	// Acceleration = inverseMass * (sum of forces)
	Beta::Vector2D	acceleration;

	// Previous position.  May be used for resolving collisions.
	Beta::Vector2D	oldTranslation;

	// Transform component
	Transform*	transform;
};
//------------------------------------------------------------------------------
