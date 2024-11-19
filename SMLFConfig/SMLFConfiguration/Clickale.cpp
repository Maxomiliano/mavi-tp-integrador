#include "Clickale.h"
#include "Alien.h"
#include "Cross.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

Clickale::Clickale() : window(VideoMode(800, 600), "Clickale"), aliensDefeated(0)
{
	crossTex.loadFromFile("crosshair.png");
	alienTex.loadFromFile("et.png");

	cross.setTexture(crossTex);
	alien.setTexture(alienTex);

	float widthCross = (float)crossTex.getSize().x;
	float heightCross = (float)crossTex.getSize().y;
	float widthAlien = (float)alienTex.getSize().x;
	float heightAlien = (float)alienTex.getSize().y;

	float scaleX = widthCross / widthAlien;
	float scaleY = heightCross / heightAlien;

	alien.setScale(scaleX, scaleY);
	alien.Spawn(window.getSize());

	Play();
}

void Clickale::Play()
{
	Event evt;
	Mouse mouse;
	while (window.isOpen())
	{
		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
			case Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				cross.UpdatePosition(Vector2f(evt.mouseMove.x, evt.mouseMove.y));
				break;
			case Event::MouseButtonPressed:
				if (mouse.isButtonPressed(mouse.Left))
				{
					if (alien.IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
					{
						aliensDefeated++;
					}
					if (aliensDefeated < maxScore)
					{
						alien.Spawn(window.getSize());
					}
					else
					{
						window.close();
					}
				}
				break;
			}
		}
		window.clear();
		alien.Draw(window);
		cross.Draw(window);
		window.display();
	}
}