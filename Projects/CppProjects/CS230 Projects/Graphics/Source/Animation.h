//------------------------------------------------------------------------------
//
// File Name:	Animation.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class SpriteSource;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Animation
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Construct a new animation resource.
	// Params:
	//   name = The name of the animation.
	//   spriteSource = The sprite source used by this animation.
	//   frameCount = The number of frames in this animation.
	//   frameStart = The starting frame in the sprite source for this animation.
	//   duration = The time that each frame will be displayed.
	Animation(const std::string& name = "", const SpriteSource* spriteSource = nullptr,
		unsigned frameCount = 1, unsigned frameStart = 0, float frameDuration = 0.0f);

	// Return the total number of frames in the animation
	unsigned GetFrameCount() const;

	// Return the frame index that a sprite should use. This is based on the
	// sprite's current frame (given as a parameter), the animation's start frame, 
	// and the animation's frame count.
	// Params:
	//   frameIndex = The current frame in he animation, zero-based.
	// Returns:
	//   The frame in the sprite source for the current frame of the animation.
	unsigned GetActualFrameIndex(unsigned frameIndex) const;

	// Return the duration of the current frame.
	// Params:
	//   frameIndex = The current frame in he animation, zero-based.
	// Returns:
	//   The duration of the current frame in the animation.
	float GetActualFrameDuration(unsigned frameIndex) const;

	// Get the name of the animation.
	const std::string& GetName() const;

	// Get the sprite source used by this animation.
	const SpriteSource* GetSpriteSource() const;

private:
	// The amount of time to display each frame.
	float frameDuration;

	// Animation attributes
	unsigned frameCount;
	unsigned frameStart;

	// Name of animation
	std::string name;

	// Sprite source used for this animation.
	const SpriteSource* spriteSource;
};

//----------------------------------------------------------------------------
