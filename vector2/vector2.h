#include <iostream>
#include <math.h> 

struct Vector2
{
	float y, x; 
	Vector2(float _x, float _y);
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
	
	/*
	fixit : у вас стили именования методов разные ... определитесь как больше нравится ...
	пишите, например, всегда первую букву строчной
	*/
	float Len() const;
	float squareLen() const;
	Vector2 Norm() const;
	Vector2 Perpendicular() const;
	float operator * (const Vector2& other) const;
	float operator ^ (const Vector2& other) const;
	Vector2 operator - () const;
	Vector2& rotate(float angle);
	Vector2 getRotated (float angle) const;
};
