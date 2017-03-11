#include <SFML\Graphics.hpp>

const int K = 10;
const int IterationCount = 30;

using Centroids = std::vector<sf::Color>;
using ClosestCentroidsIndices = std::vector<int>;

struct ColorBuf
{
	int r, g, b, a;
	int count;
	ColorBuf& operator += (const sf::Color& c)
	{
		count++;
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	};
};

Centroids initializeCentroids(sf::Image image, int k)
{
	Centroids result;
	sf::Color color;
	sf::Vector2u pixel;
	for (int it = 0; it < k; ++it)
	{
		pixel.x = rand() % image.getSize().x;
		pixel.y = rand() % image.getSize().y;
		color = image.getPixel(pixel.x, pixel.y);
		result.push_back(color);
	}
	return result;
}

int getLength(sf::Color pixel, sf::Color centroid)
{
	return ((pixel.r - centroid.r) * (pixel.r - centroid.r) + (pixel.g - centroid.g) * (pixel.g - centroid.g) + (pixel.b - centroid.b) * (pixel.b - centroid.b));
}

ClosestCentroidsIndices findClosestCentroids(const sf::Image& image, Centroids centroids)
{
	sf::Vector2u size(image.getSize().x, image.getSize().y);
	ClosestCentroidsIndices result;
	result.resize(size.x * size.y);
	std::vector<int> length;
	length.resize(K);
	int min;
	int num = 0;
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			for (int k = 0; k < K; k++)
			{
				length[k] = getLength(image.getPixel(j, i), centroids[k]);
			}
			min = length[0];
			for (int k = 0; k < K; k++)
			{
				if (min > length[k])
				{
					min = length[k];
					num = k;
				}
			}
			result[i * size.x + j] = num;
		}
	}
	return result;
}
Centroids computeMeans(sf::Image& image, ClosestCentroidsIndices ids, int k)
{
	Centroids result;
	result.resize(k);
	std::vector<ColorBuf> colorbuf;
	colorbuf.resize(K);
	for (int i = 0; i < ids.size(); i++)
	{
		colorbuf[ids[i]] += image.getPixel(i % image.getSize().x, i / image.getSize().x);
	}
	for (int i = 0; i < K; i++)
	{
		if (colorbuf[i].count != 0)
		{
			colorbuf[i].r /= colorbuf[i].count;
			colorbuf[i].g /= colorbuf[i].count;
			colorbuf[i].b /= colorbuf[i].count;
		}
	}
	for (int i = 0; i < K; i++)
	{
		result[i] = sf::Color(colorbuf[i].r, colorbuf[i].g, colorbuf[i].b);
	}
	return result;
}

void changeColors(sf::Image& image, ClosestCentroidsIndices ids, Centroids centroids)
{
	for (int i = 0; i < ids.size(); i++)
	{
		image.setPixel(i % image.getSize().x, i / image.getSize().x, centroids[ids[i]]);
	}
}

int main()
{
	sf::Texture texture;
	texture.loadFromFile("nika.png");
	auto image = texture.copyToImage();
	texture.update(image);
	ClosestCentroidsIndices ids;
	Centroids centroids = initializeCentroids(image, K);
	for (int it = 0; it < IterationCount; ++it)
	{
		ids = findClosestCentroids(image, centroids);
		centroids = computeMeans(image, ids, K);
	}
	changeColors(image, ids, centroids);
	texture.update(image);
	image.saveToFile("result.png");
	texture.update(image);
	sf::Sprite photo;
	photo.setTexture(texture);
	sf::Vector2u size = photo.getTexture()->getSize();
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "My window");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(photo);
		window.display();
	}
}