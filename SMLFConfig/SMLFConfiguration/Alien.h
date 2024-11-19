#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Alien
{
public: Alien();
	  void Spawn(Vector2u windowSize);
	  bool IsClicked(Vector2f crossPosition);
	  void Draw(RenderWindow& window);
	  bool IsVisible() const;
	  void setTexture(const sf::Texture& texture);
	  void setScale(float x, float y);
private:
	Texture alienTex;
	Sprite alienSpr;
	bool isVisible;
};

