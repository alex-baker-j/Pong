#pragma once
#include "Player.h"


class ball;
class slowBall;
class fastBall;
enum state {
	start,
	play,
	win,
	restart
};


class game
{
public:
	game(Player* player1, Player* player2, ball* theBall, slowBall* slowPower, fastBall* fastPower, state initialState, float windowHeight, float windowWidth);
	void powerUps(sf::RenderWindow &window, ball &theBall, int windowWidth, int windowHeight);
	bool getAlreadyPowerUp();
	void activatePowerUp(string powerUp);
	void displayMenu(sf::RenderWindow &window);
	state gameState;
	sf::RectangleShape* getPlayButton();
	void displayWin(sf::RenderWindow &window);

private:
	//Game stuff
	Player* player1;
	Player* player2;
	slowBall* slowPower;
	fastBall* fastPower;
	bool alreadyPowerUp = false;
	ball* gameBall;
	float windowHeight;
	float windowWidth;

	//Menu stuff
	sf::Text playText;
	sf::Font playFont;
	sf::RectangleShape playButton;
	sf::Text winText;

};



