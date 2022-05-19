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
#include "Tilemap.h"

// Components
#include "Sprite.h"
#include "Archetypes.h"
#include "Animator.h"
#include "GameObject.h"

// Levels
#include "Level1.h"
#include "Level3.h"
#include "AsteroidsLevel.h"

//------------------------------------------------------------------------------

using namespace Beta;

//namespace Levels
//{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2::Level2()
		: Level("Level2"), meshMonkey(nullptr), textureMonkey(nullptr),spriteSourceMonkey(nullptr), 
		columnsMonkey(3), rowsMonkey(5), dataMap(nullptr), textureMap(nullptr), spriteSourceMap(nullptr),
		meshMap(nullptr), columnsMap(4), rowsMap(3)
	{
	}

	// Load the resources associated with Level 2.
	void Level2::Load()
	{
		std::cout << "Level2::Load" << std::endl;
		
		// TO DO:
		// Create a texture from the Monkey.png file using Texture::CreateTextureFromFile
		textureMonkey = Texture::CreateTextureFromFile("Monkey.png");

		// Create a new sprite sources for monkey
		spriteSourceMonkey = new SpriteSource(textureMonkey, "Monkey", 3, 5);

		// Create a tilemap from a file
		dataMap = Tilemap::CreateTilemapFromFile("Level2.txt");
		if (dataMap == nullptr)
			std::cout << "Error loading map!" << std::endl;

		// Create visuals for tilemap
		meshMap = CreateQuadMesh(Vector2D(1.f / columnsMap, 1.f / rowsMap), Vector2D(0.5f, 0.5f));
		textureMap = Texture::CreateTextureFromFile("Tilemap.png");
		spriteSourceMap = new SpriteSource(textureMap, "Tilemap", columnsMap, rowsMap);

		// Create a textured mesh with 2 triangles using CreateQuadMesh
		meshMonkey = CreateQuadMesh(Vector2D(1.f / columnsMonkey, 1.f / rowsMonkey), Vector2D(0.5f, 0.5f));
	}

	// Initialize the memory associated with Level 2.
	void Level2::Initialize()
	{
		std::cout << "Level2::Initialize" << std::endl;
		
		// TO DO:
		GameObject* monkey = Archetypes::CreateMonkey(meshMonkey, spriteSourceMonkey);
		GameObject* tilemap = Archetypes::CreateTilemapObject(meshMap, spriteSourceMap, dataMap);
		GetSpace()->GetObjectManager().AddObject(*monkey);
		GetSpace()->GetObjectManager().AddObject(*tilemap);
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
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('4'))
		{
			AsteroidsLevel* level = new AsteroidsLevel;
			EngineCore::GetInstance().GetModule<Space>()->SetLevel(level);
		}
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('2'))
			GetSpace()->RestartLevel();
	}

	// Unload the resources associated with Level 2.
	void Level2::Unload()
	{
		std::cout << "Level2::Unload" << std::endl;
		
		// Delete the sprite source, texture, mesh
		delete spriteSourceMonkey;
		delete spriteSourceMap;
		delete meshMonkey;
		delete meshMap;
		delete textureMonkey;
		delete textureMap;
		delete dataMap;
	}
//}
