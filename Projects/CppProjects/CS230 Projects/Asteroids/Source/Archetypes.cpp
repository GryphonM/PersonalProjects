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
#include "TimedDeath.h"
#include "PlayerShip.h"
#include "MonkeyMovement.h"
#include "ColorChange.h"
#include "ScreenWrap.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include "ColliderPoint.h"
#include "ColliderRectangle.h"
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
		PlayerShip* pS = new PlayerShip();
		ScreenWrap* sW = new ScreenWrap();
		ship->AddComponent(t);
		ship->AddComponent(s);
		ship->AddComponent(rB);
		ship->AddComponent(pS);
		ship->AddComponent(sW);
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
		TimedDeath* tD = new TimedDeath();
		bullet->AddComponent(t);
		bullet->AddComponent(s);
		bullet->AddComponent(rB);
		bullet->AddComponent(tD);
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
		MonkeyMovement* mM = new MonkeyMovement();
		monkey->AddComponent(t);
		monkey->AddComponent(s);
		monkey->AddComponent(a);
		monkey->AddComponent(rB);
		monkey->AddComponent(mM);
		return monkey;
	}

	// Create the circle game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateCircle(Beta::Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* circle = new GameObject("Circle");
		Transform* t = new Transform();
		Sprite* s = new Sprite(mesh, spriteSource);
		RigidBody* rB = new RigidBody();
		ColliderCircle* colC = new ColliderCircle(t->GetScale().x * 0.5f);
		ColorChange* cC = new ColorChange(Colors::Yellow, Colors::Red);
		ScreenWrap* sW = new ScreenWrap();
		circle->AddComponent(t);
		circle->AddComponent(s);
		circle->AddComponent(rB);
		circle->AddComponent(colC);
		circle->AddComponent(cC);
		circle->AddComponent(sW);
		return circle;
	}

	// Create the point game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreatePoint(Beta::Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* point = new GameObject("Point");
		Transform* t = new Transform(Vector2D(), Vector2D(0.2f, 0.2f));
		Sprite* s = new Sprite(mesh, spriteSource);
		RigidBody* rB = new RigidBody();
		ColliderPoint* cP = new ColliderPoint();
		ColorChange* cC = new ColorChange(Colors::Blue, Colors::Red);
		ScreenWrap* sW = new ScreenWrap();
		point->AddComponent(t);
		point->AddComponent(s);
		point->AddComponent(rB);
		point->AddComponent(cP);
		point->AddComponent(cC);
		point->AddComponent(sW);
		return point;
	}

	// Create the rectangle game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateRectangle(Beta::Mesh* mesh)
	{
		GameObject* rectangle = new GameObject("rectangle");
		Transform* t = new Transform(Vector2D(), Vector2D(2.5, 1));
		Sprite* s = new Sprite(mesh);
		RigidBody* rB = new RigidBody();
		ColliderRectangle* cR = new ColliderRectangle(Vector2D(0.5f * t->GetScale().x, 0.5f *  t->GetScale().y));
		ColorChange* cC = new ColorChange(Colors::Green, Colors::Red);
		ScreenWrap* sW = new ScreenWrap();
		rectangle->AddComponent(t);
		rectangle->AddComponent(s);
		rectangle->AddComponent(rB);
		rectangle->AddComponent(cR);
		rectangle->AddComponent(cC);
		rectangle->AddComponent(sW);
		return rectangle;
	}
}
