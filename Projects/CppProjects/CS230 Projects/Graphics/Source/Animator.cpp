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
#include "Animator.h"
#include "Animation.h"
#include "Sprite.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Construct a new animation controller object.
Animator::Animator(Sprite* sprite_)
	: animationIndex(0), playbackSpeed(1.f), 
	isRunning(false), isLooping(true), isDone(false), 
	currentFrameIndex(0), currentFrameDuration(0.f), timer(0.f),
	sprite(sprite_)
{
	/*for (int i = 0; i < 255; i++)
	{
		animationList[i] = new Animation();
	}*/
}

// Update the animation.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Animator::Update(float dt)
{
	std::cout << "Animator::Update" << std::endl;

	if (!isRunning)
		return;

	if (timer >= currentFrameDuration)
	{
		sprite->SetFrame(animationList[animationIndex]->GetActualFrameIndex(currentFrameIndex++));
		if (currentFrameIndex == animationList[animationIndex]->GetFrameCount())
		{
			if (!isLooping)
				isRunning = false;

			isDone = true;
			timer = 0;
			currentFrameIndex = 0;
		}
		else
			isDone = false;
	}
	else
	{
		timer += dt * playbackSpeed;
	}
}

// Play an animation.
// Params:
//   animationIndex = The index of the animation to play.
//	 playbackSpeed = The speed at which to play the animation.
//	 loop = Whether the animation should go back to the beginning after it reaches the end.
void Animator::Play(size_t animationIndex_, float playbackSpeed_, bool loop)
{
	std::cout << "Animator::Play" << std::endl;

	if (animationIndex_ >= animationList.Size())
		return;

	animationIndex = animationIndex_;
	playbackSpeed = playbackSpeed_;
	isLooping = loop;
	isRunning = true;

	const Animation* currentAnim = animationList[animationIndex_];

	if (currentAnim->GetSpriteSource() != nullptr)
		sprite->SetSpriteSource(currentAnim->GetSpriteSource());
	sprite->SetFrame(currentAnim->GetActualFrameIndex(currentFrameIndex++));
	currentFrameDuration = currentAnim->GetActualFrameDuration(0);
}

// Add an animation to the controller.
// Params:
//   animation = The animation resource that will be added to the controller.
// Returns:
//   The index of the animation in the controller, for use with the Play function.
size_t Animator::AddAnimation(const Animation* animation)
{
	animationList.PushBack(animation);
	for (int i = 0; i < 255; i++)
	{
		if (animationList[i]->GetName() == animation->GetName())
			return i;
	}
	
	return 255;
}

// Get the index of the currently playing animation, for use with the Play function.
size_t Animator::GetCurrentAnimationIndex() const
{
	return animationIndex;
}

// Get the index of the animation with the specified name
// Params:
//   name = The name of the animation for which the index was requested.
// Returns:
//   The index of the given animation if it was found, or 0.
size_t Animator::GetAnimationIndex(const std::string& name) const
{
	for (int i = 0; i < 255; i++)
	{
		if (animationList[i]->GetName() == name)
			return i;
	}

	return 0;
}

// Determine if the animation has reached the end of its sequence.
// Returns:
//	 True if the animation is done, false otherwise.
bool Animator::IsDone() const
{
	return isDone;
}

// Set the time to wait between frames for the currently playing animation.
// Params:
//	 duration = The amount of time to wait between frames (in seconds).
void Animator::SetPlaybackSpeed(float speed)
{
	playbackSpeed = speed;
}