//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 6.1.6 ASSIGNMENT - Graphics
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files and Using Declarations:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Transform.h"
#include "GameObject.h"
#include "FileStream.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a new sprite object.
Sprite::Sprite(Mesh* mesh_, const SpriteSource* spriteSource_)
	: frameIndex(0), flipX(false), flipY(false), color(Colors::White),
	mesh(mesh_), spriteSource(spriteSource_), transform(nullptr), Component("Sprite")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* Sprite::Clone() const
{
	return new Sprite(*this);
}

// Initialize this component, grab pointers to other components from owner.
void Sprite::Initialize()
{
	transform = dynamic_cast<Transform*>(GetOwner()->GetComponent("Transform"));
}

// Draw a sprite (Sprite can be textured or untextured).
void Sprite::Draw()
{
	Draw(Vector2D(0, 0));
}

// Draw a sprite at an offset from the object's translation.
// Params:
//   offset = The offset that will be added to the translation when drawing.
void Sprite::Draw(const Beta::Vector2D& offset)
{
	if (mesh == nullptr || transform == nullptr)
		return;

	GraphicsEngine& graphics = *EngineGetModule(GraphicsEngine);
	graphics.GetSpriteShader().Use();
	graphics.SetSpriteBlendColor(color);

	if (spriteSource != nullptr)
		spriteSource->UseTexture(frameIndex, flipX, flipY);
	else
		graphics.GetDefaultTexture().Use();

	Matrix2D offset_ = Matrix2D::TranslationMatrix(offset.x, offset.y);
	offset_ *= reinterpret_cast<const Matrix2D&>(transform->GetMatrix());
	graphics.SetTransform(offset_);
	mesh->Draw();
}

// Set a sprite's transparency (between 0.0f and 1.0f).
// Params:
//   alpha = New value for the sprite's 'alpha' value.
void Sprite::SetAlpha(float alpha)
{
	color.a = alpha;
}

// Get the current value for a sprite's transparency.
float Sprite::GetAlpha() const
{
	return color.a;
}

// Set the sprite's current frame.
// Params:
//   frameIndex = New frame index for the sprite (0 .. frame count).
void Sprite::SetFrame(unsigned int frameIndex_)
{
	if (frameIndex_ < spriteSource->GetFrameCount())
		frameIndex = frameIndex_;
}

// Set the sprite's mesh.
// (NOTE: This mesh may be textured or untextured.)
// (NOTE: This mesh may contain any number of triangles.)
// Params:
//   mesh = Pointer to a mesh created using the Beta Framework.
void Sprite::SetMesh(Beta::Mesh* mesh_)
{
	mesh = mesh_;
}

// Set a new SpriteSource for the specified sprite.
// Params:
//	 spriteSource = A new sprite source for the sprite.
void Sprite::SetSpriteSource(const SpriteSource* spriteSource_)
{
	spriteSource = spriteSource_;
}

// Returns the current sprite source being used by the sprite.
const SpriteSource* Sprite::GetSpriteSource()
{
	return spriteSource;
}

// Set the blend color for the specified sprite.
// Params:
//	 color = A new color for the sprite.
void Sprite::SetColor(Color color_)
{
	color = color_;
}

// Retrieves the blend color for the sprite.
const Color& Sprite::GetColor() const
{
	return color;
}

// Set whether to flip the sprite horizontally when drawing
void Sprite::SetFlipX(bool flipX_)
{
	flipX = flipX_;
}

// Set whether to flip the sprite vertically when drawing
void Sprite::SetFlipY(bool flipY_)
{
	flipY = flipY_;
}

// Loads object data from a file.
// Params:
//   stream = The stream for the file we want to read from.
void Sprite::Deserialize(FileStream& stream)
{
	stream.ReadVariable("frameIndex", frameIndex);
	stream.ReadVariable("color", color);
}

// Saves object data to a file.
// Params:
//   stream = The stream for the file we want to write to.
void Sprite::Serialize(FileStream& stream) const
{
	stream.WriteVariable("frameIndex", frameIndex);
	stream.WriteVariable("color", color);
}