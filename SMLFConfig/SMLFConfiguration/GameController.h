#pragma once
#include "Cross.h"
#include "Enemy.h"
#include "Innocent.h"
#include "Character.h"
#include <SFML/Graphics.hpp>
using namespace sf;

enum class State
{
	MainMenu,
	Play,
	GameOver
};

class GameController
{
public:
	GameController();
	void Play();
	void ProcessEvents();
	void Update();
	void Render();
	void SpawnCharacters();
	void CheckCollisions();
	void RestartGame();

private:
	Event evt;
	Mouse mouse;
	RenderWindow window;
	State state;
	Cross cross;
	Enemy enemy;
	Innocent innocent;
	Texture crossTex;
	Texture enemyTex;
	Texture innocentTex;
	Texture bgTex;

	int enemiesDefeated;
	int score;
	int maxLives = 3;
};

