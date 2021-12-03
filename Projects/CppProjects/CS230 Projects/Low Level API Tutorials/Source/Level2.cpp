// Level2.cpp
#include "stdafx.h"
#include "Level2.h"

using namespace Beta;

Level2::Level2()
	: BetaObject("Level2"), mesh(nullptr)
{
}

void Level2::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;

	// Obtain mesh factory module
	MeshFactory& meshFactory = *EngineGetModule(MeshFactory);

	// Create the mesh
	
	// Add a green triangle
	meshFactory.AddTriangle(Vector2D(-0.5f, -1.0f),
		Vector2D(-1.0f, 0.0f), Vector2D(-0.5f, 1.0f), Colors::Green);
	meshFactory.AddTriangle(Vector2D(-0.5f, -1.0f),
		Vector2D(0.5f, 1.0f), Vector2D(0.5f, -1.0f), Colors::Green);
	meshFactory.AddTriangle(Vector2D(-0.5f, -1.0f),
		Vector2D(-0.5f, 1.0f), Vector2D(0.5f, 1.0f), Colors::Green);
	meshFactory.AddTriangle(Vector2D(0.5f, -1.0f),
		Vector2D(0.5f, 1.0f), Vector2D(1.0f, 0.0f), Colors::Green);

	// End mesh creation
	mesh = meshFactory.EndCreate();
}

void Level2::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Set the background color to white
	GraphicsEngine& graphics = *EngineGetModule(GraphicsEngine);
	graphics.SetBackgroundColor(Colors::White);

	// Set the position and scale to use when drawing
	graphics.SetTransform(Vector2D(0.0f, 0.0f), Vector2D(1.f, 1.f));
	graphics.GetDefaultTexture().Use();

	// Draw the mesh
	mesh->Draw();
}

void Level2::Shutdown()
{
	std::cout << "Level2::Shutdown" << std::endl;

	// Delete the mesh
	delete mesh;
}