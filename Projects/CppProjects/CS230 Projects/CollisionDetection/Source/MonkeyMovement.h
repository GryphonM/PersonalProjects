//------------------------------------------------------------------------------
//
// File Name:	MonkeyMovement.h
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

#include "Component.h"	// base class
#include "Vector2D.h"	// Vector2D

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class MonkeyMovement : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	MonkeyMovement();

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

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Moves horizontally based on input
	void MoveHorizontal() const;

	// Moves vertically based on input
	void MoveVertical() const;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Movement properties
	float monkeyWalkSpeed;
	float monkeyJumpSpeed;
	float groundHeight;
	Beta::Vector2D gravity;

	// Components
	Transform* transform;
	RigidBody* rigidBody;
};

//------------------------------------------------------------------------------
