//------------------------------------------------------------------------------
//
// File Name:	Archetypes.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.1.3 Assignment: Object Management
// Course:	WANIC VGP2
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
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
#include "PlayerProjectile.h"
#include "Component.h"
#include "Asteroid.h"
#include "HomingMissile.h"
#include "Bomb.h"
#include "Tilemap.h"
#include "SpriteTilemap.h"
#include "ColliderTilemap.h"

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
	GameObject* CreateShip(Beta::Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* ship = new GameObject("Ship");
		Transform* t = new Transform(Vector2D(0, 0), Vector2D(0.5f, 0.5f));
		Sprite* s = new Sprite(mesh, spriteSource);
		RigidBody* rB = new RigidBody();
		PlayerShip* pS = new PlayerShip();
		ScreenWrap* sW = new ScreenWrap();
		ColliderCircle* cC = new ColliderCircle(0.5f * t->GetScale().x);
		ship->AddComponent(t);
		ship->AddComponent(s);
		ship->AddComponent(rB);
		ship->AddComponent(pS);
		ship->AddComponent(sW);
		ship->AddComponent(cC);
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(ship);
		return ship;
	}

	// Create the archetype for the bullet object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateBulletArchetype(Beta::Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* bullet = new GameObject("Bullet");
		Transform* t = new Transform(Vector2D(0, 0), Vector2D(0.07f, 0.07f));
		Sprite* s = new Sprite(mesh, spriteSource);
		RigidBody* rB = new RigidBody();
		TimedDeath* tD = new TimedDeath();
		PlayerProjectile* pP = new PlayerProjectile();
		ColliderCircle* cC = new ColliderCircle(t->GetScale().x / 2.0f);
		bullet->AddComponent(t);
		bullet->AddComponent(s);
		bullet->AddComponent(rB);
		bullet->AddComponent(tD);
		bullet->AddComponent(pP);
		bullet->AddComponent(cC);
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(bullet);
		return bullet;
	}

	// Create the monkey game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	//   animatino = The walk animation.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateMonkey(Beta::Mesh* mesh, SpriteSource* spriteSource/*, Animation* animation*/)
	{
		GameObject* monkey = new GameObject("Monkey");
		Transform* t = new Transform(Vector2D(0, 1), Vector2D(1, 1));
		Sprite* s = new Sprite(mesh, spriteSource);
		RigidBody* rB = new RigidBody();
		ColliderRectangle* cR = new ColliderRectangle(Vector2D(0.5f * t->GetScale().x, 0.5f * t->GetScale().y));
		MonkeyMovement* mM = new MonkeyMovement();
		monkey->AddComponent(t);
		monkey->AddComponent(s);
		monkey->AddComponent(rB);
		monkey->AddComponent(cR);
		monkey->AddComponent(mM);
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(monkey);
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
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(circle);
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
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(point);
		return point;
	}

	// Create the rectangle game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateRectangle(Beta::Mesh* mesh)
	{
		GameObject* rectangle = new GameObject("Rectangle");
		Transform* t = new Transform(Vector2D(), Vector2D(2.5, 1));
		Sprite* s = new Sprite(mesh);
		RigidBody* rB = new RigidBody();
		ColliderRectangle* cR = new ColliderRectangle(Vector2D(0.5f * t->GetScale().x, 0.5f * t->GetScale().y));
		ColorChange* cC = new ColorChange(Colors::Green, Colors::Red);
		ScreenWrap* sW = new ScreenWrap();
		rectangle->AddComponent(t);
		rectangle->AddComponent(s);
		rectangle->AddComponent(rB);
		rectangle->AddComponent(cR);
		rectangle->AddComponent(cC);
		rectangle->AddComponent(sW);
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(rectangle);
		return rectangle;
	}

	// Create the asteroid game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateAsteroidArchetype(Beta::Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* asteroid = new GameObject("Asteroid");
		Transform* t = new Transform(Vector2D(0, 0), Vector2D(0.5f, 0.5f));
		Sprite* s = new Sprite(mesh, spriteSource);
		Asteroid* a = new Asteroid();
		RigidBody* rB = new RigidBody();
		ColliderCircle* cC = new ColliderCircle(t->GetScale().x * 0.5f);
		ScreenWrap* sW = new ScreenWrap();
		asteroid->AddComponent(t);
		asteroid->AddComponent(s);
		asteroid->AddComponent(a);
		asteroid->AddComponent(rB);
		asteroid->AddComponent(cC);
		asteroid->AddComponent(sW);
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(asteroid);
		return asteroid;
	}

	// Create the homing missile game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateMissileArchetype(Beta::Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* missile = new GameObject("Missile");
		Transform* t = new Transform(Vector2D(0, 0), Vector2D(0.25f, 0.25f));
		Sprite* s = new Sprite(mesh, spriteSource);
		RigidBody* rB = new RigidBody();
		HomingMissile* hM = new HomingMissile();
		ScreenWrap* sW = new ScreenWrap();
		ColliderCircle* cC = new ColliderCircle(t->GetScale().x / 2.0f);
		missile->AddComponent(t);
		missile->AddComponent(s);
		missile->AddComponent(rB);
		missile->AddComponent(hM);
		missile->AddComponent(sW);
		missile->AddComponent(cC);
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(missile);
		return missile;
	}

	// Create the homing missile game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateBombArchetype(Beta::Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* bomb = new GameObject("Bomb");
		Transform* t = new Transform(Vector2D(0, 0), Vector2D(0.2f, 0.2f));
		Sprite* s = new Sprite(mesh, spriteSource);
		Bomb* b = new Bomb();
		ColliderCircle* cC = new ColliderCircle(t->GetScale().x / 2.0f);
		bomb->AddComponent(t);
		bomb->AddComponent(s);
		bomb->AddComponent(b);
		bomb->AddComponent(cC);
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(bomb);
		return bomb;
	}

	// Create a tilemap object
	// Params:
	//   mesh = The mesh to use for the sprite.
	//   spriteSource = The sprite source to use for the sprite.
	//   map = The map to use for tilemap related components.
	// Returns:
	//   A pointer to the newly constructed game object.
	GameObject* CreateTilemapObject(Beta::Mesh* mesh, SpriteSource* spriteSource, Tilemap* map)
	{
		GameObject* tilemap = new GameObject("Tilemap");
		Transform* t = new Transform(Vector2D(-3.5, 2.5));
		SpriteTilemap* sT = new SpriteTilemap(mesh, spriteSource, map);
		ColliderTilemap* cT = new ColliderTilemap();
		cT->SetTilemap(map);
		tilemap->AddComponent(t);
		tilemap->AddComponent(sT);
		tilemap->AddComponent(cT);
		EngineCore::GetInstance().GetModule<GameObjectFactory>()->SaveObjectToFile(tilemap);
		return tilemap;
	}
}
