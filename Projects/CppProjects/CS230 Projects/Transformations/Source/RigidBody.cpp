//------------------------------------------------------------------------------
//
// File Name:	RigidBody.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.0.7 Assignment: Transformations
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "RigidBody.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   transform - The transform of the object.
RigidBody::RigidBody(Transform* transform_) : 
	velocity(Beta::Vector2D(0, 0)), angularVelocity(0), inverseMass(1.0f), 
	forcesSum(Beta::Vector2D(0, 0)), acceleration(Beta::Vector2D(0, 0)), 
	oldTranslation(transform_->GetTranslation()), transform(transform_)
{
}

// Reset acceleration.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void RigidBody::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	
	acceleration = forcesSum / inverseMass;
	forcesSum = 0;
}

// Update velocity and translation.
// Params:
//	 dt = Change in time (in seconds) since the last fixed update.
void RigidBody::FixedUpdate(float dt)
{
	//UNREFERENCED_PARAMETER(dt);
	
	velocity += acceleration;
	oldTranslation = transform->GetTranslation();
	transform->SetTranslation(oldTranslation + (velocity * dt));
	transform->SetRotation(transform->GetRotation() + (angularVelocity * dt));
}

// Set the velocity of a rigid body.
// Params:
//	 velocity = Pointer to a velocity vector.
void RigidBody::SetVelocity(const Beta::Vector2D& velocity_)
{
	velocity = velocity_;
}

// Get the velocity of a rigid body.
// Returns:
//		A reference to the component's velocity structure.
const Beta::Vector2D& RigidBody::GetVelocity() const
{
	return velocity;
}

// Set the angular velocity of a rigid body.
// Params:
//	 velocity = New value for the rotational velocity.
void RigidBody::SetAngularVelocity(float velocity_)
{
	angularVelocity = velocity_;
}

// Get the angular velocity of a rigid body.
// Returns:
//	 A float representing the new angular velocity.
float RigidBody::GetAngularVelocity() const
{
	return angularVelocity;
}

// Set the mass of the rigid body.
// Params:
//   mass = The new mass of the rigid body.
void RigidBody::SetMass(float mass)
{
	inverseMass = 1 / mass;
}

// Add a force to the object.
// Params:
//	 force = A force vector with direction and magnitude.
void RigidBody::AddForce(const Beta::Vector2D& force)
{
	forcesSum += force;
}

// Get the acceleration of a rigid body.
// Returns:
//	 A reference to the component's acceleration structure.
const Beta::Vector2D& RigidBody::GetAcceleration() const
{
	return acceleration;
}

// Get the old translation (position) of a rigid body.
// Returns: 
//   A reference to the component's oldTranslation structure,
const Beta::Vector2D& RigidBody::GetOldTranslation() const
{
	return oldTranslation;
}