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
#include "Archetypes.h"
#include "Animator.h"
#include "GameObject.h"

// Levels
#include "Level1.h"
#include "Level3.h"

//------------------------------------------------------------------------------

using namespace Beta;

//namespace Levels
//{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2::Level2()
		: Level("Level2"), mesh(nullptr), texture(nullptr),spriteSource(nullptr), 
		columns(3), rows(5), animation(nullptr), animFrameStart(0), animFrameCount(8), animFrameDuration(0.2f)
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
		spriteSource = new SpriteSource(texture, "Monkey", 3, 5);

		// Create a new animation for the monkey walk cycle
		animation = new Animation("Monkey Walk", nullptr, animFrameCount, animFrameStart, animFrameDuration);

		// Create a textured mesh with 2 triangles using CreateQuadMesh
		mesh = CreateQuadMesh(Vector2D(1.f / columns, 1.f / rows), Vector2D(0.5f, 0.5f));
	}

	// Initialize the memory associated with Level 2.
	void Level2::Initialize()
	{
		std::cout << "Level2::Initialize" << std::endl;
		
		// TO DO:
		GameObject* monkey = Archetypes::CreateMonkey(mesh, spriteSource, animation);
		GetSpace()->GetObjectManager().AddObject(*monkey);
	}

	// Update Level 2.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level2::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('1'))
		{
			Level1* level = new Level1;
			EngineCore::GetInstance().GetModule<Space>()->SetLevel(level);
		}
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('3'))
		{
			Level3* level = new Level3;
			EngineCore::GetInstance().GetModule<Space>()->SetLevel(level);
		}
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('2'))
			GetSpace()->RestartLevel();
	}

	// Unload the resources associated with Level 2.
	void Level2::Unload()
	{
		std::cout << "Level2::Unload" << std::endl;
		
		// TO DO: Delete the animation, sprite source, texture, mesh
		delete animation;
		delete spriteSource;
		delete mesh;
		delete texture;
	}
//}
