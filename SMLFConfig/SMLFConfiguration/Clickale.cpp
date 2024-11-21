/*
#include "Clickale.h"
#include "Alien.h"
#include "Cross.h"
#include "Character.h"
#include "Enemy.h"
#include "Innocent.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

Clickale::Clickale() : window(VideoMode(800, 600), "Clickale"), enemiesDefeated(0)
{
	crossTex.loadFromFile("crosshair.png");
	alienTex.loadFromFile("et.png");

	cross.setTexture(crossTex);
	enemy.setTexture(alienTex);

	float widthCross = (float)crossTex.getSize().x;
	float heightCross = (float)crossTex.getSize().y;
	float widthAlien = (float)alienTex.getSize().x;
	float heightAlien = (float)alienTex.getSize().y;

	float scaleX = widthCross / widthAlien;
	float scaleY = heightCross / heightAlien;

	enemy.setScale(scaleX, scaleY);
	enemy.Spawn(window.getSize());

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
					if (enemy.IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
					{
						enemiesDefeated++;
					}
					if (enemiesDefeated < maxScore)
					{
						enemy.Spawn(window.getSize());
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
		enemy.Draw(window);
		cross.Draw(window);
		window.display();
	}
}
*/