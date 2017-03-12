#include <SFML\Graphics.hpp>
#include "Vector2.h"

const float Pi = 3.14159f;
const int indent = 20;

struct Hero
{
	Vector2 pos;
	Vector2 velocity;
	void update(float dt)
	{
		pos += velocity * dt;
	}
};

struct Bullet
{
	Vector2 pos;
	Vector2 velocity;
	void update(float dt)
	{
		pos += velocity * dt;
	}
};

struct Lazer
{
	Vector2 pos;
	int velocity;
	Vector2 len;
};

struct Map
{
	Vector2 size;
	Hero hero;
	std::vector<Bullet>bullets;
	void update(float dt)
	{
		hero.update(dt);
		for (auto& b : bullets)
		{
			b.update(dt);
		}
	}

	bool bullet_delete(const Bullet& bullet) const
	{
		return bullet.pos.x > size.x || bullet.pos.x < 0 || bullet.pos.y > size.y || bullet.pos.y < 0;
	}
	
	Vector2 check_pos(const Vector2& position) const
	{
		Vector2 result = position;
		if (position.x > size.x)
			result.x = indent;
		if (position.x < 0)
			result.x = size.x - indent;
		if (position.y > size.y)
			result.y = indent;
		if (position.y < 0)
			result.y  = size.y - indent;
		return result;
	}
	
};

int main()
{
	Map map;
	map.size = Vector2(900, 700);
	sf::RenderWindow window(sf::VideoMode(map.size.x, map.size.y), "My window");
	sf::Clock clock;
	Bullet bull;
	Lazer lazer;
	map.hero.pos = Vector2(100, 100);
	lazer.len = Vector2(4, 0);
	float last_time = 0;
	Vector2 tmp;
	sf::Texture texture;
	texture.loadFromFile("homer.png");
	sf::Sprite circle(texture);
	sf::Texture texture2;
	texture2.loadFromFile("eat.png");
	sf::Sprite circle1(texture2);
	circle1.setScale(0.2f, 0.2f);
	float V = 1;
	lazer.velocity = 10;
	circle.setScale(0.5f, 0.5f);
	sf::RectangleShape rectangle(sf::Vector2f(0, 0));
	rectangle.move(sf::Vector2f(400, 200));
	rectangle.setFillColor(sf::Color(128, 255, 0));
	sf::Event event;
	while (window.isOpen())
	{
		sf::Time time = clock.getElapsedTime();
		sf::Event event;
		map.hero.velocity = Vector2(0, 0);
		window.clear(sf::Color::Red);
		map.hero.pos = map.check_pos(map.hero.pos);
		circle.setPosition(map.hero.pos.x, map.hero.pos.y);
		window.draw(circle);
		sf::Vector2u circleSize = circle.getTexture()->getSize();
		circle.setOrigin(circleSize.x / 2, circleSize.y / 2);
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		Vector2 center = Vector2(circle.getPosition().x, circle.getPosition().y);
		Vector2 d = Vector2(mousePosition.x, mousePosition.y) - center;
		circle.setRotation(atan2f(d.y, d.x) * 180 / Pi);
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Left)
					{
						map.hero.velocity = Vector2(-V, 0);
					}
					if (event.key.code == sf::Keyboard::Right)
					{
						map.hero.velocity = Vector2(V, 0);
					}
					if (event.key.code == sf::Keyboard::Up)
					{
						map.hero.velocity = Vector2(0, -V);
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						map.hero.velocity = Vector2(0, V);
					}
				}
				case sf::Event::MouseButtonPressed:
					if (event.key.code == sf::Mouse::Left)
					{
						bull.pos = map.hero.pos;
						bull.velocity = d.Norm() * 3;
						map.bullets.push_back(bull);
					}
				default:
					break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			lazer.len.y += lazer.velocity;
			lazer.pos = map.hero.pos;
			rectangle.setSize(sf::Vector2f(lazer.len.x, lazer.len.y));
			rectangle.setPosition(map.hero.pos.x, map.hero.pos.y);
			rectangle.setRotation(270 + atan2f(d.y, d.x) * 180 / Pi);
			window.draw(rectangle);
		}
		else
		{
			lazer.len.y = 0;
		}

		for (auto& bullet : map.bullets)
		{
			tmp = bullet.pos + bullet.velocity;
			circle1.setPosition(tmp.x, tmp.y);
			bullet.pos = tmp;
			window.draw(circle1);
		}
		for (auto itr = map.bullets.begin(); itr != map.bullets.end(); ++itr)
		{

			if (map.bullet_delete(*itr))
			{
				map.bullets.erase(itr);
				itr--;
			}
		}
		map.update(time.asSeconds());
		window.display();
	}
	return 0;
}
