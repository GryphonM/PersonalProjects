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
	translation(Beta::Vector2D(x, y)), rotation(0), scale(Beta::Vector2D(1,1)), isDirty(true)
{
}

// Transform constructor.
// Params:
//	 translation = World position of the object.
//   scale		 = Width and height of the object.
//   rotation	 = Rotation of the object about the z-axis.
Transform::Transform(Beta::Vector2D translation_, Beta::Vector2D scale_, float rotation_) : 
	translation(translation_), rotation(rotation_), scale(scale_), isDirty(true)
{
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
		CS230::Matrix2D Rotation = CS230::Matrix2D::RotationMatrixDegrees(rotation);

		matrix = Scale * Rotation * Translation;
		isDirty = false;
	}
	return matrix;
}

// Set the translation of a transform component.
// Params:
//	 translation = Reference to a translation vector.
void Transform::SetTranslation(const Beta::Vector2D& translation_)
{
	if (!(translation_.x == translation.x && translation_.y == translation.y))
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
	if (rotation != rotation_)
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
	if (!(scale_.x == scale.x && scale_.y == scale.y))
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