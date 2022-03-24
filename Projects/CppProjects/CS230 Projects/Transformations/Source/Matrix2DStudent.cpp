//------------------------------------------------------------------------------
//
// File Name:	Matrix2DStudnet.cpp
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
#include "Matrix2DStudent.h"

namespace CS230
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for matrix. Sets all data in matrix to 0.
	Matrix2D::Matrix2D()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				m[i][j] = 0;
		}
	}

	// This function creates an identity matrix and returns it.
	Matrix2D Matrix2D::IdentityMatrix()
	{
		Matrix2D I;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i == j)
					I.m[i][j] = 1;
			}
		}
		return I;
	}

	// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
		// (NOTE: Care must be taken when pResult = pMtx.)
	Matrix2D Matrix2D::Transposed() const
	{
		Matrix2D T = *this;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				T.m[i][j] = m[j][i];
			}
		}
		return T;
	}

	// This function creates a translation matrix from x & y and returns it.
	Matrix2D Matrix2D::TranslationMatrix(float x, float y)
	{
		Matrix2D T;
		T.m[0][2] = x;
		T.m[1][2] = y;
		T.m[2][2] = 1;
		return T;
	}

	// This function creates a scaling matrix from x & y and returns it.
	Matrix2D Matrix2D::ScalingMatrix(float x, float y)
	{
		Matrix2D S;
		S.m[0][0] = x;
		S.m[1][1] = y; 
		S.m[2][2] = 1;
		return S;
	}

	// This matrix creates a rotation matrix from "Angle" whose value is in radians.
	// Return the resulting matrix.
	Matrix2D Matrix2D::RotationMatrixRadians(float angle)
	{
		Matrix2D R;
		R.m[0][0] = cos(angle);
		R.m[0][1] = -sin(angle);
		R.m[1][0] = sin(angle);
		R.m[1][1] = cos(angle);
		return R;
	}

	// This matrix creates a rotation matrix from "Angle" whose value is in degrees.
	// Return the resulting matrix.
	// Converting from degrees to radians can be performed as follows:
	//	 radians = (angle * M_PI) / 180.0f
	Matrix2D Matrix2D::RotationMatrixDegrees(float angle)
	{
		return RotationMatrixRadians((angle * M_PI) / 180.0f);
	}

	// This function multiplies the current matrix with another and returns the result as a new matrix.
	// HINT: Use the RowColumnMultiply function to help write this function.
	Matrix2D Matrix2D::operator*(const Matrix2D& other) const
	{
		Matrix2D result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				result.m[i][j] = RowColumnMultiply(other, i, j);
		}
		return result;
	}

	// This function multiplies the current matrix with another, storing the result in the current matrix.
	// HINT: Use the RowColumnMultiply function to help write this function.
	Matrix2D& Matrix2D::operator*=(const Matrix2D& other)
	{
		Matrix2D result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				result.m[i][j] = RowColumnMultiply(other, i, j);
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				m[i][j] = result.m[i][j];
		}
		return *this;
	}

	// This function multiplies a matrix with a vector and returns the result as a new vector.
	// Result = Mtx * Vec.
	Beta::Vector2D Matrix2D::operator*(const Beta::Vector2D& vec) const
	{
		
	}

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Multiplies a row of the current matrix by a column in another and returns the result.
	float Matrix2D::RowColumnMultiply(const Matrix2D& other, unsigned row, unsigned col) const
	{
		float result = 0;
		for (int i = 0; i < 3; i++)
			result += m[row][i] * other.m[i][col];
		return result;
	}
}