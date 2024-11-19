#include "Splats.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

Splats::Splats()
{
	Event evt;
	Mouse mouse;
	Texture _bcircleTex;
	Texture _rcircleTex;
	Sprite* _bcircleSpr = new Sprite();
	Sprite* _rcircleSpr = new Sprite();
	Vector2f* _leftClickOffset = new Vector2f(0, 0);
	Vector2f* _rightClickOffset = new Vector2f(0, 0);

	_bcircleTex.loadFromFile("rcircleb.png");
	_rcircleTex.loadFromFile("rcircle.png");
	_bcircleSpr->setTexture(_bcircleTex);
	_rcircleSpr->setTexture(_rcircleTex);

	RenderWindow window(VideoMode(800, 600, 32), "Splats");

	while (window.isOpen())
	{
		Vector2i mousePositionInt = mouse.getPosition(window);
		Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);
		_rcircleSpr->setOrigin(64, 64);
		_bcircleSpr->setOrigin(64, 64);
		_rcircleSpr->setPosition(mousePosition);
		_bcircleSpr->setPosition(mousePosition);

		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::MouseButtonPressed:
				_leftClickOffset = new Vector2f(_rcircleSpr->getPosition().x - mousePosition.x, _rcircleSpr->getPosition().y - mousePosition.y);
				_rightClickOffset = new Vector2f(_bcircleSpr->getPosition().x - mousePosition.x, _bcircleSpr->getPosition().y - mousePosition.y);
				if (mouse.isButtonPressed(mouse.Left))
				{
					window.draw(*_rcircleSpr);
				}
				else if (mouse.isButtonPressed(mouse.Right))
				{
					window.draw(*_bcircleSpr);
				}
				break;
			}
		}
		window.display();
	}
}
