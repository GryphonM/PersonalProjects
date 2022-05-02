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
#include "Archetypes.h"
#include "GameObject.h"
#include "SpriteSource.h"

// Levels
#include "Level2.h"
#include "Level3.h"
#include "AsteroidsLevel.h"

//------------------------------------------------------------------------------

using namespace Beta;

//namespace Levels
//{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 1.
	Level1::Level1() : Level("Level1"), meshShip(nullptr), meshBullet(nullptr), meshBomb(nullptr),
		textureShip(nullptr), textureBullet(nullptr), textureBomb(nullptr),
		spriteSourceShip(nullptr), spriteSourceBullet(nullptr), spriteSourceBomb(nullptr)
	{
	}

	// Load the resources associated with Level 1.
	void Level1::Load()
	{
		std::cout << "Level1::Load" << std::endl;

		meshShip = CreateTriangleMesh(Colors::Red, Colors::Green, Colors::Blue);
		meshBullet = CreateTriangleMesh(Colors::Violet, Colors::Violet, Colors::Violet);
		meshBomb = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));

		textureShip = Texture::CreateTextureFromFile("ship.png");
		textureBullet = Texture::CreateTextureFromFile("bullet.png");
		textureBomb = Texture::CreateTextureFromFile("Circle.png");

		spriteSourceShip = new SpriteSource(textureShip, "Ship");
		spriteSourceBullet = new SpriteSource(textureBullet, "Bullet");
		spriteSourceBomb = new SpriteSource(textureBomb, "Bomb");
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBulletArchetype(meshBullet, spriteSourceBullet));
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBombArchetype(meshBomb, spriteSourceBomb));
	}

	// Initialize the memory associated with Level 1.
	void Level1::Initialize()
	{
		std::cout << "Level1::Initialize" << std::endl;

		GameObject* ship = Archetypes::CreateShip(meshShip, nullptr);
		GetSpace()->GetObjectManager().AddObject(*ship);
	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level1::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		
		if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('1'))
			GetSpace()->RestartLevel();
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('2'))
		{
			Level2* level = new Level2;
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
	}

	// Unload the resources associated with Level 1.
	void Level1::Unload()
	{
		std::cout << "Level1::Unload" << std::endl;

		delete meshShip;
		delete meshBullet;
	}
//}
