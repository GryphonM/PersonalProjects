//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 8.2.4 Assignment: Collision Detection
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "ColliderLine.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "Transform.h"
#include "FileStream.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a new (line) collider component.
ColliderLine::ColliderLine(bool reflection_) : Collider(ColliderType::Lines), reflection(reflection_)
{
}

// Clone an collider and return a pointer to the cloned object.
// Returns:
//   A pointer to a collider.
Component* ColliderLine::Clone() const
{
	return new ColliderLine(*this);
}

// Debug drawing for colliders.
void ColliderLine::Draw()
{
	Beta::DebugDraw& debugDraw = *Beta::EngineCore::GetInstance().GetModule<Beta::DebugDraw>();

	for (auto it = lineSegments.begin(); it != lineSegments.end(); it++)
	{
		Beta::LineSegment truePos = GetLineWithTransform(it - lineSegments.begin());
		debugDraw.AddLineToList(truePos.start, truePos.end, Beta::Colors::Green);
		Beta::Vector2D midpoint = 0.5f * (truePos.start - truePos.end);
		debugDraw.AddLineToList(midpoint, 0.2f * (midpoint + truePos.normal), Beta::Colors::Red);
	}
	
	debugDraw.EndLineList();
}

// Add a line segment to the line collider's line segment list.
// Params:
//	 collider = Pointer to the line collider component.
//	 p0 = The line segment's starting position.
//	 p1 = The line segment's ending position.
void ColliderLine::AddLineSegment(const Beta::Vector2D& p0, const Beta::Vector2D& p1)
{
	lineSegments.push_back(Beta::LineSegment(p0, p1));
}

// Check for collision between a line collider and another arbitrary collider.
// Params:
//	 other = Reference to the other collider component.
// Returns:
//	 Return the results of the collision check.
bool ColliderLine::IsCollidingWith(const Collider& other) const
{
	if (other.GetType() != ColliderType::Point)
		return false;

	Beta::LineSegment otherMove = Beta::LineSegment(other.GetOwner()->GetComponent<RigidBody>()->GetOldTranslation(), 
		other.GetOwner()->GetComponent<Transform>()->GetTranslation());

	for (auto it = lineSegments.begin(); it != lineSegments.end(); it++)
	{
		Beta::LineSegment truePos = GetLineWithTransform(it - lineSegments.begin());
		Beta::Vector2D intersection;
		float timeToIntersection;
		if (MovingPointLineIntersection(truePos, otherMove, intersection, timeToIntersection))
		{
			MovingPointLineReflection(other.GetOwner()->GetComponent<Transform>(), other.GetOwner()->GetComponent<RigidBody>(), truePos, otherMove, intersection);
			return true;
		}
	}
	return false;
}

// Save object data to file.
// Params:
//   file = The file stream to save the object's data.
void ColliderLine::Serialize(FileStream& file) const
{
	file.WriteVariable("lineCount", lineSegments.size());
	file.WriteVariable("lines", lineSegments);
}

// Load object data from file
// Params:
//   file = The file stream used to load the object's data.
void ColliderLine::Deserialize(FileStream& file)
{
	file.ReadVariable("lines", lineSegments);
}

// Gets a line segment that incorporates the transform of the object
// Params:
//   index = The index of the line within the array of line segments.
Beta::LineSegment ColliderLine::GetLineWithTransform(unsigned index) const
{
	Beta::Vector2D pos = GetOwner()->GetComponent<Transform>()->GetTranslation();
	return Beta::LineSegment(lineSegments[index].start + pos, lineSegments[index].end + pos);
}