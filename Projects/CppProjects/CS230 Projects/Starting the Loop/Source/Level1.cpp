// Level1.cpp
#include "stdafx.h"
#include "Level1.h"

Level1::Level1() : BetaObject("Level1")
{
}

// Initializes the level
void Level1::Initialize()
{
	std::cout << "Level1::Initialize" << std::endl;
}

// Updates the level based on the time passed since the last interval
void Level1::Update(float dt)
{
	std::cout << "Level1::Update - " << dt << std::endl;
}

// Manages the shutdown of the level
void Level1::Shutdown()
{
	std::cout << "Level1::Shutdown" << std::endl;
}