#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class ball
{
public:
	ball(int windowWidth, int windowHeight);
	sf::CircleShape theBall;
	void update(sf::RenderWindow &window, Player &player1, Player &player2);

private:
	float leftEdge;
	float rightEdge;
	float radius;
	sf::Vector2f movement;
	void checkCollisions(Player &player1, Player &player2);
};

