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
// Forward References:
//------------------------------------------------------------------------------

namespace Beta
{
	class Texture;
	class Mesh;
}

class SpriteSource;
class Animation;
class GameObject;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Level2 : public Level
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2();

	// Load the resources associated with Level 2.
	void Load() override;

	// Initialize the memory associated with Level 2.
	void Initialize() override;

	// Update Level 2.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	// Unload the resources associated with Level 2.
	void Unload() override;

private:

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Mesh and texture for sprite
	Beta::Mesh* mesh;
	Beta::Texture* texture;

	// Sprite source variables
	SpriteSource* spriteSource;
	unsigned columns;
	unsigned rows;

	// Animation variables
	Animation* animation;
	unsigned animFrameStart;
	unsigned animFrameCount;
	float animFrameDuration;

	GameObject *object;
};

//----------------------------------------------------------------------------
