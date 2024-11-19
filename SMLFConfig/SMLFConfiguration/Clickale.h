#pragma once
#include "Alien.h"
#include "Cross.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Clickale
{
public:
	Clickale();
	void Play();

private:
	RenderWindow window;
	Cross cross;
	Alien alien;
	int aliensDefeated;
	int maxScore = 5;

	Texture crossTex;
	Texture alienTex;
};



