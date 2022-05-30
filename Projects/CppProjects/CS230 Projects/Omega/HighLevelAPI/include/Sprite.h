//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <Color.h>		// Beta::Color
#include "Component.h"	// inheritance

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

namespace Beta
{
	class Mesh;
	class Vector2D;
}

class SpriteSource;
class Transform;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class Sprite : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new sprite object.
	Sprite(Beta::Mesh* mesh_ = nullptr, const SpriteSource* spriteSource_ = nullptr);

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Clone() const override;

	// Initialize this component, grab pointers to other components from owner.
	void Initialize() override;

	// Draw a sprite (Sprite can be textured or untextured).
	void Draw() override;

	// Draw a sprite at an offset from the object's translation.
	// Params:
	//   offset = The offset that will be added to the translation when drawing.
	void Draw(const Beta::Vector2D& offset);

	// Set a sprite's transparency (between 0.0f and 1.0f).
	// Params:
	//   alpha = New value for the sprite's 'alpha' value.
	void SetAlpha(float alpha);

	// Get the current value for a sprite's transparency.
	float GetAlpha() const;

	// Set the sprite's current frame.
	// Params:
	//   frameIndex = New frame index for the sprite (0 .. frame count).
	void SetFrame(unsigned int frameIndex);

	// Set the sprite's mesh.
	// (NOTE: This mesh may be textured or untextured.)
	// (NOTE: This mesh may contain any number of triangles.)
	// Params:
	//   mesh = Pointer to a mesh created using the Beta Framework.
	void SetMesh(Beta::Mesh* mesh);

	// Set a new SpriteSource for the specified sprite.
	// Params:
	//	 spriteSource = A new sprite source for the sprite.
	void SetSpriteSource(const SpriteSource* spriteSource);

	// Returns the current sprite source being used by the sprite.
	const SpriteSource* GetSpriteSource();

	// Set the blend color for the specified sprite.
	// Params:
	//	 color = A new color for the sprite.
	void SetColor(Beta::Color color);

	// Retrieves the blend color for the sprite.
	const Beta::Color& GetColor() const;

	// Set whether to flip the sprite horizontally when drawing
	void SetFlipX(bool flipX);

	// Set whether to flip the sprite vertically when drawing
	void SetFlipY(bool flipY);

	// Loads object data from a file.
	// Params:
	//   stream = The stream for the file we want to read from.
	virtual void Deserialize(FileStream& stream) override;

	// Saves object data to a file.
	// Params:
	//   stream = The stream for the file we want to write to.
	virtual void Serialize(FileStream& stream) const override;

protected:
	//------------------------------------------------------------------------------
	// Protected Variables:
	//------------------------------------------------------------------------------

	// Other components
	const Transform* transform;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The sprite source used when drawing (simple colored mesh will have no sprite source).
	const SpriteSource* spriteSource;

	// The mesh used to draw the sprite.
	Beta::Mesh* mesh;

	// Color used for blending/tint
	Beta::Color color;

	// Mirroring
	bool flipX;
	bool flipY;
};


//------------------------------------------------------------------------------
