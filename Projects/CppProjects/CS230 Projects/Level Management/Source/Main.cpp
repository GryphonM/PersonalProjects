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

#include "Space.h"
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
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	// Unused parameters
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(show);
	UNREFERENCED_PARAMETER(instance);

	using namespace Beta;
	EngineCore& engine = EngineCore::GetInstance();

	// TO DO: Uncomment the following line to add the 
	// Space object to the engine as a module. The engine 
	// will automatically call the Space's Initialize, Update,
	// and Shutdown  functions when the engine is starting, 
	// updating, and shutting down respectively.
	// 
	//Space* space = engine.AddModule<Space>();

	// TO DO: Uncomment to set initial level to the first level.
	//space->SetLevel(new Levels::Level1());

	// Game engine goes!
	StartupSettings settings;
	settings.windowWidth = 800;
	settings.windowHeight = 600;
	settings.framerateCap = 200;

	// TO DO: Uncomment to redirect std::cout to file
	//std::streambuf* coutBuff = std::cout.rdbuf();
	//std::ofstream fileOutput("trace.txt");
	//std::cout.rdbuf(fileOutput.rdbuf());

	engine.Start(settings);

	// TO DO: Uncomment to redirect std::cout to file
	//std::cout.rdbuf(coutBuff);

	return 0;
}
