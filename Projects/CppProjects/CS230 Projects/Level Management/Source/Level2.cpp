//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
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
#include "Level2.h"

// Systems
#include "Space.h"

using namespace Beta;

//------------------------------------------------------------------------------

namespace Levels
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2::Level2()
		: Level("Level2"), lives(2), maxHealth(2)
	{
	}

	// Load resources associated with Level 2.
	void Level2::Load()
	{
		std::cout << "Level2::Load" << std::endl;
	}

	// Create objects associated with Level 2.
	void Level2::Initialize()
	{
		std::cout << "Level2::Initialize" << std::endl;
		currentHealth = maxHealth;
	}

	// Update Level 2.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level2::Update(float dt)
	{
		std::cout << "Level2::Update" << std::endl;
		// Tell compiler we are not using this parameter
		UNREFERENCED_PARAMETER(dt);

		--currentHealth;
		if (currentHealth == 0)
		{
			--lives;
			if (lives == 0)
				EngineCore::GetInstance().Stop();
			else
				EngineCore::GetInstance().GetModule<Space>()->RestartLevel();
		}
	}

	// Deallocate objects associated with Level 2.
	void Level2::Shutdown()
	{
		std::cout << "Level2::Shutdown" << std::endl;
	}

	// Unload resources associated with Level 2.
	void Level2::Unload()
	{
		std::cout << "Level2::Unload" << std::endl;
	}
}
