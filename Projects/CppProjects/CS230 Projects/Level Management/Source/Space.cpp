//------------------------------------------------------------------------------
//
// File Name:	Space.cpp
// Author(s):	Jeremy Kings
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"

#include "Level.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor(s)
Space::Space(const std::string& name)
	: BetaObject(name)
{
}

// Destructor
Space::~Space()
{

}

// Updates the state manager and object manager.
void Space::Update(float dt)
{
	// TO DO: Remove this once dt is actually being used
	// Tell compiler we are not using this parameter
	UNREFERENCED_PARAMETER(dt);
}

// Shuts down the object manager
void Space::Shutdown()
{

}

// Accessors
bool Space::IsPaused() const
{
	return false;
}

// Returns the name of the level currently running in this space.
const std::string& Space::GetLevelName() const
{
	return "";
}

// Pauses the space, preventing objects from being updated, but objects are still drawn.
void Space::SetPaused(bool value)
{

}

void Space::SetLevel(Level* level)
{
	level->SetOwner(this);

	// TO DO: Set next level to given param

}

// Restarts the current level (next level = current)
void Space::RestartLevel()
{

}

// Game State Update
void Space::ChangeLevel()
{

}
