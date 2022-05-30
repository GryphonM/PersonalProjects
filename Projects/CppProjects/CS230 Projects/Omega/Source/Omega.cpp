//------------------------------------------------------------------------------
//
// File Name:	Omega.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 8.2.4 Assignment: Omega
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Omega.h"

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
#include "AsteroidsLevel.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Creates an instance of the Asteroids level.
Omega::Omega() : asteroidSpawnInitial(8), asteroidSpawnMaximum(20),
asteroidSpawnCount(0), asteroidWaveCount(0), playerShip(nullptr), asteroidHighScore(0),
mesh(nullptr), textureShip(nullptr), bulletArchetype(nullptr), textureBullet(nullptr),
asteroidArchetype(nullptr), textureAsteroid(nullptr), missileArchetype(nullptr),
textureMissile(nullptr), bombArchetype(nullptr), textureBomb(nullptr), spriteAsteroid(nullptr),
spriteBullet(nullptr), spriteShip(nullptr), Level("AsteroidsLevel")
{
}

// Load the resources associated with the Asteroids level.
void Omega::Load()
{
	mesh = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));

	textureShip = Texture::CreateTextureFromFile("ship.png");
	spriteShip = new SpriteSource(textureShip, "Ship");

	textureBullet = Texture::CreateTextureFromFile("bullet.png");
	spriteBullet = new SpriteSource(textureBullet, "Bullet");

	textureAsteroid = Texture::CreateTextureFromFile("asteroid.png");
	spriteAsteroid = new SpriteSource(textureAsteroid, "Asteroid");

	textureMissile = Texture::CreateTextureFromFile("bullet.png");
	spriteMissile = new SpriteSource(textureMissile, "Missile");

	textureBomb = Texture::CreateTextureFromFile("Circle.png");
	spriteBomb = new SpriteSource(textureBomb, "Bomb");

	asteroidArchetype = EngineGetModule(GameObjectFactory)->CreateObject("Asteroid", mesh, spriteAsteroid);
	bulletArchetype = EngineGetModule(GameObjectFactory)->CreateObject("Bullet", mesh, spriteBullet);
	missileArchetype = EngineGetModule(GameObjectFactory)->CreateObject("Missile", mesh, spriteMissile);
	bombArchetype = EngineGetModule(GameObjectFactory)->CreateObject("Bomb", mesh, spriteBomb);
	Beta::EngineCore::GetInstance().GetModule<Beta::GraphicsEngine>()->SetBackgroundColor();

	GetSpace()->GetObjectManager().AddArchetype(*bulletArchetype);
	GetSpace()->GetObjectManager().AddArchetype(*missileArchetype);
	GetSpace()->GetObjectManager().AddArchetype(*bombArchetype);
}

// Initialize the memory associated with the Asteroids level.
void Omega::Initialize()
{
	GameObject* ship = EngineGetModule(GameObjectFactory)->CreateObject("Ship", mesh, spriteShip);
	GetSpace()->GetObjectManager().AddObject(*ship);

	asteroidWaveCount = 0;
	asteroidSpawnCount = asteroidSpawnInitial;
	playerShip = GetSpace()->GetObjectManager().GetObjectByName("Ship")->GetComponent<PlayerShip>();
	playerShip->EnableMissile();
}

// Update the Asteroids level.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Omega::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (GetSpace()->GetObjectManager().GetObjectCount("Asteroid") <= 0)
		SpawnAsteroidWave();
	UpdateScore();
	SwitchLevels();
}

void Omega::Shutdown()
{
	if (playerShip->GetScore() > asteroidHighScore)
		asteroidHighScore = playerShip->GetScore();
	playerShip->StopSoundEvent();
}

// Unload/delete the resources associated with the Asteroids level.
void Omega::Unload()
{
	delete mesh;
	delete textureShip;
	delete textureBullet;
	delete textureMissile;
	delete textureBomb;
	delete textureAsteroid;
	delete spriteShip;
	delete spriteBullet;
	delete spriteMissile;
	delete spriteBomb;
	delete spriteAsteroid;
	delete asteroidArchetype;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Create a single asteroid object from the archetype
void Omega::SpawnAsteroid(void)
{
	GameObject* ast = new GameObject(*asteroidArchetype);
	GetSpace()->GetObjectManager().AddObject(*ast);
}

// Create a group of asteroids
void Omega::SpawnAsteroidWave(void)
{
	asteroidWaveCount++;
	for (unsigned i = 0; i < asteroidSpawnCount; i++)
		SpawnAsteroid();

	if (asteroidSpawnCount < asteroidSpawnMaximum)
		asteroidSpawnCount++;
}

// Update the score string
void Omega::UpdateScore()
{
	std::string windowTitle = "Asteroids: Wave = " + std::to_string(asteroidWaveCount) +
		", Score = " + std::to_string(playerShip->GetScore()) + ", High Score = " + std::to_string(asteroidHighScore);
	EngineCore::GetInstance().GetModule<WindowSystem>()->SetWindowTitle(windowTitle);
}

// Switch levels when keys are pressed
void Omega::SwitchLevels()
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
		EngineCore::GetInstance().GetModule<Space>()->SetLevel<AsteroidsLevel>();
	}
	else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('5'))
	{
		GetSpace()->RestartLevel();
	}
}