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
#include "Space.h"
#include "Archetypes.h"
#include "PlayerShip.h"
#include "GameObject.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "MeshHelper.h"

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
	meshMissile(nullptr), textureMissile(nullptr), spriteSourceMissile(nullptr), Level("AsteroidsLevel")
{
}

// Load the resources associated with the Asteroids level.
void AsteroidsLevel::Load()
{
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

	asteroidArchetype = Archetypes::CreateAsteroidArchetype(meshAsteroid, spriteSourceAsteroid);
	bulletArchetype = Archetypes::CreateBulletArchetype(meshBullet, spriteSourceBullet);
	missileArchetype = Archetypes::CreateMissileArchetype(meshMissile, spriteSourceMissile);
	Beta::EngineCore::GetInstance().GetModule<Beta::GraphicsEngine>()->SetBackgroundColor();

	GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBulletArchetype(meshBullet, spriteSourceBullet));
	GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateMissileArchetype(meshMissile, spriteSourceMissile));
}

// Initialize the memory associated with the Asteroids level.
void AsteroidsLevel::Initialize()
{
	GameObject* ship = Archetypes::CreateShip(meshShip, spriteSourceShip);	
	GetSpace()->GetObjectManager().AddObject(*ship);

	asteroidWaveCount = 0;
	asteroidSpawnCount = asteroidSpawnInitial;
	playerShip = dynamic_cast<PlayerShip*>(GetSpace()->GetObjectManager().GetObjectByName("Ship")->GetComponent("PlayerShip"));
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
	if (playerShip->GetScore() > asteroidHighScore)
		asteroidHighScore = playerShip->GetScore();
}

// Unload/delete the resources associated with the Asteroids level.
void AsteroidsLevel::Unload()
{
	delete meshShip;
	delete textureShip;
	delete spriteSourceShip;
	delete bulletArchetype;
	delete meshBullet;
	delete textureBullet;
	delete spriteSourceBullet;
	delete asteroidArchetype;
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
		Level1* level = new Level1;
		EngineCore::GetInstance().GetModule<Space>()->SetLevel(level);
	}
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
		GetSpace()->RestartLevel();
	}
}