#include "Enemy.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

Enemy::Enemy() : Character()
{

}

void Enemy::Shoot()
{

}

void Enemy::Spawn(Vector2u windowSize)
{
	Character::Spawn(windowSize);
}