// Level1.h
#pragma once

#include "BetaObject.h"

class Level1 : public Beta::BetaObject
{
public:
	Level1();

	// Initializes the level
	void Initialize();
	// Updates the level based on the time passed since the last interval
	void Update(float dt);
	// Manages the shutdown of the level
	void Shutdown();
};