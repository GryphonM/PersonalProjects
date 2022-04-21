//------------------------------------------------------------------------------
//
// File Name:	Animator.h
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

#include "Component.h" // inheritance

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Sprite;
class Animation;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Animator : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Construct a new animation controller object.
	Animator();

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* Clone() const override;

	// Initialize this component, grab pointers to other components from owner.
	void Initialize() override;

	// Update the animation.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt);

	// Play an animation.
	// Params:
	//   animationIndex = The index of the animation to play.
	//	 playbackSpeed = The speed at which to play the animation.
	//	 loop = Whether the animation should go back to the beginning after it reaches the end.
	void Play(size_t animationIndex = 0, float playbackSpeed = 1.0f, bool loop = true);

	// Add an animation to the controller.
	// Params:
	//   animation = The animation resource that will be added to the controller.
	// Returns:
	//   The index of the animation in the controller, for use with the Play function.
	size_t AddAnimation(const Animation* animation);

	// Get the index of the currently playing animation, for use with the Play function.
	size_t GetCurrentAnimationIndex() const;

	// Get the index of the animation with the specified name
	// Params:
	//   name = The name of the animation for which the index was requested.
	// Returns:
	//   The index of the given animation if it was found, or 0.
	size_t GetAnimationIndex(const std::string& name) const;

	// Determine if the animation has reached the end of its sequence.
	// Returns:
	//	 True if the animation is done, false otherwise.
	bool IsDone() const;

	// Set the time to wait between frames for the currently playing animation.
	// Params:
	//	 duration = The amount of time to wait between frames (in seconds).
	void SetPlaybackSpeed(float speed);

private:
	// The current animation being played.
	size_t animationIndex;

	// How fast animations will play.
	float playbackSpeed;

	// True if the animation is running; false if the animation has stopped.
	bool isRunning;

	// True if the animation loops back to the beginning.
	bool isLooping;

	// True if the end of the animation has been reached, false otherwise.
	bool isDone;

	// Current animation position and frame duration
	unsigned currentFrameIndex;
	float currentFrameDuration;

	// Accumulates time so we know when to change frames
	float timer;

	// Components
	Sprite* sprite;

	// List of animations used by this controller
	Beta::Array<const Animation*> animationList;
};

//----------------------------------------------------------------------------
