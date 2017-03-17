#pragma once
#include "Vector2.h"

class MaterialPoint
{
public:
	void updatePosition(float dt)
	{
		position += velocity * dt;
	};
	Vector2 getImpulse() const
	{
		return Vector2(mass * velocity);
	};
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	float mass;
};