//------------------------------------------------------------------------------
//
// File Name:	AsteroidsLevel.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.1.7 Assignment: Asteroids
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AsteroidsLevel.h"

// Systems
#include "Space.h"
#include "MeshHelper.h"
#include "SoundManager.h"
#include "GameObjectFactory.h"

// Components
#include "PlayerShip.h"
#include "GameObject.h"
#include "SpriteSource.h"
#include "Sprite.h"

// Levels
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Creates an instance of the Asteroids level.
AsteroidsLevel::AsteroidsLevel() : asteroidSpawnInitial(8), asteroidSpawnMaximum(20),
	asteroidSpawnCount(0), asteroidWaveCount(0), playerShip(nullptr), asteroidHighScore(0),
	meshShip(nullptr), textureShip(nullptr), spriteSourceShip(nullptr), bulletArchetype(nullptr),
	meshBullet(nullptr), textureBullet(nullptr), spriteSourceBullet(nullptr), asteroidArchetype(nullptr),
	meshAsteroid(nullptr), textureAsteroid(nullptr), spriteSourceAsteroid(nullptr), missileArchetype(nullptr),
	meshMissile(nullptr), textureMissile(nullptr), spriteSourceMissile(nullptr), bombArchetype(nullptr),
	meshBomb(nullptr), textureBomb(nullptr), spriteSourceBomb(nullptr), soundManager(nullptr), musicChannel(nullptr),
	Level("AsteroidsLevel")
{
}

// Load the resources associated with the Asteroids level.
void AsteroidsLevel::Load()
{
	soundManager = EngineGetModule(SoundManager);
	soundManager->AddMusic("Asteroid_Field.mp3");
	soundManager->AddEffect("teleport.wav");
	soundManager->AddBank("Master Bank.strings.bank");
	soundManager->AddBank("Master Bank.bank");
	
	meshShip = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
	textureShip = Texture::CreateTextureFromFile("ship.png");
	spriteSourceShip = new SpriteSource(textureShip, "Ship");

	meshBullet = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
	textureBullet = Texture::CreateTextureFromFile("bullet.png");
	spriteSourceBullet = new SpriteSource(textureBullet, "Bullet");

	meshAsteroid = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
	textureAsteroid = Texture::CreateTextureFromFile("asteroid.png");
	spriteSourceAsteroid = new SpriteSource(textureAsteroid, "Asteroid");

	meshMissile = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
	textureMissile = Texture::CreateTextureFromFile("bullet.png");
	spriteSourceMissile = new SpriteSource(textureMissile, "Missile");

	meshBomb = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
	textureBomb = Texture::CreateTextureFromFile("Circle.png");
	spriteSourceBomb = new SpriteSource(textureBomb, "Bomb");

	asteroidArchetype = EngineGetModule(GameObjectFactory)->CreateObject("Asteroid", meshAsteroid, spriteSourceAsteroid);
	bulletArchetype = EngineGetModule(GameObjectFactory)->CreateObject("Bullet", meshBullet, spriteSourceBullet);
	missileArchetype = EngineGetModule(GameObjectFactory)->CreateObject("Missile", meshMissile, spriteSourceMissile);
	bombArchetype = EngineGetModule(GameObjectFactory)->CreateObject("Bomb", meshBomb, spriteSourceBomb);
	Beta::EngineCore::GetInstance().GetModule<Beta::GraphicsEngine>()->SetBackgroundColor();

	GetSpace()->GetObjectManager().AddArchetype(*bulletArchetype);
	GetSpace()->GetObjectManager().AddArchetype(*missileArchetype);
	GetSpace()->GetObjectManager().AddArchetype(*bombArchetype);
}

// Initialize the memory associated with the Asteroids level.
void AsteroidsLevel::Initialize()
{
	GameObject* ship = EngineGetModule(GameObjectFactory)->CreateObject("Ship", meshShip, spriteSourceShip);
	GetSpace()->GetObjectManager().AddObject(*ship);

	musicChannel = soundManager->PlaySound("Asteroid Field");

	asteroidWaveCount = 0;
	asteroidSpawnCount = asteroidSpawnInitial;
	playerShip = GetSpace()->GetObjectManager().GetObjectByName("Ship")->GetComponent<PlayerShip>();
	playerShip->EnableMissile();
}

// Update the Asteroids level.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void AsteroidsLevel::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (GetSpace()->GetObjectManager().GetObjectCount("Asteroid") <= 0)
		SpawnAsteroidWave();
	UpdateScore();
	SwitchLevels();
}

void AsteroidsLevel::Shutdown()
{
	musicChannel->stop();
	if (playerShip->GetScore() > asteroidHighScore)
		asteroidHighScore = playerShip->GetScore();
	playerShip->StopSoundEvent();
}

// Unload/delete the resources associated with the Asteroids level.
void AsteroidsLevel::Unload()
{
	soundManager->Shutdown();

	delete meshShip;
	delete textureShip;
	delete spriteSourceShip;
	delete meshBullet;
	delete textureBullet;
	delete spriteSourceBullet;
	delete meshAsteroid;
	delete textureAsteroid;
	delete spriteSourceAsteroid;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Create a single asteroid object from the archetype
void AsteroidsLevel::SpawnAsteroid(void)
{
	GameObject* ast = new GameObject(*asteroidArchetype);
	GetSpace()->GetObjectManager().AddObject(*ast);
}

// Create a group of asteroids
void AsteroidsLevel::SpawnAsteroidWave(void)
{
	asteroidWaveCount++;
	for (unsigned i = 0; i < asteroidSpawnCount; i++)
		SpawnAsteroid();

	if (asteroidSpawnCount < asteroidSpawnMaximum)
		asteroidSpawnCount++;
}

// Update the score string
void AsteroidsLevel::UpdateScore()
{
	std::string windowTitle = "Asteroids: Wave = " + std::to_string(asteroidWaveCount) +
		", Score = " + std::to_string(playerShip->GetScore()) + ", High Score = " + std::to_string(asteroidHighScore);
	EngineCore::GetInstance().GetModule<WindowSystem>()->SetWindowTitle(windowTitle);
}

// Switch levels when keys are pressed
void AsteroidsLevel::SwitchLevels()
{
	if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('1'))
	{
		EngineCore::GetInstance().GetModule<Space>()->SetLevel<Level1>();
	}
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
		GetSpace()->RestartLevel();
	}
}