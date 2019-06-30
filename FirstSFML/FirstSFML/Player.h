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
	void stop();
	bool isMovingRight();
	bool isMovingLeft();
	


private:
	sf::RectangleShape paddle;
	sf::Vector2f movement;
	bool movingRight = false;
	bool movingLeft = false;
	float rightEdge;
	float leftEdge;
	float paddleWidth;
};

