//------------------------------------------------------------------------------
//
// File Name:	Behaviors.cpp
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
#include "Behaviors.h"
#include "Transform.h"
#include "RigidBody.h"

using namespace Beta;

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Ship Variables:
	//------------------------------------------------------------------------------
	const float ShipSpeed = 1.0f;
	const float StopDistance = 0.4f;

	//------------------------------------------------------------------------------
	// Monkey Variables:
	//------------------------------------------------------------------------------
	const float MonkeySpeed = 2.0f;
	const float JumpSpeed = 3.0f;
	const float Gravity = 4.0f;
	bool grounded = true;
	
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Movement behavior for the triangle/ship.
	// Params:
	//	 transform = The transform component of the ship.
	//   rigidBody = The rigid body of the ship.
	void UpdateShip(Transform* transform, RigidBody* rigidBody)
	{
		GraphicsEngine* Graphics = EngineCore::GetInstance().GetModule<GraphicsEngine>();
		Input* input = EngineCore::GetInstance().GetModule<Input>();

		Vector2D pos = transform->GetTranslation();
		Vector2D mousePos = Graphics->GetDefaultCamera().ScreenToWorldPosition(input->GetCursorPosition());
		Vector2D mouseDir = mousePos - pos;

		if (mouseDir.Magnitude() > StopDistance)
		{
			float angleToMouse = atan2(mouseDir.y, mouseDir.x);
			transform->SetRotation(angleToMouse);
			rigidBody->SetVelocity(Vector2D(1, 0).Rotate(angleToMouse) * ShipSpeed);
		}
		else
		{
			rigidBody->SetVelocity(Vector2D(0, 0));
		}
	}

	// Movement behavior for the monkey.
	// Params:
	//	 transform = The transform component of the monkey.
	//   rigidBody = The rigid body of the monkey.
	void UpdateMonkey(Transform* transform, RigidBody* rigidBody)
	{
		Input* input = EngineCore::GetInstance().GetModule<Input>();
		BoundingRectangle screen = EngineCore::GetInstance().GetModule<GraphicsEngine>()->GetDefaultCamera().GetScreenWorldDimensions();

		// Gravity
		float bottom = transform->GetTranslation().y - (0.5f * transform->GetScale().y);
		if (bottom > screen.bottom)
		{
			rigidBody->AddForce(Vector2D(0, -Gravity));
			grounded = false;
		}
		else
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x, screen.bottom + (0.5f * transform->GetScale().y)));
			rigidBody->SetVelocity(Vector2D(rigidBody->GetVelocity().x, 0));
			grounded = true;
		}

		// Movement
		if (input->CheckHeld('A'))
		{
			// Move Left
			rigidBody->SetVelocity(Vector2D(-MonkeySpeed, rigidBody->GetVelocity().y));
		}
		else if (input->CheckHeld('D'))
		{
			// Move Right
			rigidBody->SetVelocity(Vector2D(MonkeySpeed, rigidBody->GetVelocity().y));
		}
		else
		{
			// Stop Moving
			rigidBody->SetVelocity(Vector2D(0, rigidBody->GetVelocity().y));
		}

		// Jump
		if (input->CheckTriggered(' '))
		{
			if (grounded)
			{
				rigidBody->SetVelocity(Vector2D(rigidBody->GetVelocity().x, JumpSpeed));
				grounded = false;
			}
		}
	}
}