#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class ball
{
public:
	ball(int setWindowWidth, int setWindowHeight, sf::Clock* clock);
	sf::CircleShape theBall;
	void update(sf::RenderWindow &window, Player &player1, Player &player2, game &theGame);
	int getHitCount();
	int getLastPlayerHit();
	void applyPower(string power);
	void unApplyPower();
	void reset();

private:
	bool detailedCollisionCheck(Player player);
	sf::Clock* gameClock;
	float leftEdge;
	float rightEdge;
	float radius;
	sf::Vector2f movement;
	bool checkCollisions(Player &player1, Player &player2, game &theGame);
	int lastPlayerHit;
	int hitCount;
	float movementModifier;
	float windowWidth;
	float windowHeight;
};

