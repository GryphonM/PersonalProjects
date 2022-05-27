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
#include "SoundManager.h"
#include "GameObjectFactory.h"

// Components
#include "GameObject.h"
#include "SpriteSource.h"
#include "PlayerShip.h"

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
		textureShip(nullptr), textureBullet(nullptr), textureBomb(nullptr), soundManager(nullptr),
		spriteSourceShip(nullptr), spriteSourceBullet(nullptr), spriteSourceBomb(nullptr), musicChannel(nullptr)
	{
	}

	// Load the resources associated with Level 1.
	void Level1::Load()
	{
		std::cout << "Level1::Load" << std::endl;

		soundManager = EngineCore::GetInstance().GetModule<SoundManager>();
		soundManager->AddMusic("Asteroid_Field.mp3");
		soundManager->AddEffect("teleport.wav");
		soundManager->AddBank("Master Bank.strings.bank");
		soundManager->AddBank("Master Bank.bank");

		meshShip = CreateTriangleMesh(Colors::Red, Colors::Green, Colors::Blue);
		meshBullet = CreateTriangleMesh(Colors::Violet, Colors::Violet, Colors::Violet);
		meshBomb = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));

		textureShip = Texture::CreateTextureFromFile("ship.png");
		textureBullet = Texture::CreateTextureFromFile("bullet.png");
		textureBomb = Texture::CreateTextureFromFile("Circle.png");

		spriteSourceShip = new SpriteSource(textureShip, "Ship");
		spriteSourceBullet = new SpriteSource(textureBullet, "Bullet");
		spriteSourceBomb = new SpriteSource(textureBomb, "Bomb");
		GetSpace()->GetObjectManager().AddArchetype(*EngineGetModule(GameObjectFactory)->CreateObject("Bullet", meshBullet, spriteSourceBullet));
		GetSpace()->GetObjectManager().AddArchetype(*EngineGetModule(GameObjectFactory)->CreateObject("Bomb", meshBomb, spriteSourceBomb));
	}

	// Initialize the memory associated with Level 1.
	void Level1::Initialize()
	{
		std::cout << "Level1::Initialize" << std::endl;

		musicChannel = soundManager->PlaySound("Asteroid Field");

		GameObject* ship = EngineGetModule(GameObjectFactory)->CreateObject("Ship", meshShip);
		GetSpace()->GetObjectManager().AddObject(*ship);
	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level1::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('T'))
			soundManager->PlaySound("teleport.wav");
		
		if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('1'))
			GetSpace()->RestartLevel();
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('2'))
		{
			EngineCore::GetInstance().GetModule<Space>()->SetLevel<Level2>();
		}
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('3'))
		{
			EngineCore::GetInstance().GetModule<Space>()->SetLevel<Level3>();
		}
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('4'))
		{
			EngineCore::GetInstance().GetModule<Space>()->SetLevel<AsteroidsLevel>();
		}
	}

	// Destroy objects associated with the Asteroids level.
	void Level1::Shutdown()
	{
		musicChannel->stop();
		GetSpace()->GetObjectManager().GetObjectByName("Ship")->GetComponent<PlayerShip>()->StopSoundEvent();
	}

	// Unload the resources associated with Level 1.
	void Level1::Unload()
	{
		std::cout << "Level1::Unload" << std::endl;

		soundManager->Shutdown();

		delete meshShip;
		delete meshBullet;
	}
//}
