//------------------------------------------------------------------------------
//
// File Name:	Level1.c
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
#include "Level1.h"

#include "curses.h" // Colors

#include "GameObject.h" // GameObject
#include "Vector2D.h" // Vector2D

#include "Player.h" // Update, Collisions
#include "Enemy.h" // Update
#include "Wall.h" // Collisions
#include "Engine.h" // DrawText
#include "ObjectManager.h" // AddObject, DestroyAllObjects

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

#define NUM_WALLS 5

static const float levelWidth = 49.0f;
static const float levelHeight = 19.0f;

static const Vector2D levelCenter = { 35.0f, 15.0f };

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void Level1CreateWalls(GameObject** walls);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the memory associated with the Level1 game state.
void Level1Init(void)
{
	// Create the player object
	Vector2D startPosition;
	startPosition.x = levelCenter.x - 15.0f;
	startPosition.y = levelCenter.y - 5.0f;
	GameObject* player = GameObjectCreate(startPosition.x, startPosition.y, 'o', COLOR_YELLOW, PlayerUpdate, NULL);

	// Create walls
	GameObject* walls[NUM_WALLS];
	Level1CreateWalls(walls);

	//define which room this door points to
	int* doorRoom = (int*)malloc(1 * sizeof(int));
	*doorRoom = 1;

	GameObject* door = GameObjectCreate(levelCenter.x + 5.0f, levelCenter.y + 5.0f, 'G', COLOR_GREEN, NULL, doorRoom);

	// Create enemy game objects
	// Create variables
	int totalPatrolPoints = 2;
	Vector2D* patrolPos = (Vector2D*)malloc(totalPatrolPoints * sizeof(Vector2D));
	// Set patrol positions
	patrolPos[0].x = levelCenter.x - 5.0f;
	patrolPos[0].y = levelCenter.y - 5.0f;
	patrolPos[1].x = levelCenter.x + 5.0f;
	patrolPos[1].y = levelCenter.y - 5.0f;
	// Create patrolPoints structure
	patrolPoints* Points = (patrolPoints*)malloc(sizeof(patrolPoints));
	Points->points = patrolPos;
	Points->size = totalPatrolPoints;
	// Create game object
	GameObject* enemy = GameObjectCreate(patrolPos[0].x, patrolPos[0].y, 'X', COLOR_RED, EnemyUpdate, Points);

	// Check for player and enemy collision with walls
	for (int i = 0; i < NUM_WALLS; ++i)
	{
		GameObjectAddCollisionPair(player, walls[i], WallCollision);
	}

	// Check other collisions
	GameObjectAddCollisionPair(player, door, PlayerCollisionDoor);
	GameObjectAddCollisionPair(player, enemy, PlayerCollisionEnemy);

	// Register objects with Object Manager to ensure they are updated
	ObjectManagerAddObject(player);
	ObjectManagerAddObject(door);
	ObjectManagerAddObject(enemy);

	// Create a color pair to use later
	EngineSetColorPair(0, COLOR_WHITE, COLOR_BLUE);
	EngineSetColorPair(1, COLOR_BLACK, COLOR_CYAN);
	EngineSetColorPair(2, COLOR_BLACK, COLOR_GREEN);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Level1Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Draw level title
	EngineDrawTextColorPair("DUNGEON", 1, levelCenter.x - 3.0f, levelCenter.y - 14.0f);
	EngineDrawText("Outside Front Gate", COLOR_GREEN, levelCenter.x - 9.0f, levelCenter.y - 12.0f);

	// Draw objective
	EngineDrawTextColorPair("Objective:", 0, levelCenter.x + 26.0f, levelCenter.y - 9.0f);
	EngineDrawText("Break into house", COLOR_WHITE, levelCenter.x + 26.0f, levelCenter.y - 8.0f);

	// Display inventory
	// Draw inventory title
	EngineDrawTextColorPair("Inventory:", 2, levelCenter.x + 26.0f, levelCenter.y - 5.0f);

	// Call player function to print inventory with given print locations
	PlayerPrintInventory(COLOR_WHITE, levelCenter.x + 26.0f, levelCenter.y - 4.0f);
}

// Free any memory associated with the Level1 game state.
void Level1Shutdown(void)
{
	ObjectManagerDestroyAllObjects();
}

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void Level1CreateWalls(GameObject** walls)
{
	// Top
	walls[0] = WallCreate(levelCenter.x, levelCenter.y - levelHeight / 2.0f, levelWidth, 1.0f);

	// Bottom
	walls[1] = WallCreate(levelCenter.x, levelCenter.y + levelHeight / 2.0f, levelWidth, 1.0f);

	// Left
	walls[2] = WallCreate(levelCenter.x - levelWidth / 2.0f, levelCenter.y, 1.0f, levelHeight + 1.0f);

	// Right
	walls[3] = WallCreate(levelCenter.x + levelWidth / 2.0f, levelCenter.y, 1.0f, levelHeight);

	// Near goal
	walls[4] = WallCreate(levelCenter.x, levelCenter.y, 20.0f, 3.0f);

	// Register objects with Object Manager to ensure they are updated
	for (int i = 0; i < NUM_WALLS; ++i)
		ObjectManagerAddObject(walls[i]);
}
