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

		// TO DO: Create a mesh with 1 triangle using CreateTriangleMesh
	}

	// Initialize the memory associated with Level 1.
	void Level1::Initialize()
	{
		std::cout << "Level1::Initialize" << std::endl;

		// TO DO: Create a new sprite
	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level1::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		// TO DO:
		// Draw the sprite

		// Decrease lives counter by 1

		// If lives reaches 0, change state to Level2
	}

	// Shutdown any memory associated with Level 1.
	void Level1::Shutdown()
	{
		std::cout << "Level1::Shutdown" << std::endl;

		// TO DO: Delete the sprite
	}

	// Unload the resources associated with Level 1.
	void Level1::Unload()
	{
		std::cout << "Level1::Unload" << std::endl;

		// TO DO: Delete the mesh
	}
}
