//------------------------------------------------------------------------------
//
// File Name:	HomingMissile.cpp
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
#include "HomingMissile.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "PlayerShip.h"
#include "Asteroid.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include "Space.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Friend Functions:
//------------------------------------------------------------------------------

// Collision handler for HomingMissile objects.
// Params:
//   object = The first object.
//   other  = The other object the first object is colliding with.
void MissileCollisionHandler(GameObject& object, GameObject& other)
{
	if (other.GetName() == "Asteroid")
	{
		int points = dynamic_cast<Asteroid*>(other.GetComponent("Asteroid"))->GetPointValue();
		dynamic_cast<HomingMissile*>(object.GetComponent("HomingMissile"))->player->IncreaseScore(points);
		dynamic_cast<HomingMissile*>(object.GetComponent("HomingMissile"))->Explode();
	}
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default Constructor
// Params:
//   speed_ = The speed at which the missile approaches asteroids
HomingMissile::HomingMissile(float speed_) : speed(speed_), explosionRadius(1.0f),
	player(nullptr), targetID(0), transform(nullptr), rigidBody(nullptr), Component("HomingMissile")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* HomingMissile::Clone() const
{
	return new HomingMissile(*this);
}

// Initialize this component (happens at object creation).
void HomingMissile::Initialize()
{
	transform = dynamic_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	rigidBody = dynamic_cast<RigidBody*>(GetOwner()->GetComponent("RigidBody"));
	dynamic_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(MissileCollisionHandler);
	SetTarget();
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void HomingMissile::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	Move();
}

// Set the object that spawned this object
// Params:
//   player_ = the object to set the spawner to
void HomingMissile::SetSpawner(PlayerShip* player_)
{
	player = player_;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Handles a custom destruction
void HomingMissile::Explode()
{
	dynamic_cast<ColliderCircle*> (GetOwner()->GetComponent("Collider"))->SetRadius(explosionRadius);
	GetOwner()->Destroy();
}

// Finds the nearest Asteroid and sets it as the target
void HomingMissile::SetTarget()
{
	std::vector<GameObject*> Asteroids;
	GetOwner()->GetSpace()->GetObjectManager().GetObjectsByName("Asteroid", Asteroids);
	int target_ = Asteroids[0]->GetID();
	float currentDist = dynamic_cast<Transform*>(Asteroids[0]->GetComponent("Transform"))->GetTranslation().DistanceSquared(transform->GetTranslation());

	for (auto it = Asteroids.begin() + 1; it != Asteroids.end(); it++)
	{
		float dist = dynamic_cast<Transform*>((*it)->GetComponent("Transform"))->GetTranslation().DistanceSquared(transform->GetTranslation());
		if (dist < currentDist)
		{
			target_ = (*it)->GetID();
			currentDist = dist;
		}
	}

	targetID = target_;
}

// Find the direction toward the target and move that way
void HomingMissile::Move()
{
	GameObject* target = dynamic_cast<GameObject*>(GetOwner()->GetSpace()->GetObjectByID(targetID));
	if (target != nullptr)
	{
		Vector2D targetDir = dynamic_cast<Transform*>(target->GetComponent("Transform"))->GetTranslation() - transform->GetTranslation();
		float angle = atan2(targetDir.y, targetDir.x);
		transform->SetRotation(angle);
		rigidBody->SetVelocity(targetDir * speed);
	}
	else
		SetTarget();
}