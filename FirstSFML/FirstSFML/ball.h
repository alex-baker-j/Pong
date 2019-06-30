#pragma once
#include <SFML/Graphics.hpp>

class ball
{
public:
	ball(int windowWidth, int windowHeight);
	sf::CircleShape theBall;
	void update(sf::RenderWindow &window);

private:
	float leftEdge;
	float rightEdge;
	float radius;
	sf::Vector2f movement;
};

