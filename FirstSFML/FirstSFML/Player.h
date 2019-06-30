#pragma once
#include<SFML/Graphics.hpp>

using namespace std;

class Player
{
public:
	Player(int playerNum, int windowHeight, int windowWidth);
	void update(sf::RenderWindow &window);
	void moveLeft();
	void moveRight();
	void rotateRight();
	void rotateLeft();
	void stopMoving();
	void stopRotating();
	bool isMovingRight();
	bool isMovingLeft();
	bool isRotatingRight();
	bool isRotatingLeft();
	sf::RectangleShape getPaddle();
	float getAngleRadians();
	


private:
	sf::RectangleShape paddle;
	sf::Vector2f movement;
	bool movingRight = false;
	bool movingLeft = false;
	bool rotatingRight = false;
	bool rotatingLeft = false;
	float rightEdge;
	float leftEdge;
	float paddleWidth;
	float angle;
	float angleToRotate;
};

