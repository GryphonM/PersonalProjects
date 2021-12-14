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
	Vector2D midpointP_PV = pointP + (0.5f * vectorV);
	Vector2D midpointP_PU = pointP + (0.5f * vectorU);
	Vector2D midpointPV_PU = 0.5f * (pointP_V + pointP_U);

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
	Vector2D midpointP_V = pointP + (0.5f * vectorV);
	Vector2D midpointP_U = pointP + (0.5f * vectorU);
	Vector2D midpointPV_PU = 0.5f * (pointP_V + pointP_U);
	Vector2D backMidpointP_V = pointP - (0.5f * vectorV);
	Vector2D backMidpointP_U = pointP - (0.5f * vectorU);
	Vector2D backMidpointPV_PU = 0.5f * (backPointP_V + backPointP_U);

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
	Vector2D midpointMMPU_MPV = 0.5f * (midpointP_U + midpointP_V);
	Vector2D backMidpointMMPU_MPV = 0.5f * (backMidpointP_U + backMidpointP_V);

	// Draw Circles
	EngineGetModule(DebugDraw)->AddCircle(midpointMMPU_MPV, 0.1f, Colors::Red);
	EngineGetModule(DebugDraw)->AddCircle(backMidpointMMPU_MPV, 0.1f, Colors::Red);

	// Mouth
	// Determine points
	Vector2D pointU_MPVPU = backMidpointPV_PU + vectorU;
	Vector2D midpointUMPVU_BMPV = 0.5f * (pointU_MPVPU + backMidpointP_V);
	Vector2D midpointUMPVU_MPU = 0.5f * (pointU_MPVPU + midpointP_U);

	// Draw Lins
	DrawLine(pointU_MPVPU, midpointUMPVU_BMPV);
	DrawLine(pointU_MPVPU, midpointUMPVU_MPU);
	DrawLine(midpointUMPVU_BMPV, midpointUMPVU_MPU);
}

void Lab2::CreateHexagon()
{
	// Helper Variables
	Vector2D pointPV = pointP + vectorV;
	Vector2D pointPU = pointP + vectorU;
	Vector2D vectorPVPU = pointPU - pointPV;

	// Determine Points
	Vector2D midpointPV1 = pointP + ((1 / 3.f) * vectorV);
	Vector2D midpointPV2 = pointP + ((2 / 3.f) * vectorV);

	Vector2D midpointPU1 = pointP + ((1 / 3.f) * vectorU);
	Vector2D midpointPU2 = pointP + ((2 / 3.f) * vectorU);

	Vector2D midpointPV_PU1 = pointPV + ((1 / 3.f) * vectorPVPU);
	Vector2D midpointPV_PU2 = pointPV + ((2 / 3.f) * vectorPVPU);

	// Draw Lines
	DrawLine(midpointPV1, midpointPV2);
	DrawLine(midpointPV2, midpointPV_PU1);
	DrawLine(midpointPV_PU1, midpointPV_PU2);
	DrawLine(midpointPV_PU2, midpointPU2);
	DrawLine(midpointPU2, midpointPU1);
	DrawLine(midpointPU1, midpointPV1);
}

void Lab2::CreateDiamondCut()
{
	// Helper Variables
	Vector2D pointPV = pointP + vectorV;
	Vector2D pointPU = pointP + vectorU;
	Vector2D vectorPVPU = pointPU - pointPV;

	// Inner Hexagon
	// Determine Points
	Vector2D midpointPV1 = pointP + ((1 / 3.f) * vectorV);
	Vector2D midpointPV2 = pointP + ((2 / 3.f) * vectorV);

	Vector2D midpointPU1 = pointP + ((1 / 3.f) * vectorU);
	Vector2D midpointPU2 = pointP + ((2 / 3.f) * vectorU);

	Vector2D midpointPV_PU1 = pointPV + ((1 / 3.f) * vectorPVPU);
	Vector2D midpointPV_PU2 = pointPV + ((2 / 3.f) * vectorPVPU);

	// Draw Lines
	DrawLine(midpointPV1, midpointPV2);
	DrawLine(midpointPV2, midpointPV_PU1);
	DrawLine(midpointPV_PU1, midpointPV_PU2);
	DrawLine(midpointPV_PU2, midpointPU2);
	DrawLine(midpointPU2, midpointPU1);
	DrawLine(midpointPU1, midpointPV1);

	// Outer Hexagon
	// Determine Points
	Vector2D endpointPV1 = pointPV - ((1 / 3.f) * vectorU);
	Vector2D endpointPV2 = pointPV + ((1 / 3.f) * vectorU);
	Vector2D endpointPU1 = pointPU - ((1 / 3.f) * vectorV);
	Vector2D endpointPU2 = pointPU + ((1 / 3.f) * vectorV);
	Vector2D endpointP1 = pointP + ((1 / 3.f) * vectorPVPU);
	Vector2D endpointP2 = pointP - ((1 / 3.f) * vectorPVPU);

	// Draw Lines
	DrawLine(endpointP1, endpointP2);
	DrawLine(endpointP2, endpointPV1);
	DrawLine(endpointPV1, endpointPV2);
	DrawLine(endpointPV2, endpointPU2);
	DrawLine(endpointPU2, endpointPU1);
	DrawLine(endpointPU1, endpointP1);

	// Connecting Lines
	DrawLine(midpointPV1, endpointP2);
	DrawLine(midpointPV2, endpointPV1);
	DrawLine(midpointPU1, endpointP1);
	DrawLine(midpointPU2, endpointPU1);
	DrawLine(midpointPV_PU1, endpointPV2);
	DrawLine(midpointPV_PU2, endpointPU2);
}
