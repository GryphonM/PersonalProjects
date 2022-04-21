//------------------------------------------------------------------------------
//
// File Name:	Asteroid.cpp
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

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Creates an instance of the Asteroids level.
AsteroidsLevel::AsteroidsLevel() : asteroidSpawnInitial(8), asteroidSpawnMaximum(20),
	asteroidSpawnCount(0), asteroidWaveCount(0), playerShip(nullptr), asteroidHighScore(0),
	meshShip(nullptr), textureShip(nullptr), spriteSourceShip(nullptr), bulletArchetype(nullptr),
	meshBullet(nullptr), textureBullet(nullptr), spriteSourceBullet(nullptr), asteroidArchetype(nullptr),
	meshAsteroid(nullptr), textureAsteroid(nullptr), spriteSourceAsteroid(nullptr), Level("AsteroidsLevel")
{
}

// Load the resources associated with the Asteroids level.
void AsteroidsLevel::Load()
{
	asteroidArchetype = Archetypes::CreateAsteroidArchetype(meshAsteroid, spriteSourceAsteroid);
	bulletArchetype = Archetypes::CreateBulletArchetype(meshBullet, spriteSourceBullet);
	Beta::EngineCore::GetInstance().GetModule<Beta::GraphicsEngine>()->SetBackgroundColor();
}

// Initialize the memory associated with the Asteroids level.
void AsteroidsLevel::Initialize()
{
	asteroidWaveCount = 0;
	asteroidSpawnCount = asteroidSpawnInitial;
}

// Update the Asteroids level.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void AsteroidsLevel::Update(float dt)
{
	if (GetSpace()->GetObjectManager().GetObjectCount("Asteroid") <= 0)
		SpawnAsteroidWave();
}

// Unload/delete the resources associated with the Asteroids level.
void AsteroidsLevel::Unload()
{
	delete playerShip;
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
	for (int i = 0; i < asteroidSpawnCount; i++)
		SpawnAsteroid();

	if (asteroidSpawnCount < asteroidSpawnMaximum)
		asteroidSpawnCount++;
}