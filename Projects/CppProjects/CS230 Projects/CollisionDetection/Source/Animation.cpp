//------------------------------------------------------------------------------
//
// File Name:	Animator.cpp
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
#include "Animation.h"

using namespace Beta;

//------------------------------------------------------------------------------

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
Animation::Animation(const std::string& name_, const SpriteSource* spriteSource_,
	unsigned frameCount_, unsigned frameStart_, float frameDuration_)
	: name(name_), spriteSource(spriteSource_), 
	frameCount(frameCount_), frameStart(frameStart_), frameDuration(frameDuration_)
{
}

// Return the total number of frames in the animation
unsigned Animation::GetFrameCount() const
{
	return frameCount;
}

// Return the frame index that a sprite should use. This is based on the
// sprite's current frame (given as a parameter), the animation's start frame, 
// and the animation's frame count.
// Params:
//   frameIndex = The current frame in he animation, zero-based.
// Returns:
//   The frame in the sprite source for the current frame of the animation.
unsigned Animation::GetActualFrameIndex(unsigned frameIndex) const
{
	return (frameStart + frameIndex) % frameCount;
}

// Return the duration of the current frame.
// Params:
//   frameIndex = The current frame in he animation, zero-based.
// Returns:
//   The duration of the current frame in the animation.
float Animation::GetActualFrameDuration(unsigned frameIndex) const
{
	// Will use parameter when changing time between frames
	UNREFERENCED_PARAMETER(frameIndex);

	return frameDuration;
}

// Get the name of the animation.
const std::string& Animation::GetName() const
{
	return name;
}

// Get the sprite source used by this animation.
const SpriteSource* Animation::GetSpriteSource() const
{
	return spriteSource;
}