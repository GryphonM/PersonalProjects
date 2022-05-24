//------------------------------------------------------------------------------
//
// File Name:	Level3.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.1.6 Assignment: Collision Detection
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Level3.h"

// Systems
#include "Space.h"
#include "MeshHelper.h"
#include "GameObjectFactory.h"

// Components
#include "GameObject.h"
#include "SpriteSource.h"
#include "Animation.h"
#include "Transform.h"
#include "RigidBody.h"

// Levels
#include "Level2.h"
#include "Level1.h"
#include "AsteroidsLevel.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Creates an instance of Level 3.
Level3::Level3() : meshQuad(nullptr), spriteSourceCircle(nullptr), textureCircle(nullptr),
	circleSpeed(100.0f), pointSpeed(100.0f), Level("Level3")
{
}

// Load the resources associated with Level 3.
void Level3::Load()
{
	meshQuad = CreateQuadMesh(Vector2D(1, 1), Vector2D(0.5, 0.5));
	textureCircle = Texture::CreateTextureFromFile("Circle.png");
	spriteSourceCircle = new SpriteSource(textureCircle, "Circle");
}

// Initialize the memory associated with Level 3.
void Level3::Initialize()
{
	GameObject* staticCircle = EngineGetModule(GameObjectFactory)->CreateObject("Circle", meshQuad, spriteSourceCircle);
	dynamic_cast<Transform*>(staticCircle->GetComponent("Transform"))->SetTranslation(Vector2D(2.0f, 2.0f));

	GameObject* staticRect = EngineGetModule(GameObjectFactory)->CreateObject("Rectangle", meshQuad);
	dynamic_cast<Transform*>(staticRect->GetComponent("Transform"))->SetTranslation(Vector2D(1.0f, -1.5f));

	GameObject* point = EngineGetModule(GameObjectFactory)->CreateObject("Point", meshQuad, spriteSourceCircle);
	dynamic_cast<Transform*>(point->GetComponent("Transform"))->SetTranslation(Vector2D(1.0f, 2.0f));
	dynamic_cast<RigidBody*>(point->GetComponent("RigidBody"))->AddForce(Vector2D(0, -pointSpeed));

	GameObject* moveCircle = EngineGetModule(GameObjectFactory)->CreateObject("Circle", meshQuad, spriteSourceCircle);
	dynamic_cast<Transform*>(moveCircle->GetComponent("Transform"))->SetTranslation(Vector2D(-1.5f, 0.5f));
	dynamic_cast<RigidBody*>(moveCircle->GetComponent("RigidBody"))->AddForce(Vector2D(0, circleSpeed).Rotate(-120.f));

	GameObject* moveRect = EngineGetModule(GameObjectFactory)->CreateObject("Rectangle", meshQuad);
	dynamic_cast<Transform*>(moveRect->GetComponent("Transform"))->SetTranslation(Vector2D(-2.0f, 2.0f));
	dynamic_cast<RigidBody*>(moveRect->GetComponent("RigidBody"))->AddForce(Vector2D(0, circleSpeed).Rotate(45.f));

	GetSpace()->GetObjectManager().AddObject(*staticCircle);
	GetSpace()->GetObjectManager().AddObject(*staticRect);
	GetSpace()->GetObjectManager().AddObject(*point);
	GetSpace()->GetObjectManager().AddObject(*moveCircle);
	GetSpace()->GetObjectManager().AddObject(*moveRect);
}

// Update Level 3.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Level3::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

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
		GetSpace()->RestartLevel();
	else if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered('4'))
	{
		AsteroidsLevel* level = new AsteroidsLevel;
		EngineCore::GetInstance().GetModule<Space>()->SetLevel(level);
	}
}

// Unload the resources associated with Level 3.
void Level3::Unload()
{
	delete meshQuad;
	delete textureCircle;
	delete spriteSourceCircle;
}