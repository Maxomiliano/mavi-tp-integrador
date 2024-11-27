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

	window(VideoMode(1024, 900, 32), "TPIntegrador"), state(State::MainMenu), maxLives(3), score(0), enemiesDefeated(0), innocentsShooted(0),
	spawnPositions{ {0.f, 0.f}, {500.f, 0.f}, {400.f, 0.f}, {600.f, 0.f} }
{
	srand(time(NULL));
	if (!font.loadFromFile("Cowboys.otf"))
	{
		cout << "Error loading font" << endl;
	}
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
	Vector2f mousePos(evt.mouseButton.x, evt.mouseButton.y);
	while (window.pollEvent(evt))
	{
		switch (state)
		{
		case State::MainMenu:
			if (evt.type == Event::MouseButtonPressed)
			{
				if (playButton.getGlobalBounds().contains(mousePos))
				{
					state = State::Play;
					RestartGame();
				}
				else if (exitButton.getGlobalBounds().contains(mousePos))
				{
					window.close();
				}
			}
			break;
		case State::Play:
			if (evt.type == Event::MouseMoved)
			{
				cross.UpdatePosition(Vector2f(evt.mouseMove.x, evt.mouseMove.y));
			}
			else if (evt.type == Event::MouseButtonPressed)
			{
				CheckCollisions();
			}
			break;
		case State::GameOver:
			if (evt.type == Event::MouseButtonPressed)
			{
				if (backToMenuButton.getGlobalBounds().contains(mousePos))
				{
					state = State::MainMenu;
				}
			}
			break;
		}
	}
}

void GameController::Update()
{
	if (state == State::Play)
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
					cout << "Enemy shot! Lives remaining:" << maxLives << endl;
				}
				else if (spawnedChar->getCharacterType() == Character::CharacterType::Innocent)
				{
					delete spawnedChar;
					spawnedChar = NULL;
					cout << "Disapeared" << endl;
				}
				if (spawnedChar != NULL)
					actionTime = 0.0f;
			}
		}
		else
		{
			SpawnCharacters();
		}
		if (enemiesDefeated >= 10)
		{
			state = State::GameOver;
			resultText.setString("Victory!");
		}
		else if (maxLives <= 0)
		{
			state = State::GameOver;
			resultText.setString("Defeat!");
		}
	}
}

void GameController::Render()
{
	window.clear();

	if (state == State::MainMenu)
		RenderMainMenu();
	else if (state == State::Play)
		RenderPlayScene();
	else if (state == State::GameOver)
		RenderGameOver();

	window.display();
}

void GameController::RenderMainMenu()
{
	playButton.setFont(font);
	playButton.setString("Play");
	playButton.setCharacterSize(30);
	playButton.setPosition(350, 200);

	exitButton.setFont(font);
	exitButton.setString("Exit");
	exitButton.setCharacterSize(30);
	exitButton.setPosition(150, 200);

	window.draw(playButton);
	window.draw(exitButton);
}

void GameController::RenderPlayScene()
{
	window.draw(bgSpr);
	if (spawnedChar != NULL)
	{
		spawnedChar->Draw(window);
	}
	cross.Draw(window);

	nombreAlumno.setFont(font);
	nombreAlumno.setCharacterSize(30);
	nombreAlumno.setString("TP Integral. Garcia, Maximiliano.");
	nombreAlumno.setPosition(10, 870);

	livesHud.setFont(font);
	livesHud.setCharacterSize(30);
	livesHud.setString("Lives: " + to_string(maxLives));
	livesHud.setPosition(10, 800);

	enemiesDefeatedHud.setFont(font);
	enemiesDefeatedHud.setCharacterSize(30);
	enemiesDefeatedHud.setString("Enemies killed: " + to_string(enemiesDefeated));
	enemiesDefeatedHud.setPosition(10, 850);

	scoreHud.setFont(font);
	scoreHud.setCharacterSize(30);
	scoreHud.setString("Score " + to_string(enemiesDefeated - (innocentsShooted * 2)));
	enemiesDefeatedHud.setPosition(700, 850);

	window.draw(nombreAlumno);
	window.draw(livesHud);
	window.draw(enemiesDefeatedHud);
	window.draw(scoreHud);
}

void GameController::RenderGameOver()
{
	resultText.setFont(font);
	resultText.setCharacterSize(40);
	resultText.setPosition(500, 500);

	backToMenuButton.setFont(font);
	backToMenuButton.setString("Back to Menu");
	backToMenuButton.setCharacterSize(30);
	backToMenuButton.setPosition(320, 300);

	window.draw(resultText);
	window.draw(backToMenuButton);
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
	if (spawnedChar != NULL && spawnedChar->IsClicked(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
	{
		if (spawnedChar->getCharacterType() == Character::CharacterType::Enemy)
		{
			enemiesDefeated++;
			cout << "Enemy defeated! Total: " << enemiesDefeated << endl;
		}
		else if (spawnedChar->getCharacterType() == Character::CharacterType::Innocent)
		{
			maxLives--;
			innocentsShooted++;
			cout << "You clicked an innocent! Lives remaining: " << maxLives << endl;
		}

		delete spawnedChar;
		spawnedChar = NULL;
	}
}


void GameController::RestartGame()
{
	enemiesDefeated = 0;
	maxLives = 3;
}
