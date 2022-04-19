//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
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
#include "Collider.h"
//#include "Intersection2D.h"
#include "Transform.h"
#include "RigidBody.h"
#include "GameObject.h"

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Allocate a new collider component.
// Params:
//   type = The type of collider (see the ColliderType enum).
Collider::Collider(ColliderType type_) : transform(nullptr), rigidBody(nullptr),
	type(type_), handler(nullptr), Component("Collider")
{
}

// Set component pointers.
void Collider::Initialize()
{
	transform = dynamic_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	rigidBody = dynamic_cast<RigidBody*>(GetOwner()->GetComponent("RigidBody"));
}

// Check if two objects are colliding and send collision events.
// Params:
//	 other = Reference to the second collider component.
void Collider::CheckCollision(const Collider& other)
{
	if (IsCollidingWith(other))
	{
		handler(*this->GetOwner(), *other.GetOwner());
		other.handler(*this->GetOwner(), *other.GetOwner());
	}
}

// Get the type of this component.
ColliderType Collider::GetType() const
{
	return type;
}

// Sets the collision handler function for the collider.
// Params:
//   handler = A pointer to the collision handler function.
void Collider::SetCollisionHandler(CollisionEventHandler handler_)
{
	handler = handler_;
}