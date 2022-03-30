//------------------------------------------------------------------------------
//
// File Name:	Transform.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 7.0.7 Assignment: Transformations
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
// Transform constructor.
// Params:
//	 x = Initial world position on the x-axis.
//	 y = Initial world position on the y-axis.
Transform::Transform(float x, float y) : 
	translation(Beta::Vector2D(x, y)), rotation(0), scale(Beta::Vector2D(1,1)), isDirty(true), Component("Transform")
{
}

// Transform constructor.
// Params:
//	 translation = World position of the object.
//   scale		 = Width and height of the object.
//   rotation	 = Rotation of the object about the z-axis.
Transform::Transform(Beta::Vector2D translation_, Beta::Vector2D scale_, float rotation_) : 
	translation(translation_), rotation(rotation_), scale(scale_), isDirty(true), Component("Transform")
{
}

// Clone a component and return a pointer to the cloned component.
// Returns:
//   A pointer to a dynamically allocated clone of the component.
Component* Transform::Clone() const
{
	Transform* clone = new Transform(*this);
	return clone;
}

// Get the transform matrix, based upon translation, rotation and scale settings.
// Returns:
//	 A reference to the component's matrix structure
const CS230::Matrix2D& Transform::GetMatrix() const
{
	if (isDirty)
	{
		CS230::Matrix2D Translation = CS230::Matrix2D::TranslationMatrix(translation.x, translation.y);
		CS230::Matrix2D Scale = CS230::Matrix2D::ScalingMatrix(scale.x, scale.y);
		CS230::Matrix2D Rotation = CS230::Matrix2D::RotationMatrixRadians(rotation);

		matrix = Translation * Rotation * Scale;
		isDirty = false;
	}
	return matrix;
}

// Set the translation of a transform component.
// Params:
//	 translation = Reference to a translation vector.
void Transform::SetTranslation(const Beta::Vector2D& translation_)
{
	if (!Beta::AlmostEqual(translation, translation_))
	{
		translation.x = translation_.x;
		translation.y = translation_.y;
		isDirty = true;
	}
}

// Get the translation of a transform component.
// Returns:
//	 A reference to the component's translation structure.
const Beta::Vector2D& Transform::GetTranslation() const
{
	return translation;
}

// Set the rotation of a transform component.
// Params:
//	 rotation = The rotation value (in radians).
void Transform::SetRotation(float rotation_)
{
	if (!Beta::AlmostEqual(rotation, rotation_))
	{
		rotation = rotation_;
		isDirty = true;
	}
}

// Get the rotation value of a transform component.
// Returns:
//	 The component's rotation value (in radians).
float Transform::GetRotation() const
{
	return rotation;
}

// Set the scale of a transform component.
// Params:
//	 translation = Reference to a scale vector.
void Transform::SetScale(const Beta::Vector2D& scale_)
{
	if (!Beta::AlmostEqual(scale, scale_))
	{
		scale.x = scale_.x;
		scale.y = scale_.y;
		isDirty = true;
	}
}

// Get the scale of a transform component.
// Returns:
//	 A reference to the component's scale structure.
const Beta::Vector2D& Transform::GetScale() const
{
	return scale;
}