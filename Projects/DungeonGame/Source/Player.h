//------------------------------------------------------------------------------
//
// File Name:	Player.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Dungeon
// Course:		VGP2
//
// Copyright � 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct GameObject GameObject;
typedef struct Vector2D Vector2D;

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Retrieve the player's current position.
// Returns:
//   The player's current position.
const Vector2D* PlayerGetPosition(void);

// Retrieve the player's current inventory.
// Params:
//	 xPos = the X Position at which to print the inventory
//	 yPos = the Y Position at which to print the first bit of inventory
void PlayerPrintInventory(short color, float xPos, float yPos);

// Update the player-controlled object.
// Params:
//   player = The player game object.
//	 dt = Change in time (in seconds) since the last game loop.
void PlayerUpdate(GameObject* player, float dt);

// Update the player-controlled object.
// Params:
//   player = The player game object.
//	 dt = Change in time (in seconds) since the last game loop.
void PlayerUpdate(GameObject* player, float dt);

// Handle collision logic when player collides with the goal.
// Params:
//   player = The player game object.
//	 goal = The goal game object.
void PlayerCollisionGoal(GameObject* player, GameObject* goal);

// Handle collision logic when player collides with an enemy.
// Params:
//   player = The player game object.
//	 enemy = The enemy game object.
void PlayerCollisionEnemy(GameObject* player, GameObject* enemy);

// Handle Collision logic when player collides with a door
// Params:
//   player = The player game object.
//   door = The door game object.
void PlayerCollisionDoor(GameObject* player, GameObject* door);
