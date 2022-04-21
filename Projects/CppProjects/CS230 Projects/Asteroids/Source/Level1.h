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

class GameObject;
class SpriteSource;

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

	// Unload the resources associated with Level 1.
	void Unload() override;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Meshes
	Beta::Mesh* meshShip;
	Beta::Mesh* meshBullet;

	// Textures
	Beta::Texture* textureShip;
	Beta::Texture* textureBullet;

	// SpriteSources
	SpriteSource* spriteSourceShip;
	SpriteSource* spriteSourceBullet;
};

//----------------------------------------------------------------------------
