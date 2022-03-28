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
	const float ShipSpeed = 0.01f;
	const float StopDistance = 0.25f;
	
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

		float angleToMouse = atan2(mouseDir.y, mouseDir.x);
		//transform->SetRotation(angleToMouse);

		if (mouseDir.Magnitude() > StopDistance)
		{
			rigidBody->AddForce(Vector2D(1, 0).Rotate(angleToMouse) * ShipSpeed);
		}
		else
		{
			rigidBody->SetVelocity(Vector2D(0, 0));
		}
	}
}