//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Level1.h"

// Systems
#include "Space.h"

// Levels
#include "Level2.h"

//------------------------------------------------------------------------------

namespace Levels
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 1.
	Level1::Level1()
		: Level("Level1")
	{
	}

	// Load the resources associated with Level 1.
	void Level1::Load()
	{

	}

	// Initialize the memory associated with Level 1.
	void Level1::Initialize()
	{

	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level1::Update(float dt)
	{
		// Tell compiler we are not using this parameter
		UNREFERENCED_PARAMETER(dt);
	}

	// Shutdown any memory associated with Level 1.
	void Level1::Shutdown()
	{

	}

	// Unload the resources associated with Level 1.
	void Level1::Unload()
	{

	}
}
