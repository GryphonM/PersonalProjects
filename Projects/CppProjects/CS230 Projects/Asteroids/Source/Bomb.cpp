//------------------------------------------------------------------------------
//
// File Name:	Bomb.cpp
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
#include "Bomb.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "PlayerShip.h"
#include "Asteroid.h"
#include "Collider.h"
#include "ColliderCircle.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Friend Functions:
//------------------------------------------------------------------------------

// Collision handler for Bomb objects.
// Params:
//   object = The first object.
//   other  = The other object the first object is colliding with.
void BombCollisionHandler(GameObject& object, GameObject& other)
{
	if (other.GetName() == "Asteroid" && dynamic_cast<Bomb*>(object.GetComponent("Bomb"))->exploding)
	{
		int points = dynamic_cast<Asteroid*>(other.GetComponent("Asteroid"))->GetPointValue();
		dynamic_cast<Bomb*>(object.GetComponent("Bomb"))->player->IncreaseScore(points);
	}
	else if (other.GetName() == "Bullet" && !dynamic_cast<Bomb*>(object.GetComponent("Bomb"))->exploding)
	{
		dynamic_cast<Bomb*>(object.GetComponent("Bomb"))->StartExplosion();
		other.Destroy();
	}
	else if (other.GetName() == "Bomb" && dynamic_cast<Bomb*>(object.GetComponent("Bomb"))->exploding 
		&& !dynamic_cast<Bomb*>(other.GetComponent("Bomb"))->exploding)
		dynamic_cast<Bomb*>(other.GetComponent("Bomb"))->StartExplosion();
}
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default Constructor
// Params:
//   explosionRadius_ = The radius the bomb explodes with
Bomb::Bomb(float explosionRadius_) : Component("Bomb"), 
	explosionRadius(explosionRadius_), waitDuration(3.0f), 
	waitTimer(0.0f), explosionDuration(0.5f), explosionTimer(0.0f), 
	exploding(false), blinkDuration(0.25f), blinkTime(0.0f), 
	blink(false), normalColor(Colors::Orange), blinkColor(Colors::White), 
	transform(nullptr), player(nullptr), collider(nullptr), sprite(nullptr)
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* Bomb::Clone() const
{
	return new Bomb(*this);
}

// Initialize this component (happens at object creation).
void Bomb::Initialize()
{
	transform = dynamic_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	sprite = dynamic_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
	collider = dynamic_cast<ColliderCircle*>(GetOwner()->GetComponent("Collider"));
	waitTimer = waitDuration;
	dynamic_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(BombCollisionHandler);
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void Bomb::Update(float dt)
{
	if (!exploding)
	{
		if (waitTimer > 0)
		{
			if (blinkTime <= 0)
			{
				if (blink)
					sprite->SetColor(normalColor);
				else
					sprite->SetColor(blinkColor);
				blink = !blink;
				blinkTime = blinkDuration;
			}
			else
				blinkTime -= dt;
			waitTimer -= dt;
		}
		else
			StartExplosion();
	}
	else
	{
		if (explosionTimer <= 0)
			GetOwner()->Destroy();
		else
			explosionTimer -= dt;
	}
}

// Set the object that spawned this object
// Params:
//   player_ = the object to set the spawner to
void Bomb::SetSpawner(PlayerShip* player_)
{
	player = player_;
}

// Gettor for exploding
// Returns:
//   the value of exploding
bool Bomb::IsExploding()
{
	return exploding;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Handles the start of the explosion
void Bomb::StartExplosion()
{
	exploding = true;
	explosionTimer = explosionDuration;
	collider->SetRadius(explosionRadius);
}