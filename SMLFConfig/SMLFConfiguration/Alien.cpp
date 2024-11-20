/*
#include "Alien.h"
#include <SFML/Graphics.hpp>

Alien::Alien()
{
	isVisible = true;
	std::srand(static_cast<unsigned int>(std::time(NULL)));
}

void Alien::Spawn(Vector2u windowSize)
{
	float x = rand() % windowSize.x;
	float y = rand() % windowSize.y;
	alienSpr.setPosition(x, y);
	isVisible = true;
}

bool Alien::IsClicked(Vector2f crossPosition)
{
	if (isVisible && alienSpr.getGlobalBounds().contains(crossPosition))
	{
		isVisible = false;
		return true;
	}
	return false;
}

void Alien::Draw(RenderWindow& window)
{
	if (isVisible)
	{
		window.draw(alienSpr);
	}
}

bool Alien::IsVisible() const
{
	return isVisible;
}

void Alien::setTexture(const sf::Texture& texture) {
	alienSpr.setTexture(texture);
}

void Alien::setScale(float x, float y) {
	alienSpr.setScale(x, y);
}
*/