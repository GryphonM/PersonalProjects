//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright ? 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Collider.h"
#include "Intersection2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

const int cLineSegmentMax = 10;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ColliderLine : public Collider
{
public:
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new (line) collider component.
	ColliderLine(bool reflection = true);

	// Clone an collider and return a pointer to the cloned object.
	// Returns:
	//   A pointer to a collider.
	Component* Clone() const;

	// Debug drawing for colliders.
	void Draw() override;

	// Add a line segment to the line collider's line segment list.
	// Params:
	//	 collider = Pointer to the line collider component.
	//	 p0 = The line segment's starting position.
	//	 p1 = The line segment's ending position.
	void AddLineSegment(const Beta::Vector2D& p0, const Beta::Vector2D& p1);

	// Check for collision between a line collider and another arbitrary collider.
	// Params:
	//	 other = Reference to the other collider component.
	// Returns:
	//	 Return the results of the collision check.
	bool IsCollidingWith(const Collider& other) const override;

	// Save object data to file.
	// Params:
	//   file = The file stream to save the object's data.
	void Serialize(FileStream& file) const;

	// Load object data from file
	// Params:
	//   file = The file stream used to load the object's data.
	void Deserialize(FileStream& file);

	// Gets a line segment that incorporates the transform of the object
	// Params:
	//   index = The index of the line within the array of line segments.
	Beta::LineSegment GetLineWithTransform(unsigned index) const;

private:

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The individual line segments.
	std::vector<Beta::LineSegment> lineSegments;

	// Should the collider perform reflection
	bool reflection;
};

//------------------------------------------------------------------------------
