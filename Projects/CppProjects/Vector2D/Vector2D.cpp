//------------------------------------------------------------------------------
//
// File Name:	Vector2D.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 6.3.6 ASSIGNMENT - Vector2D Class
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "Vector2D.h"  // Vector2D members
#include <cmath>    // sqrt, atan, sin, cos

namespace CS170
{

///////////////////////////////////////////////////////////////////////////////
// 22 public member functions (2 constructors, 2 accessors, 2 mutators, 7 others, 9 operators) 

// Constructors (2)
// Builds a Vector2D with the given values
// Params:
//   x = Value for X.
//   y = Value for Y.
// Return:
//   This Vector2D Object
Vector2D::Vector2D(float x_, float y_)
  : x(x_), y(y_)
{
}

// Builds a Vector2D with default values
// Return:
//   This Vector2D Object
Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

// Accessors (2)
// Returns the value of x.
float Vector2D::X() const
{
    return x;
}

// Returns the value of x.
float Vector2D::Y() const
{
    return y;
}


// Mutators (2)
// Changes the value of x to the given value
// Params:
//   newVal = The new value for X.
void Vector2D::X(const float newVal)
{
    x = newVal;
}

// Changes the value of y to the given value
// Params:
//   newVal = The new value for Y.
void Vector2D::Y(const float newVal)
{
    y = newVal;
}


// Other functions (7)
// Evaluates the squared magnitude of the vector.
// Return:
//   The squared Magnitude in a float
float Vector2D::MagnitudeSquared() const
{
    return (x * x) + (y * y);
}

// Evaluates the magnitude of the vector.
// Return:
//   The Magnitude in a float
float Vector2D::Magnitude() const
{
    return sqrt(MagnitudeSquared());
}

// Evaluates the normalized value of the vector.
// Return:
//   The normalized values
Vector2D Vector2D::Normalized() const
{
    return *this * (1 / Magnitude());
}

// Determines the squared distance between this vector and another vector
// Params:
//   other = The other vector to determine the squared distance between.
// Return:
//   The squared distance in a float
float Vector2D::DistanceSquared(const Vector2D& other) const
{
    Vector2D delta = *this - other;

    return (delta.x * delta.x) + (delta.y * delta.y);
}

// Determines distance between this vector and another vector
// Params:
//   other = The other vector to determine the distance between.
// Return:
//   The distance in a float
float Vector2D::Distance(const Vector2D& other) const
{
    return sqrt(DistanceSquared(other));
}

// Determines midpoint between two Vectors
// Params:
//   other = The other vector to determine the midpoint between.
// Return:
//   The mipoint in a Vector
Vector2D Vector2D::Midpoint(const Vector2D& other) const
{
    return 0.5 * (*this + other);
}

// Determines the dot product of this vector and a given vector
// Params:
//   other = The other vector to determine the midpoint between.
// Return:
//   The dot product in a float
float Vector2D::DotProduct(const Vector2D& other) const
{
    return (x * other.x) + (y * other.y);
}


// Operators (9)
// Overloads the + operator to add two vectors
// Params:
//   other = The other vector to add.
// Return:
//   A vector with the added values
Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D(x + other.x, y + other.y);
}

// Overloads the - operator to subtract two vectors
// Params:
//   other = The other vector to subtract.
// Return:
//   A vector with the subtracted values
Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return Vector2D(x - other.x, y - other.y);
}

// Overloads the * operator to mulitply this value by a scalar
// Params:
//   other = The scalar.
// Return:
//   A vector with the scaled values
Vector2D Vector2D::operator*(const float other) const
{
    return Vector2D(x * other, y * other);
}

// Overloads the / operator to divide this vector by a number
// Params:
//   other = The value to divide the vector by.
// Return:
//   A vector with the divided values
Vector2D Vector2D::operator/(const float other) const
{
    return Vector2D(x / other, y / other);
}

// Overloads the += operator to add two vectors and assign the result to this vector
// Params:
//   other = The other vector to add.
// Return:
//   A pointer to this vector with the changed values
Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

// Overloads the -= operator to subtract two vectors and assign the result to this vector
// Params:
//   other = The other vector to subtract.
// Return:
//   A pointer to this vector with the changed values
Vector2D& Vector2D::operator-=(const Vector2D& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

// Overloads the *= operator to multiply this vector by a scalar and assign it to this vector
// Params:
//   other = The scalar.
// Return:
//   A pointer to this vector with the changed values
Vector2D& Vector2D::operator*=(const float other)
{
    x *= other;
    y *= other;

    return *this;
}

// Overloads the /= operator to divide this vector by a number and assign it to this vector
// Params:
//   other = The number to divide this vector by.
// Return:
//   A pointer to this vector with the changed values
Vector2D& Vector2D::operator/=(const float other)
{
    x /= other;
    y /= other;

    return *this;
}

// Overloads the - operator to convert this vector to the negative.
// Return:
//   A Vector with the negated values
Vector2D Vector2D::operator-() const
{
    return Vector2D(-x, -y);
}


///////////////////////////////////////////////////////////////////////////////
// 2 non-member, non-friend functions (operators)
// Overloads the << operator to print out the vector
// Params:
//   os = the stream to output the output to.
//   output = the vector to be printed.
// Return:
//   the stream with the value to be printed
std::ostream& operator<<(std::ostream& os, const Vector2D& out)
{
    os << "(" << out.X() << ", " << out.Y() << ")";
    
    return os;
}

// Overloads the * operator to multiply a float by a vector
// Params:
//   other = the scalar.
//   vector2D = the vector to be scaled.
// Return:
//   The result of the inverse operation (i.e. Vector2D * other).
Vector2D operator*(float other, const Vector2D& vector2D)
{
    return vector2D * other;
}


} // namespace CS170



