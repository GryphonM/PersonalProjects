//------------------------------------------------------------------------------
//
// File Name:	MonkeyMovement.cpp
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
#include "MonkeyMovement.h"
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

// Constructor
MonkeyMovement::MonkeyMovement() : monkeyWalkSpeed(2.0f), monkeyJumpSpeed(3.0f),
	gravity(Vector2D(0, -4.0f)), transform(nullptr), rigidBody(nullptr), Component("Monkey")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* MonkeyMovement::Clone() const
{
	return new MonkeyMovement(*this);
}

// Initialize this component (happens at object creation).
void MonkeyMovement::Initialize()
{
	transform = dynamic_cast<Transform *>(GetOwner()->GetComponent("Transform"));
	rigidBody = dynamic_cast<RigidBody *>(GetOwner()->GetComponent("RigidBody"));
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void MonkeyMovement::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	MoveHorizontal();
	MoveVertical();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Moves horizontally based on input
void MonkeyMovement::MoveHorizontal() const
{
	// Movement
	if (EngineCore::GetInstance().GetModule<Input>()->CheckHeld(37))
	{
		// Move Left
		rigidBody->SetVelocity(Vector2D(-monkeyWalkSpeed, rigidBody->GetVelocity().y));
	}
	else if (EngineCore::GetInstance().GetModule<Input>()->CheckHeld(39))
	{
		// Move Right
		rigidBody->SetVelocity(Vector2D(monkeyWalkSpeed, rigidBody->GetVelocity().y));
	}
	else
	{
		// Stop Moving
		rigidBody->SetVelocity(Vector2D(0, rigidBody->GetVelocity().y));
	}
}

// Moves vertically based on input
void MonkeyMovement::MoveVertical()
{
	bool grounded = false;

	// Gravity
	float bottom = transform->GetTranslation().y - (0.5f * transform->GetScale().y);
	if (bottom > groundHeight)
	{
		rigidBody->AddForce(gravity);
		grounded = false;
	}
	else
	{
		transform->SetTranslation(Vector2D(transform->GetTranslation().x, groundHeight + (0.5f * transform->GetScale().y)));
		rigidBody->SetVelocity(Vector2D(rigidBody->GetVelocity().x, 0));
		grounded = true;
	}

	// Jump
	if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered(38))
	{
		if (grounded)
		{
			rigidBody->SetVelocity(Vector2D(rigidBody->GetVelocity().x, monkeyJumpSpeed));
			grounded = false;
		}
	}
}