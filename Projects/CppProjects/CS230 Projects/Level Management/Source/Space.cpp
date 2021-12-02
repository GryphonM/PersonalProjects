//------------------------------------------------------------------------------
//
// File Name:	Space.cpp
// Author(s):	Jeremy Kings
// Project:		BetaEngine
// Course:		CS230
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"

#include "Level.h"
#include "Level1.h"
#include "Level2.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor(s)
Space::Space(const std::string& name)
	: BetaObject(name), paused(false), 
	currentLevel(nullptr), nextLevel(nullptr)
{
}

// Destructor
Space::~Space()
{
	delete currentLevel;
	delete nextLevel;
}

// Updates the state manager and object manager.
void Space::Update(float dt)
{
	std::cout << "Space::Update" << std::endl;
	if (nextLevel != nullptr)
		Space::ChangeLevel();
	if (currentLevel != nullptr && !paused)
		currentLevel->Update(dt);
}

// Shuts down the object manager
void Space::Shutdown()
{
	if (currentLevel != nullptr)
	{
		currentLevel->Shutdown();
		currentLevel->Unload();
		nextLevel->Shutdown();
		nextLevel->Unload();
		delete currentLevel;
		delete nextLevel;
	}
}

// Accessors
bool Space::IsPaused() const
{
	return paused;
}

// Returns the name of the level currently running in this space.
const std::string& Space::GetLevelName() const
{
	return BetaObject::GetName();
}

// Pauses the space, preventing objects from being updated, but objects are still drawn.
void Space::SetPaused(bool value)
{
	paused = value;
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
