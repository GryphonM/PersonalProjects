//------------------------------------------------------------------------------
//
// File Name:	PlayerProjectile.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.1.7 Assignment: Asteroids
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PlayerProjectile.h"
#include "GameObject.h"
#include "PlayerShip.h"
#include "Asteroid.h"
#include "Collider.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Collision handler for PlayerProjectile objects.
// Params:
//   object = The first object.
//   other  = The other object the first object is colliding with.
void PlayerProjectileCollisionHandler(GameObject& object, GameObject& other)
{
	if (other.GetName() == "Asteroid")
	{
		int points = other.GetComponent<Asteroid>()->GetPointValue();
		object.GetComponent<PlayerProjectile>()->player->IncreaseScore(points);
		object.Destroy();
	}
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default constructor
PlayerProjectile::PlayerProjectile() : player(nullptr), Component("PlayerProjectile")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* PlayerProjectile::Clone() const
{
	return new PlayerProjectile(*this);
}

// Initialize this component (happens at object creation).
void PlayerProjectile::Initialize()
{
	GetOwner()->GetComponent<Collider>()->SetCollisionHandler(PlayerProjectileCollisionHandler);
}

// Set the object that spawned this object
void PlayerProjectile::SetSpawner(PlayerShip* player_)
{
	player = player_;
}