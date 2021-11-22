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
		Vector2D(float x, float y);
		Vector2D();
		
		// Accessors (2)
		float X() const;
		float Y() const;
		
		
		// Mutators (2)
		void X(const float newVal);
		void Y(const float newVal);
		
		
		// Other functions (7)
		float MagnitudeSquared() const;
		float Magnitude() const;
		Vector2D Normalized() const;
		float DistanceSquared(const Vector2D& other) const;
		float Distance(const Vector2D& other) const;
		Vector2D Midpoint(const Vector2D& other) const;
		float DotProduct(const Vector2D& other) const;

		// Overloaded operators (9 member functions)
		Vector2D operator+(const Vector2D& other) const;
		Vector2D operator-(const Vector2D& other) const;
		Vector2D operator*(const float other) const;
		Vector2D operator/(const float other) const;
		Vector2D& operator+=(const Vector2D& other);
		Vector2D& operator-=(const Vector2D& other);
		Vector2D& operator*=(const float other);
		Vector2D& operator/=(const float other);
		Vector2D operator-() const;
		
		
	private:
		float x; // The x-coordinate of a Vector2D
		float y; // The y-coordinate of a Vector2D
	};
  
	// Overloaded operators (2 non-member, non-friend functions)
	std::ostream& operator<<(std::ostream& os, const Vector2D& output);
	Vector2D operator*(float other, const Vector2D& vector2D);
	

} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
