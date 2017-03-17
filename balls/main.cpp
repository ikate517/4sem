#include <SFML\Graphics.hpp>
#include "MaterialPoint.h"
#include <vector>

class Ball: public MaterialPoint
{
public:
	float radius;
	int type;
	Vector2 checkVelocity(const Vector2& size) 
	{
		if ((position.x + 2 * radius)> size.x || position.x < 0)
			velocity.x = -velocity.x;
		if ((position.y + 2 * radius) > size.y || position.y < 0)
			velocity.y = -velocity.y;
		return velocity;
	}
};

Vector2 deltaImpuls(const Ball& i,const Ball& j,const Vector2& d)
{
	return (2 * (i.velocity - j.velocity) / ((1 / i.mass) + (1 / j.mass)) * d.Norm()) *d.Norm();
}

int main()
{
	Vector2 size(1000, 700);
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "My window");
	sf::Clock clock;
	std::vector<Ball> balls;
	int velocity = 30000;
	sf::CircleShape circle(10);
	circle.setFillColor(sf::Color::Green);
	sf::Time time = clock.getElapsedTime();
	while (window.isOpen())
	{
		window.clear(sf::Color::Red);
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
				} break;
				case sf::Event::MouseButtonPressed:
				{
					if (event.key.code == sf::Mouse::Left)
					{
						Ball b;
						b.position = Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
						b.velocity = Vector2(velocity, velocity);
						float angle = rand() % 360;
						b.velocity.Rotate(angle);
						b.radius = rand() % 20 + 5;
						b.mass = b.radius * 5;
						balls.push_back(b);

					} break;
				default:
					break;
				}
			}
		}
		Vector2 p;
		for (int i = 0; i < balls.size(); i++)
		{
			circle.setPosition(balls[i].position.x, balls[i].position.y);
			circle.setRadius(balls[i].radius);
			balls[i].velocity = balls[i].checkVelocity(size);
			for (int j = i + 1; j < balls.size(); j++)
			{
				Vector2 d = balls[i].position - balls[j].position + Vector2(balls[i].radius - balls[j].radius, balls[i].radius - balls[j].radius);
				if (d.Len() <= (balls[i].radius + balls[j].radius) && ((balls[i].velocity - balls[j].velocity) * d) < 0)
				{
					p = deltaImpuls(balls[i], balls[j], d);
					balls[j].velocity += p / balls[j].mass;
					balls[i].velocity -= p / balls[i].mass;
				}
			}
			balls[i].updatePosition(time.asSeconds());
			window.draw(circle);
		}
		window.display();
	}
	return 0;
}
