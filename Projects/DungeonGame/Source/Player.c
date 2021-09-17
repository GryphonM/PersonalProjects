//------------------------------------------------------------------------------
//
// File Name:	Player.c
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
#include "Player.h"

#include "GameObject.h" // GetPosition
#include "Vector2D.h" // Vector2D
#include "Engine.h" // IsKeyDown, SetLevel
#include "ObjectManager.h" // ObjectManagerDestroyObject

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Definitions:
//------------------------------------------------------------------------------

// Players Inventory Space
#define INVENTORY_SPACE 10

// Max Name Size for Player Inventory Items
#define INVENTORY_NAME_SIZE 20

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

// Player's movement speed in characters per second
static const float playerSpeed = 7.0f;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// Current position of player object (used by enemies to find player).
static Vector2D playerPosition = { 0.0f, 0.0f };

// List of strings represents inventory with default inventory
static char inventory[INVENTORY_SPACE][INVENTORY_NAME_SIZE] = { "Lockpick" };

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Retrieve the player's current position.
// Returns:
//   The player's current position.
const Vector2D* PlayerGetPosition(void)
{
	return &playerPosition;
}

// Retrieve the player's current inventory.
// Returns:
//   The player's current inventory.
void PlayerPrintInventory(short color, float xPos, float yPos)
{	
	for (int i = 0; i < INVENTORY_SPACE; i++)
	{
		if (strcmp(inventory[i], "") == 0)
			break;
		EngineDrawText(inventory[i], color, xPos, yPos + i);
	}
}

// Update the player-controlled object.
// Params:
//   player = The player game object.
//	 dt = Change in time (in seconds) since the last game loop.
void PlayerUpdate(GameObject* player, float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Calculate velocity based on input and speed
	Vector2D velocity = { 0.0f, 0.0f };

	// Note: The origin is in the top left,
	// and the positive y axis points downward.
	if (EngineIsKeyDown('W'))
		velocity.y += -1.0f;
	if (EngineIsKeyDown('S'))
		velocity.y += 1.0f;
	if (EngineIsKeyDown('D'))
		velocity.x += 1.0f;
	if (EngineIsKeyDown('A'))
		velocity.x += -1.0f;

	Vector2DNormalize(&velocity, &velocity);
	Vector2DScale(&velocity, &velocity, playerSpeed);
	GameObjectSetVelocity(player, &velocity);

	// Save player position
	playerPosition = *GameObjectGetPosition(player);
}

// Handle collision logic when player collides with the goal.
// Params:
//   player = The player game object.
//	 goal = The goal game object.
void PlayerCollisionGoal(GameObject* player, GameObject* goal)
{
	UNREFERENCED_PARAMETER(player);
	UNREFERENCED_PARAMETER(goal);

	// Go to the next level
	EngineSetLevel(gEngineLevelNext);
}

// Handle collision logic when player collides with an enemy.
// Params:
//   player = The player game object.
//	 enemy = The enemy game object.
void PlayerCollisionEnemy(GameObject* player, GameObject* enemy)
{
	UNREFERENCED_PARAMETER(player);
	UNREFERENCED_PARAMETER(enemy);
	
	EngineSetLevel(gEngineLevelRestart);
}

// Handle Collision logic when player collides with a door
// Params:
//   player = The player game object.
//   enemy = The enemy game object.
void PlayerCollisionDoor(GameObject* player, GameObject* door)
{
	UNREFERENCED_PARAMETER(player);

	int *nextLevel = GameObjectGetExtraData(door);

	EngineSetLevel(*nextLevel);
}
