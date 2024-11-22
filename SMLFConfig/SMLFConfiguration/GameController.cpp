#include "GameController.h"
#include "Cross.h"
#include "Character.h"
#include "Enemy.h"
#include "Innocent.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

GameController::GameController() :

	window(VideoMode(1024, 768, 32), "TPIntegrador"), state(State::MainMenu), maxLives(3), score(0)
{
	crossTex.loadFromFile("crosshair.png");
	enemyTex.loadFromFile("enemy.png");
	innocentTex.loadFromFile("innocent.jpg");
	bgTex.loadFromFile("background.png");

	cross.setTexture(crossTex);
	bgSpr.setTexture(bgTex);
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
	SpawnCharacters();
}

void GameController::Render()
{
	window.clear();

	window.draw(bgSpr);
	for (auto& enemy : enemies)
	{
		enemy.Draw(window);
	}
	for (auto& innocent : innocents)
	{
		innocent.Draw(window);
	}
	cross.Draw(window);
	window.display();
}

void GameController::SpawnCharacters()
{
	if (rand() % 100 < 5)
	{
		Enemy enemy;
		enemy.setTexture(enemyTex);
		enemy.Spawn(window.getSize());
		enemies.push_back(enemy);
	}
	else
	{
		Innocent innocent;
		innocent.setTexture(innocentTex);
		innocent.Spawn(window.getSize());
		innocents.push_back(innocent);
	}
}

void GameController::CheckCollisions()
{
	if (evt.type == Event::MouseButtonPressed && mouse.isButtonPressed(mouse.Left))
	{
		for (auto& enemy : enemies)
		{
			if (enemy.IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
			{
				enemiesDefeated++;
			}
			if (enemiesDefeated < maxLives)
			{
				enemy.Spawn(window.getSize());
			}
		}
		for (auto& innocent : innocents)
		{
			if (innocent.IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
			{
				maxLives--;
			}
		}
	}
}

void GameController::RestartGame()
{

}
