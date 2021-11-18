//------------------------------------------------------------------------------
//
// File Name:	Lab2.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		Lab2
// Course:		MAT140
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Lab2.h"

#include "DebugDraw.h"	// AddDebugLine
#include "Vector2D.h"	// Vector2D
#include "GraphicsEngine.h"	// SetBackgroundColor
#include "Input.h"		// CheckTriggered, CheckHeld

#include "Animator.h"	// GetPointP, GetVectorU, GetVectorV

//------------------------------------------------------------------------------

using namespace Beta;

//------------------------------------------------------------------------------
// Static Variable Definitions:
//------------------------------------------------------------------------------

Lab2::ShapeVoidFunctionPtr Lab2::shapeFunctions[ShapeNum] =
{
	CreateTriangle,CreateParallelogram,
	CreateTriforce, CreateFace, CreateHexagon, CreateDiamondCut,
};

const Vector2D& Lab2::pointP = Animator::GetPointP();
const Vector2D& Lab2::vectorV = Animator::GetVectorV();
const Vector2D& Lab2::vectorU = Animator::GetVectorU();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/****************************************
*                                      *
*  MADE BY INSTRUCTOR - DO NOT CHANGE  *
*                                      *
****************************************/

// Constructor
Lab2::Lab2()
	: BetaObject("Level:Lab2"), shape(0)
{
}

// Initialize the memory associated with the Lab2 level.
void Lab2::Initialize()
{
	// TO DO: Print "Lab2::Initialize"

	// TO DO: Set Beta’s background color to white.
}

// Update the Lab2 level.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Lab2::Update(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	Input& input = *EngineGetModule(Input);
	DebugDraw& debugDraw = *EngineGetModule(DebugDraw);
	GraphicsEngine& graphics = *EngineGetModule(GraphicsEngine);

	debugDraw.SetCamera(graphics.GetDefaultCamera());

	// Change shape drawn when arrow keys are pressed
	if (input.CheckTriggered(VK_RIGHT))
	{
		++shape;
		if (shape >= ShapeNum)
		{
			shape = 0;
		}

	}
	if (input.CheckTriggered(VK_LEFT))
	{
		--shape;
		if (shape < 0)
		{
			shape = ShapeNum - 1;
		}
	}

	// Create shape using lines
	shapeFunctions[shape]();

	// End lines
	debugDraw.EndLineList();
}

// Free memory associated with the Lab2 level.
void Lab2::Shutdown()
{
	// TO DO: Print "Lab2::Shutdown"
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Draw a red line
void Lab2::DrawLine(const Vector2D& start, const Vector2D& end)
{
	EngineGetModule(DebugDraw)->AddLineToList(start, end, Colors::Red);
}

/****************************************
*                                      *
*		STUDENT CODE GOES HERE         *
*                                      *
****************************************/

void Lab2::CreateTriangle()
{
	// PV (a point) = P (a point) + V (a vector)
	Vector2D pointPV = pointP + vectorV;

	// Draw a line from point P to point PV
	DrawLine(pointP, pointPV);
}

void Lab2::CreateParallelogram()
{

}

void Lab2::CreateTriforce()
{

}

void Lab2::CreateFace()
{

}

void Lab2::CreateHexagon()
{

}

void Lab2::CreateDiamondCut()
{

}
