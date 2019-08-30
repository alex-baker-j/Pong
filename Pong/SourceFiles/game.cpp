#include "pch.h"
#include "game.h"
#include "ball.h"
#include "slowBall.h"
#include "fastBall.h"

game::game(Player* player1set, Player* player2set, ball* theBall, slowBall* slowInput, fastBall* fastInput, state initialState, float windowHeightSet, float windowWidthSet){
	player1 = player1set;
	player2 = player2set;
	gameBall = theBall;
	fastPower = fastInput;
	slowPower = slowInput;
	gameState = initialState;
	windowHeight = windowHeightSet;
	windowWidth = windowWidthSet;

	//Menu stuff
	playButton.setSize(sf::Vector2f(400, 110));
	playButton.setOrigin(200, 55);
	playButton.setPosition(windowWidth / 2, windowHeight / 2);
	playButton.setFillColor(sf::Color::Blue);
	playFont.loadFromFile("Textures/Roboto.ttf");
	playText.setFont(playFont);
	playText.setPosition(playButton.getPosition().x - 180, playButton.getPosition().y - 50);
	playText.setString("Click to Play");
	playText.setCharacterSize(65);
	winText.setFont(playFont);
	winText.setPosition(windowWidth / 2 - 180, windowHeight / 2 - 50);
	winText.setCharacterSize(65);
}

void game::powerUps(sf::RenderWindow &window, ball &theBall, int windowWidth, int windowHeight) {
	
	//Every 7th hit and there is no current power up, enable a random powerup
	if (theBall.getHitCount() % 4 == 0 && !alreadyPowerUp) {
		random_device rd;
		int random = rd() % 2;
		if (random == 1) {
			slowPower->setState("activated");
			slowPower->setLocation(windowWidth, windowHeight);
		}
		else {
			fastPower->setState("activated");
			fastPower->setLocation(windowWidth, windowHeight);
		}
		alreadyPowerUp = true;
	}

	//if fastpower is activated but not acquired, check for collisions with ball
	if (fastPower->getState() == "activated") {
		if (theBall.theBall.getGlobalBounds().intersects(fastPower->item.getGlobalBounds())) {
			fastPower->setState("acquired");
			if (theBall.getLastPlayerHit() == 1) {
				//player1->setPowerUp("slowBall");
				player1->setPowerUp("fastBall");
			}
			else {
				//player2->setPowerUp("slowBall");
				player2->setPowerUp("fastBall");
			}
			alreadyPowerUp = false;
		}
		window.draw(fastPower->item);
	}
	//if slowpower is activated but not acquired
	else if (slowPower->getState() == "activated") {
		if (theBall.theBall.getGlobalBounds().intersects(slowPower->item.getGlobalBounds())) {
			slowPower->setState("acquired");
			if (theBall.getLastPlayerHit() == 1) {
				player1->setPowerUp("slowBall");
			}
			else {
				player2->setPowerUp("slowBall");
			}
			alreadyPowerUp = false;
		}
		window.draw(slowPower->item);
	}
}

bool game::getAlreadyPowerUp() {
	return alreadyPowerUp;
}

void game::activatePowerUp(string powerUp) {
	if (powerUp == "slowBall") {
		gameBall->applyPower("slow");
	}
	else if (powerUp == "fastBall") {
		gameBall->applyPower("fast");
	}
}

void game::displayMenu(sf::RenderWindow &window) {
	window.draw(playButton);
	window.draw(playText);
}

sf::RectangleShape* game::getPlayButton() {
	return &playButton;
}

void game::displayWin(sf::RenderWindow &window) {
	if (player1->getWin()) {
		winText.setString("Player 1 wins!");
	}
	else {
		winText.setString("Player 2 wins!");
	}
	window.draw(winText);
}

