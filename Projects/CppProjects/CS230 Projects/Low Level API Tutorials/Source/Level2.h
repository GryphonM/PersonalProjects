// Level2.h
#pragma once

// Includes
#include "BetaObject.h"

// Forward declaration
namespace Beta
{
	class Mesh;
}

// Class definition
class Level2 : public Beta::BetaObject
{
public:
	Level2();

	// Game Loop Functions
	void Initialize();
	void Update(float dt);
	void Shutdown();

private:
	Beta::Mesh* mesh;
};