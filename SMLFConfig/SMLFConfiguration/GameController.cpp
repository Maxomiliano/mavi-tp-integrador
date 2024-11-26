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

	window(VideoMode(1024, 768, 32), "TPIntegrador"), state(State::MainMenu), maxLives(3), score(0),
	spawnPositions{ {0.f, 0.f}, {500.f, 0.f}, {400.f, 0.f}, {600.f, 0.f} }
{
	srand(time(NULL));
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
	int randomPosition = rand() % spawnPositions.size();
	Vector2f spawn = spawnPositions[randomPosition];
	if (rand() % 100 < 5)
	{	
		Enemy enemy;
		enemy.setTexture(enemyTex);
		enemy.Spawn(spawn);
		enemies.push_back(enemy);
	} 
	else if (rand() % 100 < 3)
	{
		Innocent innocent;
		innocent.setTexture(innocentTex);
		innocent.Spawn(spawn);
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
				enemy.Spawn(spawn);
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
