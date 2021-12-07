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
#include "MeshHelper.h"

// Resources
#include "SpriteSource.h"
#include "Animation.h"

// Components
#include "Sprite.h"
#include "Animator.h"

//------------------------------------------------------------------------------

using namespace Beta;

namespace Levels
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2::Level2()
		: Level("Level2"), mesh(nullptr), texture(nullptr),spriteSource(nullptr), 
		columns(3), rows(5), sprite(nullptr), animator(nullptr), lives(2), 
		maxHealth(2), currentHealth(maxHealth), animation(nullptr), 
		animFrameStart(0), animFrameCount(8), animFrameDuration(0.0f)
	{
	}

	// Load the resources associated with Level 2.
	void Level2::Load()
	{
		std::cout << "Level2::Load" << std::endl;
		
		// TO DO:
		// Create a texture from the Monkey.png file using Texture::CreateTextureFromFile
		texture = Texture::CreateTextureFromFile("Monkey.png");

		// Create a new sprite sources for monkey
		spriteSource = new SpriteSource(texture);

		// Create a new animation for the monkey walk cycle

		// Create a textured mesh with 2 triangles using CreateQuadMesh
		mesh = CreateQuadMesh(Vector2D(1.f / columns, 1.f / rows), Vector2D(0.5f, 0.5f));
	}

	// Initialize the memory associated with Level 2.
	void Level2::Initialize()
	{
		std::cout << "Level2::Initialize" << std::endl;
		
		// TO DO:
		// Create a new sprite
		sprite = new Sprite(mesh, spriteSource);

		// Create a new animator

		// Add the animation to the animator

		// Reset health
	}

	// Update Level 2.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level2::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		
		// TO DO: Update the animation component
		
		// TO DO: Draw the sprite
		sprite->Draw();

		// If the animation is done
		/*if (animator->IsDone())
		{
			// Decrease health value by 1
			--currentHealth;

			// If health reaches 0, decrease lives value by 1
			if (currentHealth <= 0)
			{
				--lives;

				// If lives reaches 0, quit the game (stop the Engine)
				if (lives <= 0)
				{
					EngineCore::GetInstance().Stop();
				}
				// Otherwise, restart the level
				else
				{
					GetSpace()->RestartLevel();
				}
			}
		}*/
	}

	// Shutdown any memory associated with Level 2.
	void Level2::Shutdown()
	{
		std::cout << "Level2::Shutdown" << std::endl;
		
		// TO DO: Delete the animator and sprite
		delete sprite;
	}

	// Unload the resources associated with Level 2.
	void Level2::Unload()
	{
		std::cout << "Level2::Unload" << std::endl;
		
		// TO DO: Delete the animation, sprite source, texture, mesh
		delete spriteSource;
		delete mesh;
		delete texture;
	}
}
