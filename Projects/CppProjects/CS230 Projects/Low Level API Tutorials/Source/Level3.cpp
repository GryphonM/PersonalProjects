// Level3.cpp
#include "stdafx.h"
#include "Level3.h"

using namespace Beta;

Level3::Level3()
	: BetaObject("Level2"), mesh(nullptr), texture(nullptr),
	timer(0.0f), currentFrame(0), rows(4), columns(2), totalFrames(rows * columns)
{
}

void Level3::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;

	// Create four vertices
	Vertex topLeft = Vertex(Vector2D(-0.5f, 0.5f), Vector2D(0.0f, 0.0f));
	Vertex topRight = Vertex(Vector2D(0.5f, 0.5f), Vector2D(1.0f / columns, 0.0f));
	Vertex bottomRight = Vertex(Vector2D(0.5f, -0.5f), Vector2D(1.0f / columns, 1.0f / rows));
	Vertex bottomLeft = Vertex(Vector2D(-0.5f, -0.5f), Vector2D(0.0f, 1.0f / rows));

	// Create a mesh from two triangles that share
	// the top left and bottom right vertices
	MeshFactory& meshFactory = *EngineGetModule(MeshFactory);
	meshFactory.AddTriangle(topLeft, topRight, bottomRight);
	meshFactory.AddTriangle(topLeft, bottomLeft, bottomRight);
	mesh = meshFactory.EndCreate();

	// Load the cat texture
	texture = Texture::CreateTextureFromFile("runningcat.png");
}

void Level3::Update(float dt)
{
	// Set the background color to white
	GraphicsEngine& graphics = *EngineGetModule(GraphicsEngine);
	graphics.SetBackgroundColor(Colors::White);

	// Set the position and scale to use when drawing
	graphics.SetTransform(Vector2D(0.0f, 0.0f), Vector2D(3.f, 3.f));
	graphics.GetDefaultTexture().Use();

	// Calculate frame and UV offset
	float animationTime = 0.05f;
	timer += dt;
	if (timer > animationTime)
	{
		timer = 0.0f;
		currentFrame = (currentFrame + 1) % totalFrames;
	}
	unsigned currentColumn = currentFrame % columns;
	unsigned currentRow = currentFrame / columns;

	// Use the animated texture with correct UV offset
	texture->Use(Vector2D((float)currentColumn / columns, (float)currentRow / rows));
	
	// Draw the mesh
	mesh->Draw();
}

void Level3::Shutdown()
{
	std::cout << "Level2::Shutdown" << std::endl;

	// Delete assets
	delete mesh;
	delete texture;
}