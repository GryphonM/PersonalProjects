//------------------------------------------------------------------------------
//
// File Name:	Archetypes.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.1.3 Assignment: Object Management
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObject.h"
#include "Space.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Animator.h"
#include "Animation.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Component.h"

//------------------------------------------------------------------------------

using namespace Beta;

namespace Archetypes
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
		
	// Create the ship game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateShip(Beta::Mesh* mesh)
	{
		GameObject* ship = new GameObject("Ship");
		Transform* t = new Transform(Vector2D(0, 0), Vector2D(0.5f, 0.5f));
		Sprite* s = new Sprite(mesh);
		RigidBody* rB = new RigidBody();
		ship->AddComponent(t);
		ship->AddComponent(s);
		ship->AddComponent(rB);
		return ship;
	}

	// Create the archetype for the bullet object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateBulletArchetype(Beta::Mesh* mesh)
	{
		GameObject* bullet = new GameObject("Bullet");
		Transform* t = new Transform(Vector2D(0, 0), Vector2D(0.07f, 0.07f));
		Sprite* s = new Sprite(mesh);
		RigidBody* rB = new RigidBody();
		bullet->AddComponent(t);
		bullet->AddComponent(s);
		bullet->AddComponent(rB);
		return bullet;
	}

	// Create the monkey game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	//   animatino = The walk animation.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateMonkey(Beta::Mesh* mesh, SpriteSource* spriteSource, Animation* animation)
	{
		GameObject* monkey = new GameObject("Monkey");
		Transform* t = new Transform();
		Sprite* s = new Sprite(mesh, spriteSource);
		Animator* a = new Animator();
		a->AddAnimation(animation);
		RigidBody* rB = new RigidBody();
		monkey->AddComponent(t);
		monkey->AddComponent(s);
		monkey->AddComponent(a);
		monkey->AddComponent(rB);
		return monkey;
	}
}
