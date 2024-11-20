#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy();
	void Shoot();
	void Spawn(sf::Vector2u windowSize) override;
};

