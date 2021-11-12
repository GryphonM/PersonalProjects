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
	std::cout << "Lab1: Initialize" << std::endl;

	EngineGetModule(Beta::GraphicsEngine)->SetBackgroundColor(Colors::White);
}

// Update the Lab1 level.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Lab1::Update(float dt)
{
	// Variable Declarations	
	DebugDraw& draw = *EngineGetModule(DebugDraw);
	Vector2D secondsLineEnd;
	Vector2D minutesLineEnd;
	Vector2D hourLineEnd;

	// Draw the circle
	draw.AddCircle(origin, lineLength, Colors::Black);

	// Define ends of lines
	angle1 += dt * rotationalVelocity * 60;
	angle2 += dt * rotationalVelocity;
	angle3 += dt * rotationalVelocity / 60;

	secondsLineEnd.x = lineLength * sin(angle1);
	secondsLineEnd.y = lineLength * cos(angle1);

	minutesLineEnd.x = (lineLength - 0.2) * sin(angle2);
	minutesLineEnd.y = (lineLength - 0.2) * cos(angle2);
	
	hourLineEnd.x = (lineLength - 0.4) * sin(angle3);
	hourLineEnd.y = (lineLength - 0.4) * cos(angle3);

	// Draw Lines
	draw.AddLineToList(origin, secondsLineEnd, Colors::Red);
	draw.AddLineToList(origin, minutesLineEnd, Colors::Green);
	draw.AddLineToList(origin, hourLineEnd, Colors::Blue);
	draw.EndLineList();
}

// Shut down the Lab1 level.
void Lab1::Shutdown()
{
	std::cout << "Lab1: Shutdown" << std::endl;
}
