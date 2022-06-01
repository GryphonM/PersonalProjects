//------------------------------------------------------------------------------
//
// File Name:	Asteroid.cpp
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
#include "Asteroid.h"
#include "Bomb.h"
#include "HomingMissile.h"
#include "Space.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include "FileStream.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Collision handler for Asteroid objects.
// Params:
//   object = The first object.
//   other  = The other object the first object is colliding with.
void AsteroidCollisionHandler(GameObject& object, GameObject& other)
{
	if (other.GetName() == "Bullet" || 
		other.GetName() == "Missile" ||
		(other.GetName() == "Bomb" && other.GetComponent<Bomb>()->IsExploding()))
	{
		object.GetComponent<Asteroid>()->SpawnNewAsteroids();
		object.Destroy();
	}
}

// Set position of asteroid based on origin
void Asteroid::SetPosition()
{
	if (size == Size::Large)
	{
		Location corner = static_cast<Location>(Random::Range(0, 3));
		BoundingRectangle screen = EngineCore::GetInstance().GetModule<GraphicsEngine>()->GetDefaultCamera().GetScreenWorldDimensions();
		switch (corner)
		{
		case Location::TopLeft:
			transform->SetTranslation(Vector2D(screen.top - transform->GetScale().y - 1.0f, screen.left + transform->GetScale().x + 1.0f));
			break;
		case Location::TopRight:
			transform->SetTranslation(Vector2D(screen.top - transform->GetScale().y - 1.0f, screen.right - transform->GetScale().x - 1.0f));
			break;
		case Location::BottomLeft:
			transform->SetTranslation(Vector2D(screen.bottom + transform->GetScale().y + 1.0f, screen.left + transform->GetScale().x + 1.0f));
			break;
		case Location::BottomRight:
			transform->SetTranslation(Vector2D(screen.bottom + transform->GetScale().y + 1.0f, screen.right - transform->GetScale().x - 1.0f));
			break;
		}
	}
}

// Set velocity based on size
void Asteroid::SetVelocity()
{
	float angle = Random::Range(0.0f, 360.0f);
	float speed = Random::Range(speedMin, speedMax);
	Vector2D vel = Vector2D::FromAngleDegrees(angle) * speed;
	rigidBody->SetVelocity(vel);
}

// Generate new asteroids based off this asteroid
void Asteroid::SpawnNewAsteroids()
{
	if (!spawnedNew)
	{
		spawnedNew = true;
		if (size == Size::Large)
		{
			for (int i = 0; i < Random::Range(2, 3); i++)
			{
				GameObject* newAst = new GameObject(*GetOwner());
				newAst->GetComponent<Asteroid>()->size = Size::Medium;
				newAst->GetComponent<Transform>()->SetScale(spawnScaleModifier * transform->GetScale());
				newAst->GetComponent<ColliderCircle>()->SetRadius((spawnScaleModifier * transform->GetScale().x) / 2);
				GetOwner()->GetSpace()->GetObjectManager().AddObject(*newAst);
			}
		}
		else if (size == Size::Medium)
		{
			for (int i = 0; i < Random::Range(1, 2); i++)
			{
				GameObject* newAst = new GameObject(*GetOwner());
				newAst->GetComponent<Asteroid>()->size = Size::Small;
				newAst->GetComponent<Transform>()->SetScale(spawnScaleModifier * transform->GetScale());
				newAst->GetComponent<ColliderCircle>()->SetRadius((spawnScaleModifier * transform->GetScale().x) / 2);
				GetOwner()->GetSpace()->GetObjectManager().AddObject(*newAst);
			}
		}
	}
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Asteroid constructor
// Params:
//   speedMin = Minimum of range for asteroid movement speed.
//   speedMax = Maximum of range for asteroid movement speed.
//   basePointsValue = Point value for largest asteroid.
//   sizePointsModifier = Multiplicative scale applied to points for smaller asteroids.
//   spawnScaleModifier = Percentage of original asteroid's scale to use for new asteroids.
Asteroid::Asteroid(float speedMin_, float speedMax_, unsigned basePointsValue_, 
	float sizePointsModifier_, float spawnScaleModifier_) : 
	speedMin(speedMin_), speedMax(speedMax_), basePointsValue(basePointsValue_), spawnedNew(false),
	sizePointsModifier(sizePointsModifier_), spawnScaleModifier(spawnScaleModifier_), pointsGiven(false),
	size(Size::Large), location(Location::TopLeft), transform(nullptr), rigidBody(nullptr),
	Component("Asteroid")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* Asteroid::Clone() const
{
	return new Asteroid(*this);
}

// Initialize this component (happens at object creation).
void Asteroid::Initialize()
{
	transform = GetOwner()->GetComponent<Transform>();
	rigidBody = GetOwner()->GetComponent<RigidBody>();
	GetOwner()->GetComponent<Collider>()->SetCollisionHandler(AsteroidCollisionHandler);
	SetPosition();
	SetVelocity();
}

// Get the value of this object for increasing the player's score.
unsigned Asteroid::GetPointValue() const
{
	if (!pointsGiven)
	{
		pointsGiven = true;
		switch (size)
		{
		case Size::Medium:
			return static_cast<unsigned>(basePointsValue * sizePointsModifier);
		case Size::Small:
			return static_cast<unsigned>(basePointsValue * sizePointsModifier * sizePointsModifier);
		default:
			return basePointsValue;
		}
	}
	else
		return 0;
}

// Loads object data from a file.
// Params:
//   stream = The stream for the file we want to read from.
void Asteroid::Deserialize(FileStream& stream)
{
	stream.ReadVariable("minSpeed", speedMin);
	stream.ReadVariable("maxSpeed", speedMax);
	stream.ReadVariable("basePoints", basePointsValue);
	stream.ReadVariable("sizeModifier", sizePointsModifier);
	stream.ReadVariable("spawnModifier", spawnScaleModifier);
}

// Saves object data to a file.
// Params:
//   stream = The stream for the file we want to write to.
void Asteroid::Serialize(FileStream& stream) const
{
	stream.WriteVariable("minSpeed", speedMin);
	stream.WriteVariable("maxSpeed", speedMax);
	stream.WriteVariable("basePoints", basePointsValue);
	stream.WriteVariable("sizeModifier", sizePointsModifier);
	stream.WriteVariable("spawnModifier", spawnScaleModifier);
}