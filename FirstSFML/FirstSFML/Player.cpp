#include "pch.h"
#include "Player.h"


Player::Player(int playerNum, int windowHeight, int windowWidth)
{
	//Set paddle dimensions, position, and boundaries
	paddleWidth = 100;
	paddle.setSize(sf::Vector2f(paddleWidth, 15));
	paddle.setOrigin(sf::Vector2f(paddleWidth/2, 7.5));
	leftEdge = 0;
	rightEdge = windowWidth;

	//Set movement to 0 and angle to 0
	movement = sf::Vector2f(0, 0);
	angle = 0;
	angleToRotate = 0;

	//player 1
	if (playerNum == 1) {
		paddle.setFillColor(sf::Color::Blue);
		paddle.setPosition(sf::Vector2f(100, windowHeight - 30));
	}
	else {
		paddle.setFillColor(sf::Color::Red);
		paddle.setPosition(sf::Vector2f(100, 30));
	}
}

void Player::update(sf::RenderWindow &window) {
	//Make sure paddle is within screen edges
	//Check moving right
	if (movingRight) {
		if (paddle.getPosition().x < rightEdge - paddleWidth / 2) {
			paddle.move(movement);
		}
	}
	//Check moving left
	else if (movingLeft) {
		if (paddle.getPosition().x > leftEdge + paddleWidth / 2) {
			paddle.move(movement);
		}
	}

	//Update rotation
	if (rotatingLeft) {
		if (angle > -45) {
			angle += angleToRotate;
			paddle.rotate(angleToRotate);
		}
	}
	else if (rotatingRight) {
		if (angle < 45) {
			angle += angleToRotate;
			paddle.rotate(angleToRotate);
		}
	}
	
	window.draw(paddle);
}

void Player::moveLeft() {
	movement.x = -0.5;
	movingLeft = true;
	movingRight = false;
}

void Player::moveRight() {
	movement.x = 0.5;
	movingRight = true;
	movingLeft = false;
}

void Player::rotateRight() {
	angleToRotate = 0.1;
	rotatingRight = true;
	rotatingLeft = false;
}

void Player::rotateLeft() {
	angleToRotate = -0.1;
	rotatingLeft = true;
	rotatingRight = false;
}

void Player::stopMoving() {
	movement.x = 0;
	movingLeft = false;
	movingRight = false;
}

void Player::stopRotating() {
	angleToRotate = 0;
	rotatingLeft = false;
	rotatingRight = false;
}

bool Player::isMovingRight() {
	return movingRight;
}

bool Player::isMovingLeft() {
	return movingLeft;
}

bool Player::isRotatingLeft() {
	return rotatingLeft;
}

bool Player::isRotatingRight() {
	return rotatingRight;
}

sf::RectangleShape Player::getPaddle() {
	return paddle;
}

float Player::getAngleRadians() {
	return angle * 3.14159 / 180;
}



