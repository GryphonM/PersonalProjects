//------------------------------------------------------------------------------
//
// File Name:	ScreenWrap.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.1.6 Assignment: Collision Detection
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "ScreenWrap.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Default constructor
ScreenWrap::ScreenWrap() : transform(nullptr), rigidBody(nullptr), Component("ScreenWrap")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* ScreenWrap::Clone() const
{
	return new ScreenWrap(*this);
}

// Initialize this component (happens at object creation).
void ScreenWrap::Initialize()
{
	transform = GetOwner()->GetComponent<Transform>();
	rigidBody = GetOwner()->GetComponent<RigidBody>();
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void ScreenWrap::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	
	BoundingRectangle screen = EngineCore::GetInstance().GetModule<GraphicsEngine>()->GetDefaultCamera().GetScreenWorldDimensions();
	Vector2D position = GetOwner()->GetComponent<Transform>()->GetTranslation();
	Vector2D scale = GetOwner()->GetComponent<Transform>()->GetScale();
	Vector2D velocity = GetOwner()->GetComponent<RigidBody>()->GetVelocity();

	if (velocity.x > 0 && position.x > screen.right + scale.x)
	{
		Vector2D newPos = Vector2D(screen.left - scale.x, position.y);
		GetOwner()->GetComponent<Transform>()->SetTranslation(newPos);
	}

	if (velocity.x < 0 && position.x < screen.left - scale.x)
	{
		Vector2D newPos = Vector2D(screen.right + scale.x, position.y);
		GetOwner()->GetComponent<Transform>()->SetTranslation(newPos);
	}

	if (velocity.y > 0 && position.y > screen.top + scale.y)
	{
		Vector2D newPos = Vector2D(position.x, screen.bottom - scale.y);
		GetOwner()->GetComponent<Transform>()->SetTranslation(newPos);
	}

	if (velocity.y < 0 && position.y < screen.bottom - scale.y)
	{
		Vector2D newPos = Vector2D(position.x, screen.top + scale.y);
		GetOwner()->GetComponent<Transform>()->SetTranslation(newPos);
	}
}