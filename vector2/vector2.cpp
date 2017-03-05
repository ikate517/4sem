#include "vector2.h"

Vector2::Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2 Vector2::operator * (float k) const
{
	return Vector2(x * k, y * k);
}

Vector2 Vector2::operator / (float k) const
{
	return Vector2(x / k, y / k);
}

Vector2 Vector2::operator + (const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator - (const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator += (const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::operator *= (float k)
{
	x *= k;
	y *= k;
	return *this;
}

Vector2& Vector2::operator /= (float k)
{
	x /= k;
	y /= k;
	return *this;
}

std::ostream& operator << (std::ostream& stream, const Vector2& v)
{
	stream << v.x << " " << v.y;
	return stream;
}

std::istream& operator >> (std::istream& stream, Vector2& v)
{
	stream >> v.x >> v.y;
	return stream;
}

Vector2 operator * (float k, const Vector2& v)
 {
	return Vector2(v.x * k, v.y * k);
 }

float Vector2::Len() const
{
	return sqrt(x * x + y * y);
}

float Vector2::SquareLen() const
{
	return (x * x + y * y);
}

Vector2 Vector2::Norm() const
{
	float len = Len();
	return Vector2(x / len, y / len);
}

Vector2 Vector2::Perpendicular() const
{
	return Vector2(-y, x);
}

float Vector2::operator * (const Vector2& other) const
{
	return (other.x * x + other.y * y);
}

float Vector2::operator ^ (const Vector2& other) const
{
	 float result = x * other.y - y * other.x;
	 return result;
}

Vector2 Vector2::operator - () const
{
	return Vector2(-x, -y);
}

Vector2& Vector2::Rotate(float angle)
{
	float _x = x, _y = y;
	x = _x * cos(angle) - _y * sin(angle);
	y = _x * sin(angle) + _y * cos(angle);
	return *this;
}

Vector2 Vector2::GetRotated (float angle) const
{
	return Vector2(x, y).Rotate(angle);
}
