//------------------------------------------------------------------------------
//
// File Name:	SpriteTilemap.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 8.0.1 Assignment: Tilemaps
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "SpriteTilemap.h"
#include "Tilemap.h"
#include "GameObject.h"
#include "Transform.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a new sprite for use with a tilemap.
SpriteTilemap::SpriteTilemap(Beta::Mesh* mesh_, const SpriteSource* spriteSource_, const Tilemap* map_) : 
	Sprite(mesh_, spriteSource_), map(map_)
{
}

// Clone the sprite, returning a dynamically allocated copy.
Component* SpriteTilemap::Clone() const
{
	return new SpriteTilemap(*this);
}

// Draw a sprite (Sprite can be textured or untextured).
void SpriteTilemap::Draw()
{
	unsigned rows = map->GetHeight();
	unsigned columns = map->GetWidth();
	Vector2D scale = GetOwner()->GetComponent<Transform>()->GetScale();
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
		{
			int cellVal = map->GetCellValue(j, i);
			if (cellVal != 0)
			{
				SetFrame(cellVal - 1);
				Sprite::Draw(Vector2D(j * scale.x, i * -scale.y));
			}
		}
	}
}

// Sets the tilemap data that will be used by the sprite.
// Params:
//   map = A pointer to the tilemap resource.
void SpriteTilemap::SetTilemap(const Tilemap* map_)
{
	map = map_;
}