#include "Drag.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;


Drag::Drag()
{
	Texture _rcircleTex;
	Sprite* _rcircleUpLeft = new Sprite();
	Sprite* _rcircleUpRight = new Sprite();
	Sprite* _rcircleDownLeft = new Sprite();
	Sprite* _rcircleDownRight = new Sprite();

	Texture _cursorTex;
	Sprite _cursorSpr;
	Sprite* _currentSelectedSprite = NULL;

	Event evt;
	Mouse mouse;
	Vector2i spritePosition = mouse.getPosition();
	Vector2i spriteLastPosition = mouse.getPosition();
	Vector2f* _clickOffset = new Vector2f(0, 0);

	_rcircleTex.loadFromFile("rcircle.png");
	_rcircleUpLeft->setTexture(_rcircleTex);
	_rcircleUpRight->setTexture(_rcircleTex);
	_rcircleDownLeft->setTexture(_rcircleTex);
	_rcircleDownRight->setTexture(_rcircleTex);

	RenderWindow window(VideoMode(800, 600, 32), "Drag");

	_rcircleUpLeft->setPosition(0, 0);
	_rcircleUpRight->setPosition(window.getSize().x - _rcircleTex.getSize().x, 0); //Para evitar numeros mágicos. Hacer lo mismo en los demás
	_rcircleDownRight->setPosition(0, window.getSize().y - _rcircleTex.getSize().y);
	_rcircleDownLeft->setPosition(window.getSize().x - _rcircleTex.getSize().x, window.getSize().y - _rcircleTex.getSize().y);


	while (window.isOpen())
	{
		Vector2i mousePositionInt = mouse.getPosition(window);
		Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);

		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::MouseButtonPressed:
				if (mouse.isButtonPressed(mouse.Left))
				{
					if (_rcircleUpLeft->getGlobalBounds().contains(mousePosition))
					{
						_currentSelectedSprite = _rcircleUpLeft;
					}
					else if (_rcircleDownLeft->getGlobalBounds().contains(mousePosition))
					{
						_currentSelectedSprite = _rcircleDownLeft;
					}
					else if (_rcircleUpRight->getGlobalBounds().contains(mousePosition))
					{
						_currentSelectedSprite = _rcircleUpRight;
					}
					else if (_rcircleDownRight->getGlobalBounds().contains(mousePosition))
					{
						_currentSelectedSprite = _rcircleDownRight;
					}
					if (_currentSelectedSprite != NULL)
					{
						_clickOffset = new Vector2f(_currentSelectedSprite->getPosition().x - mousePosition.x, _currentSelectedSprite->getPosition().y - mousePosition.y);
					}
				}
				break;
			case Event::MouseButtonReleased:
				_currentSelectedSprite = NULL;
				break;
			case Event::MouseMoved:
				if (_currentSelectedSprite != NULL)
				{
					_currentSelectedSprite->setPosition(mousePosition.x + _clickOffset->x, mousePosition.y + _clickOffset->y);
				}
				break;
			}
		}

		window.clear();
		window.draw(_cursorSpr);
		window.draw(*_rcircleUpLeft);
		window.draw(*_rcircleUpRight);
		window.draw(*_rcircleDownRight);
		window.draw(*_rcircleDownLeft);
		window.display();
	}
}
