//------------------------------------------------------------------------------
//
// File Name:	Level2.h
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

namespace Beta
{
	class Mesh;
	class Texture;
};

namespace FMOD
{
	class Channel;
}

class GameObject;
class SpriteSource;
class SoundManager;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Level1 : public Level
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 1.
	Level1();

	// Load the resources associated with Level 1.
	void Load() override;

	// Initialize the memory associated with Level 1.
	void Initialize() override;

	// Update the Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	// Destroy objects associated with the Asteroids level.
	void Shutdown() override;

	// Unload the resources associated with Level 1.
	void Unload() override;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Audio
	SoundManager* soundManager;
	FMOD::Channel* musicChannel;

	// Meshes
	Beta::Mesh* meshShip;
	Beta::Mesh* meshBullet;
	Beta::Mesh* meshBomb;

	// Textures
	Beta::Texture* textureShip;
	Beta::Texture* textureBullet;
	Beta::Texture* textureBomb;

	// SpriteSources
	SpriteSource* spriteSourceShip;
	SpriteSource* spriteSourceBullet;
	SpriteSource* spriteSourceBomb;
};

//----------------------------------------------------------------------------
