//------------------------------------------------------------------------------
//
// File Name:	ColorChange.cpp
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
#include "ColorChange.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "FileStream.h"

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Collision handler for ColorChange objects.
// Params:
//   object = The first object.
//   other  = The other object the first object is colliding with.
void ColorChangeCollisionHandler(GameObject& object, GameObject& other)
{
	UNREFERENCED_PARAMETER(other);
	object.GetComponent<ColorChange>()->collided = true;
}

// Constructor
// Params:
//   normalColor = The color that the object reverts to when not colliding.
//   collidedColor = The color that the object changes to when colliding.
//   collidedColorTime = The amount of time the object will retain the collided color.
ColorChange::ColorChange(const Beta::Color& normalColor_, const Beta::Color& collidedColor_,
	float collidedColorTime_) : 
	normalColor(normalColor_), collidedColor(collidedColor_), collidedColorTime(collidedColorTime_), 
	collided(false), timer(0.0f), sprite(nullptr),	Component("ColorChange")
{
}

// Return a new copy of the component.
Component* ColorChange::Clone() const
{
	return new ColorChange(*this);
}

// Initialize data for this object.
void ColorChange::Initialize()
{
	sprite = GetOwner()->GetComponent<Sprite>();
	GetOwner()->GetComponent<Collider>()->SetCollisionHandler(ColorChangeCollisionHandler);
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void ColorChange::Update(float dt)
{
	if (collided)
	{
		sprite->SetColor(collidedColor);
		collided = false;
		timer = collidedColorTime;
	}
	else if (!collided && timer <= 0)
		sprite->SetColor(normalColor);

	timer -= dt;
}

// Loads object data from a file.
// Params:
//   stream = The stream for the file we want to read from.
void ColorChange::Deserialize(FileStream& stream)
{
	stream.ReadVariable("normalColor", normalColor);
	stream.ReadVariable("collidedColor", collidedColor);
	stream.ReadVariable("collidedColorTime", collidedColorTime);
}

// Saves object data to a file.
// Params:
//   stream = The stream for the file we want to write to.
void ColorChange::Serialize(FileStream& stream) const
{
	stream.WriteVariable("normalColor", normalColor);
	stream.WriteVariable("collidedColor", collidedColor);
	stream.WriteVariable("collidedColorTime", collidedColorTime);
}