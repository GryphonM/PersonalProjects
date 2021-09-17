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
#include "Engine.h" // SetLevel
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
static int nextPatrolPoint = 0;

// How far from the target the enemy has to be to have reached it
float closeEnough = 0.1f;

// Keep track of where the enemy is facing
enum Directions{ up, down, left, right };
static enum Directions facing = left;

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Sets the enemies direction based on it's velocity.
// If velocity is diagonal, will set direction based on x.
// If velocity is 0, will do nothing
// Params:
//   velocity = the enemy's current velocity
void SetFacing(const Vector2D* velocity);

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void EnemyUpdate(GameObject* enemy, float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Determine target patrol point
	patrolPoints* Points = (patrolPoints *) GameObjectGetExtraData(enemy);
	// Make sure a value was passed in
	if (Points == NULL)
	{
		EngineSetLevel(gEngineLevelQuit);
	}
	else 
	{
		Vector2D target = Points->points[nextPatrolPoint];

		// Grab my position
		const Vector2D* position = GameObjectGetPosition(enemy);

		// Determine the "close enough" point based on target
		float lowX = target.x - closeEnough;
		float highX = target.x + closeEnough;
		float lowY = target.y - closeEnough;
		float highY = target.x + closeEnough;

		// Determine if enemy has reached the target and set new target if so
		if (position->x >= lowX && position->x <= highX &&
			position->y >= lowY && position->y <= highY)
		{
			if (nextPatrolPoint >= Points->size - 1)
				nextPatrolPoint = 0;
			else
				nextPatrolPoint++;

			// Set next patrol point
			target = Points->points[nextPatrolPoint];
		}

		// Move towards next patrol point
		Vector2D velocity = { 0.0f, 0.0f };

		// Find direction from enemy to target
		Vector2DSub(&velocity, &target, position);

		// Normalize direction vector.
		Vector2DNormalize(&velocity, &velocity);

		// Scale direction vector using speed.
		Vector2DScale(&velocity, &velocity, enemySpeed);

		// Determine if Player is in sight of Enemy
		// Grab player position
		const Vector2D* positionPlayer = PlayerGetPosition();

		// Calculate distance
		float distance = Vector2DDistance(positionPlayer, position);

		// If player is close enough to be seen, check if enemy is facing the player
		if (distance <= visionDistance)
		{
			// Determine direction enemy is facing
			SetFacing(&velocity);

			// Check the direction the enemy is facing with the players position
			// If player's x position is greater than enemy's x position, then it is to the right of it
			if (facing == right && positionPlayer->x > position->x)
				EngineSetLevel(gEngineLevelRestart);
			// If player's x position is less than enemy's x position, then it is to the left of it
			else if (facing == left && positionPlayer->x < position->x)
				EngineSetLevel(gEngineLevelRestart);
			// If player's y position is greater than enemy's y position, then it is above it
			else if (facing == up && positionPlayer->y > position->y)
				EngineSetLevel(gEngineLevelRestart);
			// If player's y position is less than enemy's y position, then it is below it
			else if (facing == down && positionPlayer->y < position->y)
				EngineSetLevel(gEngineLevelRestart);
		}

		// Set velocity
		GameObjectSetVelocity(enemy, &velocity);
	}
}

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Sets the enemies direction based on it's velocity.
// If velocity is diagonal, will set direction based on x.
// Params:
//   velocity = the enemy's current velocity
void SetFacing(const Vector2D* velocity)
{
	if (velocity->x > 0)
		facing = right;
	else if (velocity->x < 0)
		facing = left;
	else if (velocity->y > 0)
		facing = down;
	else if (velocity->y < 0)
		facing = down;
}