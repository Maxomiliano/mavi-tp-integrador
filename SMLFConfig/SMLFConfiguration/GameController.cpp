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

	window(VideoMode(1024, 768, 32), "TPIntegrador"), state(State::MainMenu), maxLives(3), score(0), enemiesDefeated(0),
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
	float time = clock.restart().asSeconds();
	actionTime += time;
	if (spawnedChar != NULL)
	{
		if (actionTime >= actionDelay)
		{
			if (spawnedChar->getCharacterType() == Character::CharacterType::Enemy)
			{
				maxLives--;
			}
			else if (spawnedChar->getCharacterType() == Character::CharacterType::Innocent)
			{
				cout << "Disapeared" << endl;
			}
			delete spawnedChar;
			spawnedChar = NULL;
		}
	}
	else
	{
		SpawnCharacters();
	}
}

void GameController::Render()
{
	window.clear();

	window.draw(bgSpr);
	if (spawnedChar != NULL)
	{
		spawnedChar->Draw(window);
	}
	cross.Draw(window);
	window.display();
}

void GameController::SpawnCharacters()
{
	if (spawnedChar == NULL)
	{
		int randomPosition = rand() % spawnPositions.size();
		Vector2f spawn = spawnPositions[randomPosition];
		if (rand() % 2 == 0)
		{
			spawnedChar = new Enemy();
			spawnedChar->setTexture(enemyTex);
		}
		else
		{
			spawnedChar = new Innocent;
			spawnedChar->setTexture(innocentTex);
		}
		spawnedChar->Spawn(spawn);
		actionTime = 0.0f;
	}
}
void GameController::CheckCollisions()
{
	//if (evt.type == Event::MouseButtonPressed && mouse.isButtonPressed(mouse.Left))
	//{
		if (spawnedChar != NULL && spawnedChar->IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
		{
			if (spawnedChar->getCharacterType() == Character::CharacterType::Enemy)
			{
				enemiesDefeated++;
				std::cout << "Enemy defeated! Total: " << enemiesDefeated << std::endl;
			}
			else if (spawnedChar->getCharacterType() == Character::CharacterType::Innocent)
			{
				maxLives--;
				std::cout << "You clicked an innocent! Lives remaining: " << maxLives << std::endl;
			}

			delete spawnedChar;
			spawnedChar = NULL;
		}
	//}
}
/*
void GameController::CheckCollisions()
{
	if (evt.type == Event::MouseButtonPressed && mouse.isButtonPressed(mouse.Left))
	{
		if (enemy.IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
		{
			enemiesDefeated++;
		}
		if (enemiesDefeated < maxLives)
		{
			enemy.Spawn(spawn);
		}
		if (innocent.IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
		{
			maxLives--;
		}
	}
}
*/

void GameController::RestartGame()
{

}
