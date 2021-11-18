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
	std::cout << "Lab2::Initialize" << std::endl;

	EngineGetModule(Beta::GraphicsEngine)->SetBackgroundColor(Colors::White);
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
	std::cout << "Lab2::Shutdown" << std::endl;
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
	// Determine Points
	Vector2D pointP_V = pointP + vectorV;
	Vector2D pointP_U = pointP + vectorU;

	// Draw lines
	DrawLine(pointP, pointP_V);
	DrawLine(pointP, pointP_U);
	DrawLine(pointP_U, pointP_V);
}

void Lab2::CreateParallelogram()
{
	// Determine Points
	Vector2D pointP_V = pointP + vectorV;
	Vector2D pointP_U = pointP + vectorU;
	Vector2D pointPV_U = pointP_V + vectorU;

	// Draw lines
	DrawLine(pointP, pointP_V);
	DrawLine(pointP, pointP_U);
	DrawLine(pointPV_U, pointP_V);
	DrawLine(pointPV_U, pointP_U);
}

void Lab2::CreateTriforce()
{
	// Outer Triangle
	// Determine Points
	Vector2D pointP_V = pointP + vectorV;
	Vector2D pointP_U = pointP + vectorU;

	// Draw lines
	DrawLine(pointP, pointP_V);
	DrawLine(pointP, pointP_U);
	DrawLine(pointP_U, pointP_V);

	// Inner Triangle
	// Determine Points
	Vector2D midpointP_PV = pointP + (0.5 * vectorV);
	Vector2D midpointP_PU = pointP + (0.5 * vectorU);
	Vector2D midpointPV_PU = 0.5 * (pointP_V + pointP_U);

	// Draw Lines
	DrawLine(midpointP_PV, midpointP_PU);
	DrawLine(midpointP_PV, midpointPV_PU);
	DrawLine(midpointP_PU, midpointPV_PU);
}

void Lab2::CreateFace()
{
	// Helper Points
	Vector2D pointP_V = pointP + vectorV;
	Vector2D pointP_U = pointP + vectorU;
	Vector2D backPointP_V = pointP - vectorV;
	Vector2D backPointP_U = pointP - vectorU;
	
	// Eye Outlines
	// Determine Points
	Vector2D midpointP_V = pointP + (0.5 * vectorV);
	Vector2D midpointP_U = pointP + (0.5 * vectorU);
	Vector2D midpointPV_PU = 0.5 * (pointP_V + pointP_U);
	Vector2D backMidpointP_V = pointP - (0.5 * vectorV);
	Vector2D backMidpointP_U = pointP - (0.5 * vectorU);
	Vector2D backMidpointPV_PU = 0.5 * (backPointP_V + backPointP_U);

	// Draw Lines
	DrawLine(pointP, midpointP_V);
	DrawLine(pointP, midpointP_U);
	DrawLine(midpointP_U, midpointPV_PU);
	DrawLine(midpointP_V, midpointPV_PU);
	DrawLine(pointP, backMidpointP_V);
	DrawLine(pointP, backMidpointP_U);
	DrawLine(backMidpointP_U, backMidpointPV_PU);
	DrawLine(backMidpointP_V, backMidpointPV_PU);

	// Pupils
	// Determine Origin
	Vector2D midpointMMPU_MPV = 0.5 * (midpointP_U + midpointP_V);
	Vector2D backMidpointMMPU_MPV = 0.5 * (backMidpointP_U + backMidpointP_V);

	// Draw Circles
	EngineGetModule(DebugDraw)->AddCircle(midpointMMPU_MPV, 0.1, Colors::Red);
	EngineGetModule(DebugDraw)->AddCircle(backMidpointMMPU_MPV, 0.1, Colors::Red);

	// Mouth
	// Determine points
	Vector2D pointU_MPVPU = backMidpointPV_PU + vectorU;
	Vector2D midpointUMPVU_BMPV = 0.5 * (pointU_MPVPU + backMidpointP_V);
	Vector2D midpointUMPVU_MPU = 0.5 * (pointU_MPVPU + midpointP_U);

	// Draw Lins
	DrawLine(pointU_MPVPU, midpointUMPVU_BMPV);
	DrawLine(pointU_MPVPU, midpointUMPVU_MPU);
	DrawLine(midpointUMPVU_BMPV, midpointUMPVU_MPU);
}

void Lab2::CreateHexagon()
{
	// Helper Points
	Vector2D pointPV = pointP + vectorV;
	Vector2D pointPU = pointP + vectorU;

	// Determine Points
	Vector2D midpointP_PV1 = pointP + (0.25 * vectorV);
	Vector2D midpointP_PV2 = pointP + (0.75 * vectorV);

	Vector2D midpointP_PU1 = pointP + (0.25 * vectorU);
	Vector2D midpointP_PU2 = pointP + (0.75 * vectorU);

	Vector2D midpointPV_PU1 = 0.5 * (pointPV + (0.5 * (pointPV + pointPU)));
	Vector2D midpointPV_PU2 = 0.5 * (pointPU + (0.5 * (pointPV + pointPU)));

	// Draw Lines
	EngineGetModule(DebugDraw)->AddLineToList(pointP, pointPV, Colors::Orange);
	DrawLine(midpointP_PV1, midpointP_PV2);
	DrawLine(midpointP_PV2, midpointPV_PU1);
	EngineGetModule(DebugDraw)->AddLineToList(pointPV, pointPU, Colors::Orange);
	DrawLine(midpointPV_PU1, midpointPV_PU2);
	DrawLine(midpointPV_PU2, midpointP_PU2);
	EngineGetModule(DebugDraw)->AddLineToList(pointP, pointPU, Colors::Orange);
	DrawLine(midpointP_PU2, midpointP_PU1);
	DrawLine(midpointP_PU1, midpointP_PV1);
}

void Lab2::CreateDiamondCut()
{

}
