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

#include "Vector2D.h" // Vector2D

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct GameObject GameObject;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//typedef struct patrolPoints patrolPoints;

typedef struct patrolPoints
{
	Vector2D* points;
	int size;
} patrolPoints;

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Update the enemy object.
// Params:
//   enemy = The enemy game object.
//	 dt = Change in time (in seconds) since the last game loop.
void EnemyUpdate(GameObject* enemy, float dt);
