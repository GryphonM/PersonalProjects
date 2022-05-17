//------------------------------------------------------------------------------
//
// File Name:	Asteroids.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Vector2D.h"
#include "Level.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class PlayerShip;
class GameObject;
class SpriteSource;

namespace Beta
{
	class Mesh;
	class Texture;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------


class AsteroidsLevel : public Level
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of the Asteroids level.
	AsteroidsLevel();

	// Load the resources associated with the Asteroids level.
	void Load() override;

	// Initialize the memory associated with the Asteroids level.
	void Initialize() override;

	// Update the Asteroids level.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	// Destroy objects associated with the Asteroids level.
	void Shutdown() override;

	// Unload/delete the resources associated with the Asteroids level.
	void Unload() override;

private:

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Create a single asteroid object from the archetype
	void SpawnAsteroid(void);

	// Create a group of asteroids
	void SpawnAsteroidWave(void);

	// Update the score string
	void UpdateScore();

	// Switch levels when keys are pressed
	void SwitchLevels();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Spawning
	const unsigned asteroidSpawnInitial;
	const unsigned asteroidSpawnMaximum;
	unsigned asteroidSpawnCount;
	unsigned asteroidWaveCount;

	// Player
	PlayerShip* playerShip;
	unsigned asteroidHighScore;
	Beta::Mesh* meshShip;
	Beta::Texture* textureShip;
	SpriteSource* spriteSourceShip;

	// Bullet
	GameObject* bulletArchetype;
	Beta::Mesh* meshBullet;
	Beta::Texture* textureBullet;
	SpriteSource* spriteSourceBullet;

	// Missile
	GameObject* missileArchetype;
	Beta::Mesh* meshMissile;
	Beta::Texture* textureMissile;
	SpriteSource* spriteSourceMissile;

	// Bomb
	GameObject* bombArchetype;
	Beta::Mesh* meshBomb;
	Beta::Texture* textureBomb;
	SpriteSource* spriteSourceBomb;

	// Asteroid
	GameObject* asteroidArchetype;
	Beta::Mesh* meshAsteroid;
	Beta::Texture* textureAsteroid;
	SpriteSource* spriteSourceAsteroid;
};


//----------------------------------------------------------------------------
