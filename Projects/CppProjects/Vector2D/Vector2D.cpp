#include "Vector2D.h"  // Vector2D members
#include <cmath>    // sqrt, atan, sin, cos

namespace CS170
{

///////////////////////////////////////////////////////////////////////////////
// 22 public member functions (2 constructors, 2 accessors, 2 mutators, 7 others, 9 operators) 

// Constructors (2)
Vector2D::Vector2D(float x_, float y_)
  : x(x_), y(y_)
{
}

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

// Accessors (2)
float Vector2D::X() const
{
    return x;
}

float Vector2D::Y() const
{
    return y;
}


// Mutators (2)
void Vector2D::X(const float newVal)
{
    x = newVal;
}

void Vector2D::Y(const float newVal)
{
    y = newVal;
}


// Other functions (7)
float Vector2D::MagnitudeSquared() const
{
    return (x * x) + (y * y);
}

float Vector2D::Magnitude() const
{
    return sqrt(MagnitudeSquared());
}

Vector2D Vector2D::Normalized() const
{
    return *this * (1 / Magnitude());
}

float Vector2D::DistanceSquared(const Vector2D& other) const
{
    Vector2D delta = *this - other;

    return (delta.X() * delta.X()) + (delta.Y() * delta.Y());
}

float Vector2D::Distance(const Vector2D& other) const
{
    return sqrt(DistanceSquared(other));
}

Vector2D Vector2D::Midpoint(const Vector2D& other) const
{
    return 0.5 * (*this + other);
}

float Vector2D::DotProduct(const Vector2D& other) const
{
    return (x * other.X()) + (y * other.Y());
}


// Operators (9)
Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D(x + other.X(), y + other.Y());
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return Vector2D(x - other.X(), y - other.Y());
}

Vector2D Vector2D::operator*(const float other) const
{
    return Vector2D(x * other, y * other);
}

Vector2D Vector2D::operator/(const float other) const
{
    return Vector2D(x / other, y / other);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    x += other.X();
    y += other.Y();

    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
    x -= other.X();
    y -= other.Y();

    return *this;
}

Vector2D& Vector2D::operator*=(const float other)
{
    x *= other;
    y *= other;

    return *this;
}

Vector2D& Vector2D::operator/=(const float other)
{
    x /= other;
    y /= other;

    return *this;
}

Vector2D Vector2D::operator-() const
{
    return Vector2D(-x, -y);
}


///////////////////////////////////////////////////////////////////////////////
// 2 non-member, non-friend functions (operators)
std::ostream& operator<<(std::ostream& os, const Vector2D& out)
{
    os << "(" << out.X() << ", ";
    os << out.Y() << ")" << std::endl;
    
    return os;
}

Vector2D operator*(float other, const Vector2D& vector2D)
{
    return vector2D * other;
}


} // namespace CS170



