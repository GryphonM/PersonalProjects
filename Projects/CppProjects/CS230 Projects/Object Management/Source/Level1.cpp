//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
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
#include "Archetypes.h"
#include "GameObject.h"

// Levels
#include "Level2.h"

//------------------------------------------------------------------------------

using namespace Beta;

//namespace Levels
//{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 1.
	Level1::Level1()
		: Level("Level1"), meshShip(nullptr), meshBullet(nullptr), windowTitle("")
	{
	}

	// Load the resources associated with Level 1.
	void Level1::Load()
	{
		std::cout << "Level1::Load" << std::endl;

		meshShip = CreateTriangleMesh(Colors::Red, Colors::Green, Colors::Blue);
		meshBullet = CreateTriangleMesh(Colors::Violet, Colors::Violet, Colors::Violet);
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBulletArchetype(meshBullet));
	}

	// Initialize the memory associated with Level 1.
	void Level1::Initialize()
	{
		std::cout << "Level1::Initialize" << std::endl;

		GameObject* ship = Archetypes::CreateShip(meshShip);
		GetSpace()->GetObjectManager().AddObject(*ship);
	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level1::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		windowTitle = std::to_string(GetSpace()->GetObjectManager().GetObjectCount("Bullet"));
		EngineCore::GetInstance().GetModule<WindowSystem>()->SetWindowTitle(windowTitle);
		
		if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('1'))
			GetSpace()->RestartLevel();
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('2'))
		{
			Level2* level = new Level2;
			EngineCore::GetInstance().GetModule<Space>()->SetLevel(level);
		}
	}

	// Unload the resources associated with Level 1.
	void Level1::Unload()
	{
		std::cout << "Level1::Unload" << std::endl;

		delete meshShip;
		delete meshBullet;
	}
//}
