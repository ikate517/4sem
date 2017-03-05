#include <iostream>
#include <math.h> 

struct Vector2
{
	float y, x; 
	Vector2(float _x, float _y);
	Vector2();
	Vector2 operator * (float k) const;
	Vector2 operator / (float k) const;
	Vector2 operator + (const Vector2& other) const;
	Vector2 operator - (const Vector2& other) const;
	Vector2& operator += (const Vector2& other);
	Vector2& operator -= (const Vector2& other);
	Vector2& operator *= (float k);
	Vector2& operator /= (float k);
	friend Vector2 operator * (float k, const Vector2& v); 
	friend std::ostream& operator << (std::ostream& stream, const Vector2& v);
	friend std::istream& operator >> (std::istream& stream, Vector2& v);
	float Len() const;
	float SquareLen() const;
	Vector2 Norm() const;
	Vector2 Perpendicular() const;
	float operator * (const Vector2& other) const;
	float operator ^ (const Vector2& other) const;
	Vector2 operator - () const;
	Vector2& Rotate(float angle);
	Vector2 GetRotated (float angle) const;
};
