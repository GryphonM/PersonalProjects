// Level3.h
#pragma once

// Inheritance
#include "BetaObject.h"

// Forward declarations
namespace Beta
{
	class Mesh;
	class Texture;
}

// Class definition
class Level3 : public Beta::BetaObject
{
public:
	Level3();

	// Game Loop Functions
	void Initialize();
	void Update(float dt);
	void Shutdown();

private:
	Beta::Mesh* mesh;
	Beta::Texture* texture;

	// Animation data
	float timer;
	unsigned currentFrame;
	unsigned rows;
	unsigned columns;
	unsigned totalFrames;
};
