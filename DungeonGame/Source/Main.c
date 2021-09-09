//------------------------------------------------------------------------------
//
// File Name:	Main.c
// Author(s):	Jeremy Kings (j.kings)
// Project:		Dungeon
// Course:		VGP2
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Engine.h" // AddLevel, Start

// Level Functions
#include "Level1.h"

//------------------------------------------------------------------------------
// Libraries
//------------------------------------------------------------------------------

#ifdef _DEBUG
	#pragma comment(lib, "TextEngine_D.lib")
#else
	#pragma comment(lib, "TextEngine.lib")
#endif

//------------------------------------------------------------------------------
// Main Function:
//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	// We are not using these params, but let's pretend we are
	// so that the compiler won't issue a warning.
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	// Add levels to the game
	EngineAddLevel(Level1Init, Level1Update, Level1Shutdown);

	// Set starting level
	EngineSetLevel(0);

	// Get the game loop up and running
	EngineStart(30.0f);

	// Check for memory leaks
	_CrtDumpMemoryLeaks(); 

	return 0;
}
