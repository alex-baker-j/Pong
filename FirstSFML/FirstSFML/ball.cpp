#include "pch.h"
#include "ball.h"


ball::ball(int windowWidth, int windowHeight)
{
	//set screen edges
	leftEdge = 0;
	rightEdge = windowWidth;

	//set ball properties
	radius = 10;
	theBall.setRadius(radius);
	theBall.setFillColor(sf::Color::White);
	theBall.setOrigin(sf::Vector2f(radius, radius));
	theBall.setPosition(sf::Vector2f(windowWidth / 2, windowHeight / 2));
	movement = sf::Vector2f(0, 0.2);
}


void ball::update(sf::RenderWindow &window) {
	theBall.move(movement);
	window.draw(theBall);
}
