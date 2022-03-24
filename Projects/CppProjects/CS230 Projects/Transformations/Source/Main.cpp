//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

// Engine modules
#include "Space.h"

// Initial game state
#include "Level1.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Main function
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR command_line, _In_ int show)
{
	// Enable memory leak checking
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	// Unused parameters
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(show);
	UNREFERENCED_PARAMETER(instance);

	// Add additional modules to engine
	using namespace Beta;
	EngineCore& engine = EngineCore::GetInstance();
	Space* space = engine.AddModule<Space>();

	int* number = new int;
	UNREFERENCED_PARAMETER(number);

	// Set initial level to the second level.
	space-> SetLevel(new Levels::Level1());

	// Game engine goes!
	StartupSettings settings;
	settings.windowWidth = 800;
	settings.windowHeight = 600;
	//settings.framerateCap = 200;

	engine.Start(settings);

	//_CrtDumpMemoryLeaks();

	return 0;
}
