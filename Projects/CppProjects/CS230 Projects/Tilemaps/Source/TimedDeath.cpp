//------------------------------------------------------------------------------
//
// File Name:	TimedDeath.cpp
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
#include "TimedDeath.h"
#include "Transform.h"
#include "GameObject.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Non-default constructor
// Params:
//   timeUntilDeath = Amount of time until the object self-destructs.
TimedDeath::TimedDeath(float timeUntilDeath_) : timeUntilDeath(timeUntilDeath_), Component("TimedDeath")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* TimedDeath::Clone() const
{
	return new TimedDeath(*this);
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void TimedDeath::Update(float dt)
{
	timeUntilDeath -= dt;
	if (timeUntilDeath <= 0)
		GetOwner()->Destroy();
}