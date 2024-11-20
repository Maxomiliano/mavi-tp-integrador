#include "GameController.h"
#include "Cross.h"
#include "Character.h"
#include "Enemy.h"
#include "Innocent.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

GameController::GameController()
{

}

void GameController::Play()
{
	while (window.isOpen())
	{
		ProcessEvents();
		Update();
		Render();
	}
}

void GameController::ProcessEvents()
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
			CheckCollisions();
			break;
		}
	}
}

void GameController::Update()
{
	//Acá van los spwans??
}

void GameController::Render()
{
	window.clear();
	enemy.Draw(window);
	innocent.Draw(window);
	window.display();
}

void GameController::SpawnCharacters()
{

}

void GameController::CheckCollisions()
{
	if (mouse.isButtonPressed(mouse.Left))
	{
		if (enemy.IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
		{
			enemiesDefeated++;
		}
		if (enemiesDefeated < maxLives)
		{
			enemy.Spawn(window.getSize());
		}
		else
		{
			window.close();
		}
	}
}

void GameController::RestartGame()
{

}
