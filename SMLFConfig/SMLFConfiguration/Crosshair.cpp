#include "Crosshair.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;


Crosshair::Crosshair()
{
	Texture _crosshairTex;
	Sprite _crosshairSpr;

	_crosshairTex.loadFromFile("crosshair.png");


	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Crosshair");

	_crosshairSpr.setTexture(_crosshairTex);
	_crosshairSpr.setOrigin(64, 64);
	_crosshairSpr.setPosition(400, 300);

	while (window.isOpen())
	{
		window.clear();
		window.draw(_crosshairSpr);
		window.display();
	}
}