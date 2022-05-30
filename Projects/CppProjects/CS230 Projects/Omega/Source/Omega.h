//------------------------------------------------------------------------------
//
// File Name:	Omega.h
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

#include <Level.h>

#include "PlayerShip.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

namespace Beta
{
	class Mesh;
	class Texture;
}

class SpriteSource;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Omega : public Level
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create an instance of the Omega game state.
	Omega();

	// Load archetypes, meshes
	void Load();

	// Initialize the memory associated with the Omega game state.
	void Initialize();

	// Update the Omega game state.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt);

	// Set high score
	void Shutdown();

	// Unload textures, sprite sources, meshes
	void Unload();

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
	const unsigned asteroidSpawnInitial = 8;
	const unsigned asteroidSpawnMaximum = 20;
	unsigned asteroidSpawnCount;
	unsigned asteroidWaveCount;

	// Player
	PlayerShip* playerShip;
	unsigned asteroidHighScore;

	// Resources
	Beta::Mesh* mesh;
	Beta::Texture* textureShip;
	Beta::Texture* textureBullet;
	Beta::Texture* textureMissile;
	Beta::Texture* textureBomb;
	Beta::Texture* textureAsteroid;
	SpriteSource* spriteShip;
	SpriteSource* spriteMissile;
	SpriteSource* spriteBomb;
	SpriteSource* spriteBullet;
	SpriteSource* spriteAsteroid;

	// Archetypes
	GameObject* bulletArchetype;
	GameObject* bombArchetype;
	GameObject* missileArchetype;
	GameObject* asteroidArchetype;
};

//----------------------------------------------------------------------------
