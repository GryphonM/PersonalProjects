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
#include "MeshHelper.h"

// Components
#include "Sprite.h"

// Levels
#include "Level2.h"

//------------------------------------------------------------------------------

using namespace Beta;

namespace Levels
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 1.
	Level1::Level1()
		: Level("Level1"), mesh(nullptr), sprite(nullptr), lives(256)
	{
	}

	// Load the resources associated with Level 1.
	void Level1::Load()
	{
		std::cout << "Level1::Load" << std::endl;

		mesh = CreateTriangleMesh(Colors::Red, Colors::Green, Colors::Blue);
	}

	// Initialize the memory associated with Level 1.
	void Level1::Initialize()
	{
		std::cout << "Level1::Initialize" << std::endl;

		sprite = new Sprite(mesh);
	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level1::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		// TO DO:
		sprite->Draw();

		lives--;
		if (lives <= 0)
		{
			Level2* level = new Level2;
			EngineCore::GetInstance().GetModule<Space>()->SetLevel(level);
		}
	}

	// Shutdown any memory associated with Level 1.
	void Level1::Shutdown()
	{
		std::cout << "Level1::Shutdown" << std::endl;

		delete sprite;
	}

	// Unload the resources associated with Level 1.
	void Level1::Unload()
	{
		std::cout << "Level1::Unload" << std::endl;

		delete mesh;
	}
}
