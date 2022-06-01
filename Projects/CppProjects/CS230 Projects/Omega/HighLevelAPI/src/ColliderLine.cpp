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
		Beta::Vector2D midpoint = 0.5f * (truePos.end + truePos.start);
		Beta::Vector2D shortNormal = 0.2f * truePos.normal;
		Beta::Vector2D endNormal = midpoint + shortNormal;
		debugDraw.AddLineToList(midpoint, endNormal, Beta::Colors::Red);
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
	if (other.GetType() != ColliderType::Point && other.GetType() != ColliderType::Circle)
		return false;
	if (other.GetOwner()->GetComponent<RigidBody>() == nullptr || other.GetOwner()->GetComponent<Transform>() == nullptr)
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
			Transform* transform = other.GetOwner()->GetComponent<Transform>();
			RigidBody* rigidBody = other.GetOwner()->GetComponent<RigidBody>();
			MovingPointLineReflection(*transform, *rigidBody, truePos, otherMove, intersection);
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
	for (auto it = lineSegments.begin(); it != lineSegments.end(); it++)
	{
		file.WriteValue('{ ');
		file.WriteValue(*it);
		file.WriteValue(' }');
	}
}

// Load object data from file
// Params:
//   file = The file stream used to load the object's data.
void ColliderLine::Deserialize(FileStream& file)
{
	int lineCount;
	file.ReadVariable("lineCount", lineCount);
	file.ReadSkip("lines");
	file.ReadSkip(':');
	file.ReadSkip('{');
	for (int i = 0; i < lineCount; i++)
	{
		Beta::LineSegment line;
		file.ReadValue(line);
		lineSegments.push_back(line);
	}
	file.ReadSkip('}');
}

// Gets a line segment that incorporates the transform of the object
// Params:
//   index = The index of the line within the array of line segments.
Beta::LineSegment ColliderLine::GetLineWithTransform(unsigned index) const
{
	Beta::Vector2D pos = GetOwner()->GetComponent<Transform>()->GetTranslation();
	Beta::Vector2D scale = GetOwner()->GetComponent<Transform>()->GetScale();
	Beta::Vector2D p0 = Beta::Vector2D(lineSegments[index].start.x * scale.x, lineSegments[index].start.y * scale.y) + pos;
	Beta::Vector2D p1 = Beta::Vector2D(lineSegments[index].end.x * scale.x, lineSegments[index].end.y * scale.y) + pos;
	return Beta::LineSegment(p0, p1);
}