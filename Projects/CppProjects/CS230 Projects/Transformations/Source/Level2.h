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

#include "Level.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

namespace Beta
{
	class Mesh;
	class Texture;
}

class SpriteSource;
class Sprite;
class Animation;
class Animator;
class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class Level2 : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Level 2.
		Level2();

		// Load the resources associated with Level 2.
		void Load();

		// Initialize the memory associated with Level 2.
		void Initialize();

		// Update Level 1.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt);

		// Shutdown any memory associated with Level 2.
		void Shutdown();

		// Unload the resources associated with Level 2.
		void Unload();

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
		
		// Components
		Sprite* sprite;
		Transform* transform;
		RigidBody* rigidBody;
		
		// Animation variables
		Animator* animator;
		Animation* animation;
		unsigned animFrameStart;
		unsigned animFrameCount;
		float animFrameDuration;
	};
}

//----------------------------------------------------------------------------
