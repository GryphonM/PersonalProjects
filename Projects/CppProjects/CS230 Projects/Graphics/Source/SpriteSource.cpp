//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
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
#include "SpriteSource.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor for SpriteSource
	// Params:
	//   texture = The texture that contains the frames that this sprite source will use.
	//   name = The name to use for this sprite source.
	//	  numCols = The number of total columns in the sprite sheet texture.
	//	  numRows = The number of total rows in the sprite sheet texture.
SpriteSource::SpriteSource(const Texture* texture_, std::string name_,
	unsigned numCols_, unsigned numRows_) : numRows(numRows_), numCols(numCols_), 
	texture(texture_), name(name_)
{
}

// Activates the sprite source's texture and sets its UV offset based on the given frame index.
// Params:
//   frameIndex = The index of the frame of the texture that we want to use.
//   flipX		= Whether to flip the sprite horizontally when rendering.
//   flipY	    = Whether to flip the sprite vertically when rendering.
void SpriteSource::UseTexture(unsigned frameIndex, bool flipX, bool flipY) const
{
	Vector2D UVOffset = GetUV(frameIndex);
	texture->Use(1, 1, flipX, flipY, UVOffset);
}

// Returns the maximum number of possible frames in the sprite source's texture (rows * cols).
unsigned SpriteSource::GetFrameCount() const
{
	return numCols * numRows;
}

// Gets the name of the sprite source.
const std::string& SpriteSource::GetName() const
{
	return name;
}

// Gets the dimensions of the texture (number of columns, rows)
const Vector2D SpriteSource::GetTextureDimensions() const
{
	return Vector2D(static_cast<float>(numCols), static_cast<float>(numRows));
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
// Returns the UV coordinates of the specified frame in a sprite sheet.
	// Params:
	//	 frameIndex = A frame index within a sprite sheet.
	// Returns:
	//   A vector containing the UV/texture coordinates.
const Vector2D SpriteSource::GetUV(unsigned int frameIndex) const
{
	float USize = 1.f / numCols;
	float VSize = 1.f / numRows;

	unsigned column = frameIndex % numCols;
	unsigned row = frameIndex / numRows;

	return Vector2D(USize * column, VSize * row);
}