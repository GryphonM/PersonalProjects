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
#include "Sprite.h"
#include "GameObject.h"
#include "Space.h"
#include "FileStream.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Friend Functions:
//------------------------------------------------------------------------------

// Map collision handler for Monkey objects.
// Params:
//   object = The monkey object.
//   collision = Which sides the monkey collided on.
void MonkeyMapCollisionHandler(GameObject& object, const MapCollision& collision)
{
	if (collision.bottom)
		dynamic_cast<MonkeyMovement*>(object.GetComponent("Monkey"))->onGround = true;
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
MonkeyMovement::MonkeyMovement() : monkeyWalkSpeed(2.0f), monkeyJumpSpeed(3.0f), onGround(false),
	gravity(Vector2D(0, -4.0f)), transform(nullptr), rigidBody(nullptr), sprite(nullptr), Component("Monkey")
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
	sprite = dynamic_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
	dynamic_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetMapCollisionHandler(MonkeyMapCollisionHandler);
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

// Loads object data from a file.
// Params:
//   stream = The stream for the file we want to read from.
void MonkeyMovement::Deserialize(FileStream& stream)
{
	stream.ReadVariable("monkeyWalkSpeed", monkeyWalkSpeed);
	stream.ReadVariable("monkeyJumpSpeed", monkeyJumpSpeed);
	stream.ReadVariable("gravity", gravity);
}

// Saves object data to a file.
// Params:
//   stream = The stream for the file we want to write to.
void MonkeyMovement::Serialize(FileStream& stream) const
{
	stream.WriteVariable("monkeyWalkSpeed", monkeyWalkSpeed);
	stream.WriteVariable("monkeyJumpSpeed", monkeyJumpSpeed);
	stream.WriteVariable("gravity", gravity);
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
	// Gravity
	rigidBody->AddForce(gravity);

	if (rigidBody->GetVelocity().y < -0.25f)
		onGround = false;

	// Jump
	if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered(38))
	{
		if (onGround)
		{
			rigidBody->SetVelocity(Vector2D(rigidBody->GetVelocity().x, monkeyJumpSpeed));
			onGround = false;
		}
	}
}