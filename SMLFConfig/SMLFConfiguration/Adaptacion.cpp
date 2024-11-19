#include "Adaptacion.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

Adaptacion::Adaptacion()
{
	Event evt;
	int minSize = 100;
	int maxSize = 1000;

	RenderWindow window(VideoMode(800, 800, 32), "Adaptacion");
	Vector2u windowSize = window.getSize();

	while (window.isOpen())
	{
		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					if (windowSize.y < maxSize)
						windowSize.y += 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					if (windowSize.y > minSize)
						windowSize.y -= 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					if (windowSize.x < maxSize)
						windowSize.x += 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					if (windowSize.x > minSize)
						windowSize.x -= 1;
				}
				window.setSize(windowSize);
			}
		}
		window.clear();
		window.display();
	}
}