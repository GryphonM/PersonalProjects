//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Level2.h"

// Systems
#include "Space.h"
#include "MeshHelper.h"

// Resources
#include "SpriteSource.h"
#include "Animation.h"

// Components
#include "Sprite.h"
#include "Animator.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Behaviors.h"

// Levels
#include "Level1.h"

//------------------------------------------------------------------------------

using namespace Beta;

namespace Levels
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2::Level2()
		: Level("Level2"), mesh(nullptr), texture(nullptr),spriteSource(nullptr), 
		columns(3), rows(5), sprite(nullptr), animator(nullptr), animation(nullptr), 
		animFrameStart(0), animFrameCount(8), animFrameDuration(0.2f)
	{
	}

	// Load the resources associated with Level 2.
	void Level2::Load()
	{
		std::cout << "Level2::Load" << std::endl;
		
		// TO DO:
		// Create a texture from the Monkey.png file using Texture::CreateTextureFromFile
		texture = Texture::CreateTextureFromFile("Monkey.png");

		// Create a new sprite sources for monkey
		spriteSource = new SpriteSource(texture, "Monkey", 3, 5);

		// Create a new animation for the monkey walk cycle
		animation = new Animation("Monkey Walk", nullptr, animFrameCount, animFrameStart, animFrameDuration);

		// Create a textured mesh with 2 triangles using CreateQuadMesh
		mesh = CreateQuadMesh(Vector2D(1.f / columns, 1.f / rows), Vector2D(0.5f, 0.5f));
	}

	// Initialize the memory associated with Level 2.
	void Level2::Initialize()
	{
		std::cout << "Level2::Initialize" << std::endl;
		
		// TO DO:
		// Create a Transform
		BoundingRectangle screen = EngineCore::GetInstance().GetModule<GraphicsEngine>()->GetDefaultCamera().GetScreenWorldDimensions();
		transform = new Transform(Beta::Vector2D(screen.center.x, screen.bottom + 0.5f), Beta::Vector2D(1, 1), 0);

		// Create a RigidBody
		rigidBody = new RigidBody(transform);

		// Create a new sprite
		sprite = new Sprite(transform, mesh, spriteSource);

		// Create a new animator
		animator = new Animator(sprite);

		// Add the animation to the animator
		animator->AddAnimation(animation);
		animator->Play();
	}

	// Update Level 2.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level2::Update(float dt)
	{
		// TO DO: Update the animation component
		animator->Update(dt);
		
		// TO DO: Draw the sprite
		sprite->Draw();

		// Update objects
		Behaviors::UpdateMonkey(transform, rigidBody);
		rigidBody->Update(dt);
		rigidBody->FixedUpdate(dt);

		if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('1'))
		{
			Level1* level = new Level1;
			EngineCore::GetInstance().GetModule<Space>()->SetLevel(level);
		}
		else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('2'))
			GetSpace()->RestartLevel();
	}

	// Shutdown any memory associated with Level 2.
	void Level2::Shutdown()
	{
		std::cout << "Level2::Shutdown" << std::endl;
		
		// TO DO: Delete components
		delete animator;
		delete sprite;
		delete transform;
		delete rigidBody;
	}

	// Unload the resources associated with Level 2.
	void Level2::Unload()
	{
		std::cout << "Level2::Unload" << std::endl;
		
		// TO DO: Delete the animation, sprite source, texture, mesh
		delete animation;
		delete spriteSource;
		delete mesh;
		delete texture;
	}
}
