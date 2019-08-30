#include "pch.h"
#include "ball.h"
#include <iostream>
#include "game.h"


ball::ball(int setWindowWidth, int setWindowHeight, sf::Clock* getClock)
{
	//set screen edges
	leftEdge = 0;
	rightEdge = setWindowWidth;
	windowWidth = setWindowWidth;
	windowHeight = setWindowHeight;

	//set ball properties
	radius = 10;
	theBall.setRadius(radius);
	theBall.setFillColor(sf::Color::White);
	theBall.setOrigin(sf::Vector2f(radius, radius));
	theBall.setPosition(sf::Vector2f(windowWidth / 2, windowHeight / 2));
	movement = sf::Vector2f(-0.3, 0.1);
	movementModifier = 1;
	
	//set last player hit to player 2 (ball starts towards player 1)
	lastPlayerHit = 2;

	//set hitCount to 1
	hitCount = 1;

	//Set clock
	gameClock = getClock;
}

void ball::update(sf::RenderWindow &window, Player &player1, Player &player2, game &theGame) {
	if (checkCollisions(player1, player2, theGame) && hitCount % 3 == 0) {
		movement.y *= 1.02;
		movement.x *= 1.02;
		
	}
	
	//Apply movement modifier from powers
	sf::Vector2f moveWithPower;
	moveWithPower.x = movement.x * movementModifier;
	moveWithPower.y = movement.y * movementModifier;

	//Check if powerUp has been applied for long enough
	if (gameClock->getElapsedTime().asSeconds() > 2) {
		unApplyPower();
	}

	theBall.move(moveWithPower);
	window.draw(theBall);
}

bool ball::checkCollisions(Player &player1, Player &player2, game &theGame) {
	//Keeps track of whether the ball has collided with a player
	bool playerCollision = false;

	//Check collisions with player1
	if (theBall.getGlobalBounds().intersects(player1.getPaddle().getGlobalBounds()) && lastPlayerHit == 2) {
		if (detailedCollisionCheck(player1)) {
			lastPlayerHit = 1;
			playerCollision = true;
			float newX = movement.x * cos(-player1.getAngleRadians()) - movement.y * sin(-player1.getAngleRadians());
			float newY = movement.x * sin(-player1.getAngleRadians()) + movement.y * cos(-player1.getAngleRadians());
			newY *= -1;
			movement.x = newX * cos(player1.getAngleRadians()) - newY * sin(player1.getAngleRadians());
			movement.y = newX * sin(player1.getAngleRadians()) + newY * cos(player1.getAngleRadians());
		}
	}
	//Check Collisions with player2
	else if (theBall.getGlobalBounds().intersects(player2.getPaddle().getGlobalBounds()) && lastPlayerHit == 1) {
		if (detailedCollisionCheck(player2)) {
			lastPlayerHit = 2;
			playerCollision = true;
			float newX = movement.x * cos(-player2.getAngleRadians()) - movement.y * sin(-player2.getAngleRadians());
			float newY = movement.x * sin(-player2.getAngleRadians()) + movement.y * cos(-player2.getAngleRadians());
			newY *= -1;
			movement.x = newX * cos(player2.getAngleRadians()) - newY * sin(player2.getAngleRadians());
			movement.y = newX * sin(player2.getAngleRadians()) + newY * cos(player2.getAngleRadians());
		}
	}

	//If ball hit player, increment hit count (to determine ball speed increase)
	if (playerCollision) {
		hitCount++;
	}

	//Check collisions with walls
	if (theBall.getPosition().x < leftEdge + radius ||
		theBall.getPosition().x > rightEdge - radius) {
		movement.x = movement.x * (-1);
	}

	//Check ball out of bounds
	if (theBall.getPosition().y < 0){
		theGame.gameState = win;
		player1.win();
	}
	else if (theBall.getPosition().y > windowHeight) {
		theGame.gameState = win;
		player2.win();
	}

	return playerCollision;
}

bool ball::detailedCollisionCheck(Player player) {
	//Define rotation of paddle counterclockwise in radians
	float rotation = (360 - player.getPaddle().getRotation())*3.14159/180;

	//Define position of origin of paddle
	float paddleX = player.getPaddle().getPosition().x;
	float paddleY = player.getPaddle().getPosition().y;

	//Store x and y coordinates of left and right side of paddle
	float rightX;
	float rightY;
	float leftX;
	float leftY;

	//Get X and Y of right and left side of paddle without accounting for rotation
	if (player.getPlayerNum() == 1) {
		rightX = paddleX + player.getPaddleWidth() / 2;
		rightY = paddleY - 7.5;
		leftX = paddleX - player.getPaddleWidth() / 2;
		leftY = paddleY - 7.5;
	}
	else {
		rightX = paddleX + player.getPaddleWidth() / 2;
		rightY = paddleY + 7.5;
		leftX = paddleX - player.getPaddleWidth() / 2;
		leftY = paddleY + 7.5;
	}
	//Account for rotation
	rightY = rightY * cos(rotation) - rightX * sin(rotation);
	rightX = rightY * sin(rotation) + rightX * cos(rotation);
	leftY = leftY * cos(rotation) - leftX * sin(rotation);
	leftX = leftY * sin(rotation) + leftX * cos(rotation);

	//calc slope of padle
	float slope = (rightY - leftY) / (rightX - leftX);

	//Check collision with ball

	//Get position of ball with respect to center of paddle
	float ballX = theBall.getPosition().x - paddleX;
	float ballY = theBall.getPosition().y - paddleY;

	//Calculate where ball should be if colliding
	float expectedY;
	if (player.getPlayerNum() == 1) {
		expectedY = (slope * ballX) + 7.5;
		if ((ballY + 25) > expectedY - 5 && (ballY + 25) < expectedY + 5) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		expectedY = (slope * ballX) - 7.5;
		if ((ballY - 25) > expectedY - 5 && (ballY - 25) < expectedY + 5) {
			return true;
		}
		else {
			return false;
		}
	}
}

int ball::getHitCount() {
	return hitCount;
}

int ball::getLastPlayerHit() {
	return lastPlayerHit;
}

void ball::applyPower(string power) {
	if (power == "slow") {
		movementModifier = 0.3;
	}
	else if (power == "fast") {
		movementModifier = 1.5;
	}
	gameClock->restart();
}

void ball::unApplyPower() {
	movementModifier = 1;
}

void ball::reset() {
	//Set position and movement vector
	theBall.setPosition(sf::Vector2f(windowWidth / 2, windowHeight / 2));
	movement = sf::Vector2f(-0.3, 0.1);
	movementModifier = 1;

	//set last player hit to player 2 (ball starts towards player 1)
	lastPlayerHit = 2;

	//set hitCount to 1
	hitCount = 1;
}
