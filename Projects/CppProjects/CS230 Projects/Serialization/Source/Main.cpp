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
#include "SoundManager.h"
#include "GameObjectFactory.h"

// Initial game state
#include "Level1.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Main function
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR command_line, _In_ int show)
{
	// Unused parameters
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(show);
	UNREFERENCED_PARAMETER(instance);

	// Enable memory leak checking
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	// Add additional modules to engine
	using namespace Beta;
	EngineCore& engine = EngineCore::GetInstance();
	engine.AddModule<GameObjectFactory>();
	engine.AddModule<SoundManager>();
	Space* space = engine.AddModule<Space>();

	// Set initial level to the second level.
	space->SetLevel(new Level1());

	// Game engine goes!
	StartupSettings settings;
	settings.windowWidth = 800;
	settings.windowHeight = 600;
	//settings.framerateCap = 200;

	engine.Start(settings);

	return 0;
}
