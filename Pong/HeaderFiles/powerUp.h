#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "ball.h"

class powerUp
{
public:
	powerUp();
	sf::CircleShape item;
	void setLocation(int windowWidth, int windowHeight);
	string getState();
	void setState(string setState);


private:
	string state;
};



