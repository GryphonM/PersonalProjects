//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.cpp
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
#include "PlayerShip.h"
#include "Transform.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "Collider.h"
#include "PlayerProjectile.h"
#include "HomingMissile.h"
#include "Bomb.h"
#include "Sprite.h"
#include "Space.h"
#include "SoundManager.h"
#include "FileStream.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Friend Functions:
//------------------------------------------------------------------------------

// Collision handler for PlayerShip objects.
// Params:
//   object = The first object.
//   other  = The other object the first object is colliding with.
void PlayerShipCollisionHandler(GameObject& object, GameObject& other)
{
	if ((other.GetName() == "Asteroid" && !dynamic_cast<PlayerShip*>(object.GetComponent("PlayerShip"))->isDying) ||
		(other.GetName() == "Bomb" && dynamic_cast<Bomb*>(other.GetComponent("Bomb"))->IsExploding()))
	{
		dynamic_cast<PlayerShip*>(object.GetComponent("PlayerShip"))->isDying = true;
		dynamic_cast<PlayerShip*>(object.GetComponent("PlayerShip"))->timer = dynamic_cast<PlayerShip*>(object.GetComponent("PlayerShip"))->deathDuration;
		dynamic_cast<Sprite*>(object.GetComponent("Sprite"))->SetColor(dynamic_cast<PlayerShip*>(object.GetComponent("PlayerShip"))->deadColor);
		dynamic_cast<RigidBody*>(object.GetComponent("RigidBody"))->SetAngularVelocity(dynamic_cast<PlayerShip*>(object.GetComponent("PlayerShip"))->spinSpeed);
	}
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Non-default constructor
// Params:
//   forwardThrust = Amount of force added to the ship when thrusters are activated.
//   maximumSpeed  = Maximum attainable speed of the ship.
//   rotationSpeed = Speed at which the ship rotates.
//   bulletSpeed   = Speed at which bullets move when fired by ship.
PlayerShip::PlayerShip(float forwardThrust_, float maximumSpeed_, float rotationSpeed_, float bulletSpeed_, float deathDuration_) :
	forwardThrust(forwardThrust_), maximumSpeed(maximumSpeed_), rotationSpeed(rotationSpeed_), bulletSpeed(bulletSpeed_),
	deathDuration(deathDuration_), score(0), timer(0.0f), isDying(false), blinkDuration(0.25f), blinkTimer(0.0f),
	deadColor(Colors::Red), spinSpeed(2.0f), blinkOn(false), missileWait(6.0f), missileTimer(0.0f), readyColor(Colors::Blue),
	normalColor(Colors::White), flashDuration(0.5f), flashTimer(0.0f), hasMissile(false), bombArchetype(nullptr),
	missileArchetype(nullptr), bulletArchetype(nullptr), transform(nullptr), rigidBody(nullptr), Component("PlayerShip")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* PlayerShip::Clone() const
{
	return new PlayerShip(*this);
}

// Initialize this component (happens at object creation).
void PlayerShip::Initialize()
{
	soundEvent = EngineCore::GetInstance().GetModule<SoundManager>()->PlayEvent("Test Tones");
	soundEvent->setPaused(true);
	soundEvent->setVolume(0.2f);
	soundEvent->setParameterValue("Wave Type", 0);
	soundEvent->setParameterValue("LowMidHigh", 0);

	bulletArchetype = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bullet");
	missileArchetype = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Missile");
	bombArchetype = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bomb");

	transform = dynamic_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	rigidBody = dynamic_cast<RigidBody*>(GetOwner()->GetComponent("RigidBody"));
	dynamic_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(PlayerShipCollisionHandler);
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void PlayerShip::Update(float dt)
{
	if (!isDying)
	{
		Move();
		Rotate();
		Shoot();
		MissileFire(dt);
		LayBomb();
	}
	else
		DeathSequence(dt);
}

// Return the player's current score.
unsigned PlayerShip::GetScore() const
{
	return score;
}

// Increase the player's score by the given amount.
void PlayerShip::IncreaseScore(unsigned amount)
{
	score += amount;
}

// Enables the Missile
void PlayerShip::EnableMissile()
{
	hasMissile = true;
}

// Pauses/Stops the sound event if it is playing
void PlayerShip::StopSoundEvent()
{
	if (soundEvent != nullptr)
		soundEvent->setPaused(true);
}

// Loads object data from a file.
// Params:
//   stream = The stream for the file we want to read from.
void PlayerShip::Deserialize(FileStream& stream)
{
	stream.ReadVariable("forwardThrust", forwardThrust);
	stream.ReadVariable("maximumSpeed", maximumSpeed);
	stream.ReadVariable("rotationSpeed", rotationSpeed);
	stream.ReadVariable("bulletSpeed", bulletSpeed);
}

// Saves object data to a file.
// Params:
//   stream = The stream for the file we want to write to.
void PlayerShip::Serialize(FileStream& stream) const
{
	stream.WriteVariable("forwardThrust", forwardThrust);
	stream.WriteVariable("maximumSpeed", maximumSpeed);
	stream.WriteVariable("rotationSpeed", rotationSpeed);
	stream.WriteVariable("bulletSpeed", bulletSpeed);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Move forward when up arrow is pressed
void PlayerShip::Move() const
{
	if (EngineCore::GetInstance().GetModule<Input>()->CheckHeld(38))
	{
		if (rigidBody->GetVelocity().Magnitude() < maximumSpeed)
			rigidBody->AddForce(Vector2D(forwardThrust, 0).Rotate(transform->GetRotation()));
		else
			rigidBody->SetVelocity(Vector2D(maximumSpeed, 0).Rotate(transform->GetRotation()));

		soundEvent->setPaused(false);
	}
	else
	{
		if (!AlmostEqual(rigidBody->GetVelocity().Magnitude(), 0, 0.1f))
			rigidBody->SetVelocity(Vector2D((rigidBody->GetVelocity().Magnitude() - 0.025f * forwardThrust), 0).Rotate(transform->GetRotation()));
		else
			rigidBody->SetVelocity(Vector2D(0, 0));

		soundEvent->setPaused(true);
	}
}

// Rotate when left or right arrow key is pressed
void PlayerShip::Rotate() const
{
	if (EngineCore::GetInstance().GetModule<Input>()->CheckHeld(39))
		rigidBody->SetAngularVelocity(-rotationSpeed);
	else if (EngineCore::GetInstance().GetModule<Input>()->CheckHeld(37))
		rigidBody->SetAngularVelocity(rotationSpeed);
	else
		rigidBody->SetAngularVelocity(0);
}

// Shoot projectiles when space is pressed
void PlayerShip::Shoot()
{
	if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered(' '))
	{
		GameObject* bullet = new GameObject(*bulletArchetype);
		dynamic_cast<Transform*>(bullet->GetComponent("Transform"))->SetTranslation(transform->GetTranslation());
		dynamic_cast<RigidBody*>(bullet->GetComponent("RigidBody"))->SetVelocity(Vector2D(bulletSpeed, 0).Rotate(transform->GetRotation()));
		dynamic_cast<PlayerProjectile*>(bullet->GetComponent("PlayerProjectile"))->SetSpawner(this);
		GetOwner()->GetSpace()->GetObjectManager().AddObject(*bullet);
	}
}

// Handles the missile firing
void PlayerShip::MissileFire(float dt)
{
	if (hasMissile && missileTimer <= 0)
	{
		dynamic_cast<Sprite*>(GetOwner()->GetComponent("Sprite"))->SetColor(readyColor);
		if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered(16))
		{
			missileTimer = missileWait;
			dynamic_cast<Sprite*>(GetOwner()->GetComponent("Sprite"))->SetColor(normalColor);

			GameObject* missile = new GameObject(*missileArchetype);
			dynamic_cast<Transform*>(missile->GetComponent("Transform"))->SetTranslation(transform->GetTranslation());
			dynamic_cast<HomingMissile*>(missile->GetComponent("HomingMissile"))->SetSpawner(this);
			GetOwner()->GetSpace()->GetObjectManager().AddObject(*missile);
		}
	}
	else
		missileTimer -= dt;
}

// Lays a bomb when the down key is pressed
void PlayerShip::LayBomb()
{
	if (EngineCore::GetInstance().GetModule<Input>()->CheckTriggered(40))
	{
		GameObject* bomb = new GameObject(*bombArchetype);
		dynamic_cast<Transform*>(bomb->GetComponent("Transform"))->SetTranslation(transform->GetTranslation());
		dynamic_cast<Bomb*>(bomb->GetComponent("Bomb"))->SetSpawner(this);
		GetOwner()->GetSpace()->GetObjectManager().AddObject(*bomb);
	}
}

// Play death "animation"
void PlayerShip::DeathSequence(float dt)
{
	timer -= dt;
	soundEvent->setPaused(true);
	if (timer > 0)
	{
		if (blinkTimer <= 0)
		{
			blinkTimer = blinkDuration;
			if (blinkOn)
				dynamic_cast<Sprite*>(GetOwner()->GetComponent("Sprite"))->SetAlpha(1);
			else
				dynamic_cast<Sprite*>(GetOwner()->GetComponent("Sprite"))->SetAlpha(0);
			blinkOn = !blinkOn;
		}
		else
			blinkTimer -= dt;
	}
	else
		GetOwner()->GetSpace()->RestartLevel();
}