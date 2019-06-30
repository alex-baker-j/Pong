#include "pch.h"
#include "ball.h"
#include <iostream>


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
	movement = sf::Vector2f(-0.3, 0.4);
}

void ball::update(sf::RenderWindow &window, Player &player1, Player &player2) {
	checkCollisions(player1, player2);
	theBall.move(movement);
	window.draw(theBall);
}

void ball::checkCollisions(Player &player1, Player &player2) {
	//Check collisions with player1
	if (theBall.getGlobalBounds().intersects(player1.getPaddle().getGlobalBounds())) {
		float newX = movement.x * cos(-player1.getAngleRadians()) - movement.y * sin(-player1.getAngleRadians());
		float newY = movement.x * sin(-player1.getAngleRadians()) + movement.y * cos(-player1.getAngleRadians());
		newY *= -1;
		movement.x = newX * cos(player1.getAngleRadians()) - newY * sin(player1.getAngleRadians());
		movement.y = newX * sin(player1.getAngleRadians()) + newY * cos(player1.getAngleRadians());
	}
	//Check Collisions with player2
	else if (theBall.getGlobalBounds().intersects(player2.getPaddle().getGlobalBounds())) {
		float newX = movement.x * cos(-player2.getAngleRadians()) - movement.y * sin(-player2.getAngleRadians());
		float newY = movement.x * sin(-player2.getAngleRadians()) + movement.y * cos(-player2.getAngleRadians());
		newY *= -1;
		movement.x = newX * cos(player2.getAngleRadians()) - newY * sin(player2.getAngleRadians());
		movement.y = newX * sin(player2.getAngleRadians()) + newY * cos(player2.getAngleRadians());
	}

	//Check collisions with walls
	if (theBall.getPosition().x < leftEdge + radius ||
		theBall.getPosition().x > rightEdge - radius) {
		movement.x = movement.x * (-1);
	}
}
