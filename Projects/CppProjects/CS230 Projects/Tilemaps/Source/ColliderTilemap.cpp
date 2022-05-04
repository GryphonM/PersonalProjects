//------------------------------------------------------------------------------
//
// File Name:	SpriteTilemap.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 8.0.1 Assignment: Tilemaps
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "ColliderTilemap.h"
#include "Tilemap.h"
#include "ColliderRectangle.h"
#include "Transform.h"
#include "RigidBody.h"
#include "GameObject.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor for Tilemap collider.
ColliderTilemap::ColliderTilemap() : Collider(ColliderType::Tilemap), map(nullptr)
{
}

// Clone an collider and return a pointer to the cloned object.
// Returns:
//   A pointer to a collider.
Component* ColliderTilemap::Clone() const
{
	return new ColliderTilemap(*this);
}

// Check for collision between a tilemap and another arbitrary collider.
// Params:
//	 other = Reference to the second collider component.
// Returns:
//	 Return the results of the collision check.
bool ColliderTilemap::IsCollidingWith(const Collider& other) const
{
	BoundingRectangle edges = BoundingRectangle(dynamic_cast<Transform*>(other.GetOwner()->GetComponent("Transform"))->GetTranslation(),
		dynamic_cast<const ColliderRectangle&>(other).GetExtents());
	MapCollision collisions = MapCollision(IsSideColliding(edges, RectangleSide::Bottom), IsSideColliding(edges, RectangleSide::Top),
		IsSideColliding(edges, RectangleSide::Left), IsSideColliding(edges, RectangleSide::Right));
	ResolveCollisions(edges, dynamic_cast<Transform*>(other.GetOwner()->GetComponent("Transform")), 
		dynamic_cast<RigidBody*>(other.GetOwner()->GetComponent("RigidBody")), collisions);

	bool collided = collisions.bottom || collisions.top || collisions.right || collisions.left;
	if (collided)
	{
		other.GetMapCollisionHandler()(other.GetOwner(), collisions);
		return true;
	}
	return false;
}

// Sets the tilemap to use for this collider.
// Params:
//   map = A pointer to the tilemap resource.
void ColliderTilemap::SetTilemap(const Tilemap* map_)
{
	map = map_;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Checks whether the specified side of a given rectangle is colliding with the tilemap.
// Params:
//   rectangle = The bounding rectangle for an object.
//   side = The side that needs to be tested for collision.
// Returns:
//   True if there is a collision, false otherwise.
bool ColliderTilemap::IsSideColliding(const BoundingRectangle& rectangle, RectangleSide side) const
{
	if (side == RectangleSide::Bottom)
	{
		Vector2D hotspot1 = Vector2D(0.5f * (rectangle.center.x - rectangle.left), rectangle.bottom);
		Vector2D hotspot2 = Vector2D(0.5f * (rectangle.right - rectangle.center.x), rectangle.bottom);
		if (IsCollidingAtPosition(hotspot1.x, hotspot1.y) || IsCollidingAtPosition(hotspot2.x, hotspot2.y))
			return true;
		else
			return false;
	}
	else if (side == RectangleSide::Top)
	{
		Vector2D hotspot1 = Vector2D(0.5f * (rectangle.center.x - rectangle.left), rectangle.top);
		Vector2D hotspot2 = Vector2D(0.5f * (rectangle.right - rectangle.center.x), rectangle.top);
		if (IsCollidingAtPosition(hotspot1.x, hotspot1.y) || IsCollidingAtPosition(hotspot2.x, hotspot2.y))
			return true;
		else
			return false;
	}
	else if (side == RectangleSide::Left)
	{
		Vector2D hotspot1 = Vector2D(rectangle.left, 0.5f * (rectangle.center.y - rectangle.bottom));
		Vector2D hotspot2 = Vector2D(rectangle.left, 0.5f * (rectangle.top - rectangle.center.y));
		if (IsCollidingAtPosition(hotspot1.x, hotspot1.y) || IsCollidingAtPosition(hotspot2.x, hotspot2.y))
			return true;
		else
			return false;
	}
	else if (side == RectangleSide::Right)
	{
		Vector2D hotspot1 = Vector2D(rectangle.right, 0.5f * (rectangle.center.y - rectangle.bottom));
		Vector2D hotspot2 = Vector2D(rectangle.right, 0.5f * (rectangle.top - rectangle.center.y));
		if (IsCollidingAtPosition(hotspot1.x, hotspot1.y) || IsCollidingAtPosition(hotspot2.x, hotspot2.y))
			return true;
		else
			return false;
	}
}

// Determines whether a point is within a collidable cell in the tilemap.
// Params:
//   x = The x component of the point, in world coordinates.
//   y = The y component of the point, in world coordinates.
// Returns:
//   False if the point is outside the map or the map is empty at that position, 
//   or true if there is a tile at that position.
bool ColliderTilemap::IsCollidingAtPosition(float x, float y) const
{
	Vector2D tilePos = transform->GetInverseMatrix() * Vector2D(x, y);
	tilePos.x = static_cast<int>(tilePos.x);
	tilePos.y = -static_cast<int>(tilePos.y);
	if (map->GetCellValue(tilePos.y, tilePos.x) == 0)
		return false;
	else
		return true;
}

// Moves an object and sets its velocity based on where it collided with the tilemap.
// Params:
//   objectRectangle = A bounding rectangle that encompasses the object.
//   objectTransform = Pointer to the object's transform component.
//   objectRigidBody = Pointer to the object's rigidBody component.
//   collisions = True/false values from map collision checks.
void ColliderTilemap::ResolveCollisions(const BoundingRectangle& objectRectangle, Transform* objectTransform,
	RigidBody* objectRigidBody, const MapCollision& collisions) const
{
	Vector2D newPos = objectTransform->GetTranslation();
	Vector2D newVel = objectRigidBody->GetVelocity();
	if (collisions.bottom || collisions.top)
	{
		newPos.y = objectRigidBody->GetOldTranslation().y;
		newVel.y = 0;
	}
	if (collisions.right || collisions.left)
	{
		newPos.x = objectRigidBody->GetOldTranslation().x;
		newVel.x = 0;
	}
	objectTransform->SetTranslation(newPos);
	objectRigidBody->SetVelocity(newVel);
}

// Returns the center of the next tile on the x-axis or y-axis.
// Used for assisting in collision resolution on a particular side.
// Params:
//   side = Which side the collision is occurring on.
//   sidePosition = The x or y value of that side.
// Returns:
//   The center of the next tile for the given position on the given side.
float ColliderTilemap::GetNextTileCenter(RectangleSide side, float sidePosition) const
{

}