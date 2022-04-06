//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.1.3 Assignment: Object Management
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PlayerShip.h"
#include "Transform.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "Archetypes.h"
#include "Space.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Non-default constructor
// Params:
//   forwardThrust = Amount of force added to the ship when thrusters are activated.
//   maximumSpeed  = Maximum attainable speed of the ship.
//   rotationSpeed = Speed at which the ship rotates.
//   bulletSpeed   = Speed at which bullets move when fired by ship.
PlayerShip::PlayerShip(float forwardThrust_, float maximumSpeed_, float rotationSpeed_, float bulletSpeed_) :
	forwardThrust(forwardThrust_), maximumSpeed(maximumSpeed_), rotationSpeed(rotationSpeed_), bulletSpeed(bulletSpeed_),
	bulletArchetype(nullptr), transform(nullptr), rigidBody(nullptr), Component("PlayerShip")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* PlayerShip::Clone() const
{
	return new PlayerShip(*this);
}

// Initialize this component (happens at object creation).
void PlayerShip::Initialize()
{
	bulletArchetype = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bullet");
	transform = dynamic_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	rigidBody = dynamic_cast<RigidBody*>(GetOwner()->GetComponent("RigidBody"));
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void PlayerShip::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	Move();
	Rotate();
	Shoot();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Move forward when up arrow is pressed
void PlayerShip::Move() const
{
	if (EngineCore::GetInstance().GetModule<Input>()->CheckHeld(38))
	{
		if (rigidBody->GetVelocity().Magnitude() < maximumSpeed)
			rigidBody->AddForce(Vector2D(forwardThrust, 0).Rotate(transform->GetRotation()));
		else
			rigidBody->SetVelocity(Vector2D(maximumSpeed, 0).Rotate(transform->GetRotation()));
	}
	else
	{
		if (!AlmostEqual(rigidBody->GetVelocity().Magnitude(), 0, 0.1f))
			rigidBody->SetVelocity(Vector2D((rigidBody->GetVelocity().Magnitude() - 0.025f * forwardThrust), 0).Rotate(transform->GetRotation()));
		else
			rigidBody->SetVelocity(Vector2D(0, 0));
	}
}

// Rotate when left or right arrow key is pressed
void PlayerShip::Rotate() const
{
	if (EngineCore::GetInstance().GetModule<Input>()->CheckHeld(37))
		rigidBody->SetAngularVelocity(-rotationSpeed);
	else if (EngineCore::GetInstance().GetModule<Input>()->CheckHeld(39))
		rigidBody->SetAngularVelocity(rotationSpeed);
	else
		rigidBody->SetAngularVelocity(0);
}

// Shoot projectiles when space is pressed
void PlayerShip::Shoot() const
{
	if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered(' '))
	{
		GameObject* bullet = new GameObject(*bulletArchetype);
		GetOwner()->GetSpace()->GetObjectManager().AddObject(*bullet);
		dynamic_cast<Transform*>(bullet->GetComponent("Transform"))->SetTranslation(transform->GetTranslation());
		dynamic_cast<RigidBody*>(bullet->GetComponent("RigidBody"))->SetVelocity(Vector2D(bulletSpeed, 0).Rotate(transform->GetRotation()));
	}
}