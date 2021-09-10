//------------------------------------------------------------------------------
//
// File Name:	Enemy.h
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

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Update the enemy object.
// Params:
//   enemy = The enemy game object.
//	 dt = Change in time (in seconds) since the last game loop.
void EnemyUpdate(GameObject* enemy, float dt);

// Handles an Enemy's collision with walls
// Params:
//	 enemy = The enemy game object.
//	 wall = The wall game object.
void EnemyWallCollision(GameObject* enemy, GameObject* wall);
