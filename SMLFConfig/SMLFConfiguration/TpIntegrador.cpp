#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameController.h"
#include <iostream>
using namespace sf;
using namespace std;

int main()
{
	//srand(time(NULL));
	GameController gc;
	gc.Play();
	return 0;
}
