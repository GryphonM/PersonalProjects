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

// When player is at least this close, chase the player.
static const float chaseDistance = 10.0f;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//Handle wall collision
static bool hitWall = false;
enum Direction{up, right, down, left, none};
static enum Direction wallDirection = none;

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
		
		if (hitWall)
		{
			if (wallDirection == up || wallDirection == down)
				//because the player is against a wall that is above or below them
				//they can only go left or right, therefore their y movement is 0
				velocity.y = 0;
			else if (wallDirection == right || wallDirection == left)
				//because the player is against a wall that is to the side of them
				//they can only go up or down, therefore their x movement is 0
				velocity.x = 0;

			wallDirection = none;
		}

		// Normalize direction vector.
		Vector2DNormalize(&velocity, &velocity);

		// Scale direction vector using speed.
		Vector2DScale(&velocity, &velocity, enemySpeed);
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
	Vector2D position = *GameObjectGetPosition(enemy);
	const Vector2D* scale = GameObjectGetScale(enemy);

	const Vector2D* wallPosition = GameObjectGetPosition(wall);

	hitWall = true;

	// Determine where the wall is
	if (velocity.x > 0)
		wallDirection = right;
	else if (velocity.x < 0)
		wallDirection = left;
	else if (velocity.y > 0)
		wallDirection = down;
	else if (velocity.y < 0)
		wallDirection = up;

	// Set position back to outside of wall
	// Same code from Wall.c with updated variable names and less pointers
	// Adjust object position based on current velocity and position
	if (velocity.x > 0.0f && position.x < wallPosition->x)
		position.x -= scale->x * 0.5f;
	else if (velocity.x < 0.0f && position.x > wallPosition->x)
		position.x += scale->x * 0.5f;

	if (velocity.y > 0.0f && position.y < wallPosition->y)
		position.y -= scale->y * 0.5f;
	else if (velocity.y < 0.0f && position.y > wallPosition->y)
		position.y += scale->y * 0.5f;

	velocity.x = 0.0f;
	velocity.y = 0.0f;

	GameObjectSetVelocity(enemy, &velocity);
}
