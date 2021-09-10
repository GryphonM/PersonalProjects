//------------------------------------------------------------------------------
//
// File Name:	Enemy.c
// Author(s):	Jeremy Kings (j.kings)
// Project:		Dungeon
// Course:		VGP2
//
// Copyright � 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Enemy.h"

#include "GameObject.h" // GameObjectGetPosition
#include "Vector2D.h" // Vector2D
#include "Player.h" // GetPosition

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

// Speed of enemy movement.
static const float enemySpeed = 3.0f;

// When player is at least this close, chase the player.
static const float chaseDistance = 10.0f;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//Handle wall collision
static bool hitWall = false;
static enum Directions{up, right, down, left};
static enum Directions wallDirection;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void EnemyUpdate(GameObject* enemy, float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Grab my position
	const Vector2D* positionEnemy = GameObjectGetPosition(enemy);

	// Grab player position
	const Vector2D* positionPlayer = PlayerGetPosition();

	// Calculate distance
	float distance = Vector2DDistance(positionPlayer, positionEnemy);

	Vector2D velocity = { 0.0f, 0.0f };

	// Chase player if player is close enough.
	if (distance <= chaseDistance)
	{
		// Find direction from enemy to player.
		Vector2DSub(&velocity, positionPlayer, positionEnemy);
		
		if (!hitWall)
		{
			// Normalize direction vector.
			Vector2DNormalize(&velocity, &velocity);

			// Scale direction vector using speed.
			Vector2DScale(&velocity, &velocity, enemySpeed);
		}
		else
		{

		}
	}

	// Set velocity
	GameObjectSetVelocity(enemy, &velocity);
}

// Handles an Enemy's collision with walls
// Params:
//	 enemy = The enemy game object.
//	 wall = The wall game object.
void EnemyWallCollision(GameObject* enemy, GameObject* wall)
{
	UNREFERENCED_PARAMETER(wall);

	Vector2D velocity = *GameObjectGetVelocity(enemy);

	hitWall = true;

	if (velocity.x > velocity.y)
	{
		//if (velocity.x > 0)
			
	}
	else if (velocity.y > velocity.x)
	{

	}
	else
	{

	}

	velocity.x = 0.0f;
	velocity.y = 0.0f;

	GameObjectSetVelocity(enemy, &velocity);
}
