#pragma once

//------------------------------------------------------------------------------
//
// File Name:	Lab1.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		Lab1
// Course:		MAT140
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Lab1.h"

#include "DebugDraw.h" // AddDebugLine
#include "Vector2D.h"  // Vector2D
#include "GraphicsEngine.h"  // SetBackgroundColor

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

using namespace Beta;

// Constructor: Initialize helpful variables declared in Lab1.h.
Lab1::Lab1()
	: BetaObject("Level:Lab1"), pi(static_cast<float>(M_PI)), lineLength(2.0f),
	rotationalVelocity((2.0f * pi) / 60.0f),
	angle1(pi / 2.0f), angle2(pi / 2.0f), angle3(pi / 2.0f)
{

}

// Initialize the Lab1 level.
void Lab1::Initialize()
{
	// TO DO: Print "Lab1: Initialize" to the console

	// TO DO: Set Beta’s background color to white.
	//EngineGetModule(Beta::GraphicsEngine)->SetBackgroundColor(Beta::Colors:: );
}

// Update the Lab1 level.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Lab1::Update(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	// TO DO: Remove this line if/when you actually start using 'dt'.
	UNREFERENCED_PARAMETER(dt);

	// TO DO: Create variable declarations for points/vectors (Beta::Vector2D) and floats as needed.

	// TO DO: Draw a circle (see assignment page for link to example code)

	// TO DO: Draw lines (see assignment page for link to example code)
}

// Shut down the Lab1 level.
void Lab1::Shutdown()
{
	// TO DO: Print "Lab1: Shutdown" to the console
}
