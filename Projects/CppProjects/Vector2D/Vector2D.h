//------------------------------------------------------------------------------
//
// File Name:	Vector2D.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 6.3.6 ASSIGNMENT - Vector2D Class
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR2D_H
#define VECTOR2D_H
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // istream, ostream

namespace CS170
{
	class Vector2D
	{
	public:
		// Constructors (2)
		// Builds a Vector2D with the given values
		// Params:
		//   x = Value for X.
		//   y = Value for Y.
		// Return:
		//   This Vector2D Object
		Vector2D(float x, float y);
		// Builds a Vector2D with default values
		// Return:
		//   This Vector2D Object
		Vector2D();
		
		// Accessors (2)
		// Returns the value of x.
		float X() const;
		// Returns the value of x.
		float Y() const;
		
		
		// Mutators (2)
		// Changes the value of x to the given value
		// Params:
		//   newVal = The new value for X.
		void X(const float newVal);
		// Changes the value of y to the given value
		// Params:
		//   newVal = The new value for Y.
		void Y(const float newVal);
		
		
		// Other functions (7)
		// Evaluates the squared magnitude of the vector.
		// Return:
		//   The squared Magnitude in a float
		float MagnitudeSquared() const;

		// Evaluates the magnitude of the vector.
		// Return:
		//   The Magnitude in a float
		float Magnitude() const;

		// Evaluates the normalized value of the vector.
		// Return:
		//   The normalized values
		Vector2D Normalized() const;

		// Determines the squared distance between this vector and another vector
		// Params:
		//   other = The other vector to determine the squared distance between.
		// Return:
		//   The squared distance in a float
		float DistanceSquared(const Vector2D& other) const;

		// Determines distance between this vector and another vector
		// Params:
		//   other = The other vector to determine the distance between.
		// Return:
		//   The distance in a float
		float Distance(const Vector2D& other) const;

		// Determines midpoint between two Vectors
		// Params:
		//   other = The other vector to determine the midpoint between.
		// Return:
		//   The mipoint in a Vector
		Vector2D Midpoint(const Vector2D& other) const;

		// Determines the dot product of this vector and a given vector
		// Params:
		//   other = The other vector to determine the midpoint between.
		// Return:
		//   The dot product in a float
		float DotProduct(const Vector2D& other) const;

		// Overloaded operators (9 member functions)
		// Overloads the + operator to add two vectors
		// Params:
		//   other = The other vector to add.
		// Return:
		//   A vector with the added values
		Vector2D operator+(const Vector2D& other) const;

		// Overloads the - operator to subtract two vectors
		// Params:
		//   other = The other vector to subtract.
		// Return:
		//   A vector with the subtracted values
		Vector2D operator-(const Vector2D& other) const;

		// Overloads the * operator to mulitply this value by a scalar
		// Params:
		//   other = The scalar.
		// Return:
		//   A vector with the scaled values
		Vector2D operator*(const float other) const;

		// Overloads the / operator to divide this vector by a number
		// Params:
		//   other = The value to divide the vector by.
		// Return:
		//   A vector with the divided values
		Vector2D operator/(const float other) const;

		// Overloads the += operator to add two vectors and assign the result to this vector
		// Params:
		//   other = The other vector to add.
		// Return:
		//   A pointer to this vector with the changed values
		Vector2D& operator+=(const Vector2D& other);

		// Overloads the -= operator to subtract two vectors and assign the result to this vector
		// Params:
		//   other = The other vector to subtract.
		// Return:
		//   A pointer to this vector with the changed values
		Vector2D& operator-=(const Vector2D& other);

		// Overloads the *= operator to multiply this vector by a scalar and assign it to this vector
		// Params:
		//   other = The scalar.
		// Return:
		//   A pointer to this vector with the changed values
		Vector2D& operator*=(const float other);

		// Overloads the /= operator to divide this vector by a number and assign it to this vector
		// Params:
		//   other = The number to divide this vector by.
		// Return:
		//   A pointer to this vector with the changed values
		Vector2D& operator/=(const float other);

		// Overloads the - operator to convert this vector to the negative.
		// Return:
		//   A Vector with the negated values
		Vector2D operator-() const;
		
		
	private:
		float x; // The x-coordinate of a Vector2D
		float y; // The y-coordinate of a Vector2D
	};
  
	// Overloaded operators (2 non-member, non-friend functions)
	// Overloads the << operator to print out the vector
	// Params:
	//   os = the stream to output the output to.
	//   output = the vector to be printed.
	// Return:
	//   the stream with the value to be printed
	std::ostream& operator<<(std::ostream& os, const Vector2D& output);

	// Overloads the * operator to multiply a float by a vector
	// Params:
	//   other = the scalar.
	//   vector2D = the vector to be scaled.
	// Return:
	//   The result of the inverse operation (i.e. Vector2D * other).
	Vector2D operator*(float other, const Vector2D& vector2D);
	

} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
