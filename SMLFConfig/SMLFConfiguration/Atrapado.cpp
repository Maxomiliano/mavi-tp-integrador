#include "Atrapado.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

Atrapado::Atrapado()
{
	Event evt;
	Mouse mouse;
	Texture _ysquareTex;
	Texture _rcircleTex;
	Sprite* _currentSpr = new Sprite();

	bool isSquare = true;

	float scaleX;
	float scaleY;
	float heightSquare;
	float heightCircle;
	float widthSquare;
	float widthCircle;

	float movementPos = 5.0f;


	_ysquareTex.loadFromFile("cuad_yellow.png");
	_rcircleTex.loadFromFile("rcircle.png");
	_currentSpr->setTexture(_ysquareTex);
	_currentSpr->setPosition(500, 500);

	widthSquare = (float)_ysquareTex.getSize().x;
	heightSquare = (float)_ysquareTex.getSize().y;
	widthCircle = (float)_rcircleTex.getSize().x;
	heightCircle = (float)_rcircleTex.getSize().y;

	scaleX = widthCircle / widthSquare;
	scaleY = heightCircle / heightSquare;
	_currentSpr->setScale(scaleX, scaleY);

	RenderWindow window(VideoMode(800, 800, 32), "Atrapado");

	while (window.isOpen())
	{
		Vector2u windowSize = window.getSize();
		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:

				FloatRect spriteBounds = _currentSpr->getGlobalBounds();

				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					if (spriteBounds.top > 0)
						_currentSpr->move(0, -movementPos);
				}
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					if (spriteBounds.left > 0)
						_currentSpr->move(-movementPos, 0);
				}
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					if (spriteBounds.top + spriteBounds.height < windowSize.y)
						_currentSpr->move(0, movementPos);
				}
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					if (spriteBounds.left + spriteBounds.width < windowSize.x)
						_currentSpr->move(movementPos, 0);
				}

				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					if (isSquare)
					{
						_currentSpr->setTexture(_rcircleTex);
						_currentSpr->setScale(1, 1);
						isSquare = false;
					}
					else
					{
						_currentSpr->setTexture(_ysquareTex);
						_currentSpr->setScale(scaleX, scaleY);
						isSquare = true;
					}
					spriteBounds = _currentSpr->getGlobalBounds();
				}
			}
		}
		window.clear();
		window.draw(*_currentSpr);
		window.display();
	}
}
