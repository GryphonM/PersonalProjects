//------------------------------------------------------------------------------
//
// File Name:	Enemy.c
// Author(s):	Jeremy Kings (j.kings)
// Project:		Dungeon
// Course:		VGP2
//
// Copyright © 2017 DigiPen (USA) Corporation.
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

// When player is at least this close, reset the level.
static const float visionDistance = 5.0f;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// Keep track of target patrol point
int nextPatrolPoint = 0;

//How far from the target the enemy has to be to have reached it
float closeEnough = 0.1f;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

typedef struct patrolPoints
{
	Vector2D* points;
	int size;
} patrolPoints;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void EnemyUpdate(GameObject* enemy, float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Determine target patrol point
	patrolPoints* Points = (patrolPoints *) GameObjectGetExtraData(enemy);
	Vector2D target = Points->points[nextPatrolPoint];

	// Grab my position
	const Vector2D* positionEnemy = GameObjectGetPosition(enemy);

	Vector2D velocity = { 0.0f, 0.0f };

	// Move towards next patrol point
	// Find direction from enemy to target
	Vector2DSub(&velocity, &target, positionEnemy);

	// Normalize direction vector.
	Vector2DNormalize(&velocity, &velocity);

	// Scale direction vector using speed.
	Vector2DScale(&velocity, &velocity, enemySpeed);

	// Determine the "close enough" point based on target
	float lowX = target.x - closeEnough;
	float highX = target.x + closeEnough;
	float lowY = target.y - closeEnough;
	float highY = target.x + closeEnough;

	// Determine if enemy has reached the target and set new target if so
	if (velocity.x >= lowX || velocity.x <= highX ||
		velocity.y >= lowY || velocity.y <= highY)
	{
		if (nextPatrolPoint == Points->size)
			nextPatrolPoint = 0;
		else
			nextPatrolPoint++;
	}

	/*// Grab player position
	const Vector2D* positionPlayer = PlayerGetPosition();

	// Calculate distance
	float distance = Vector2DDistance(&target, positionEnemy);

	Vector2D velocity = { 0.0f, 0.0f };

	// Restart level if player is close enough and in front of enemy.
	if (distance <= visionDistance)
	{
		// Find direction from enemy to player.
		Vector2DSub(&velocity, positionPlayer, positionEnemy);

		// Normalize direction vector.
		Vector2DNormalize(&velocity, &velocity);

		// Scale direction vector using speed.
		Vector2DScale(&velocity, &velocity, enemySpeed);
	}

	// Set velocity
	GameObjectSetVelocity(enemy, &velocity);
	*/
}
