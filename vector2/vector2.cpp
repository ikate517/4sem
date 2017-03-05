#include "vector2.h"

Vector2::Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
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
	Vector2::Vector2 v2(0, 0);
	v2.x = other.x + x;
	v2.y = other.y + y;
	return v2;
	/*
	fixit: в одну строку return Vector2(x + other.x, y + other.y);
	*/
}

Vector2 Vector2::operator - (const Vector2& other) const
{
	Vector2::Vector2 v2(0, 0);
	v2.x = x - other.x;
	v2.y = y - other.y;
	/* в одну строку */
	return v2;
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

float Vector2::squareLen() const
{
	return (x * x + y * y);
}

Vector2 Vector2::Norm() const
{
	Vector2 result(0, 0);
	result.x = x/Len();
	result.y = y/Len();
	// в одну строку. в целях оптимизации производительности длину можно один раз посчитать и запомнить, т.к. корень - относительно дорогая операция
	return result;
}

Vector2 Vector2::Perpendicular() const
{
	return Vector2(-y, x);
}

float Vector2::operator * (const Vector2& other) const
{
	float result = other.x * x + other.y * y;
	// можно в одну строку писать без вспомогательной переменной
	return result;
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

Vector2& Vector2::rotate(float angle)
{
	// fixit: у вас неправильный код ... во второй строке x уже измененный подаете
	x = x * cos(angle) - y * sin(angle);
	y = x * sin(angle) + y * cos(angle);
	return *this;
}

Vector2 Vector2::getRotated (float angle) const
{
	// fix it: код правильный, но два раза писать одни и те же ф-лы не круто
	// если прошлый метод исправить, то можно написать в одну строку return Vector2(x, y).rotate(angle);
	/// и ещё ... напишите пустой конструктор Vector2(), чтобы не приходило каждый раз для взякий временных переменных сразу
	// инициализировать их явно
	Vector2 result(0, 0);
	result.x = x * cos(angle) - y * sin(angle);
	result.y = x * sin(angle) + y * cos(angle);
	return result;
}
