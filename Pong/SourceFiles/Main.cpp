
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "inputHandler.h"
#include "ball.h"
#include "game.h"
#include "slowBall.h"
#include"fastBall.h"


using namespace std;

int main(){

	//Timer for powerups
	sf::Clock powerClock;
	sf::Clock* powerClockPtr = &powerClock;

	//Create powerups for game
	slowBall slowPower;
	fastBall fastPower;

	//Define window size
	const int windowHeight = 600;
	const int windowWidth = 800;

	//Create players
	Player player1(1, windowHeight, windowWidth);
	Player player2(2, windowHeight, windowWidth);

	//Create ball
	ball gameBall(windowWidth, windowHeight, powerClockPtr);

	//State machine variable
	state gameState = start;

	//Create game
	game game(&player1, &player2, &gameBall, &slowPower, &fastPower, gameState, windowHeight, windowWidth);

	//Give players a reference to game object
	player1.setGame(&game);
	player2.setGame(&game);

	//Define render window
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong 2.0");
	
	//Main while loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//Handle key inputs for game
			else if (game.gameState == play) {
				if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
					handleGameInput(event, player1, player2);
				}
			}
			//Handle inputs for menu
			else if (game.gameState == start || game.gameState == win) {
				if (event.type == sf::Event::MouseButtonPressed) {
					handleMenuInput(event, game, window);
				}
			}
			
		}
		window.clear();
		if (game.gameState == start) {
			game.displayMenu(window);
		}
		else if (game.gameState == play) {
			player1.update(window);
			player2.update(window);
			gameBall.update(window, player1, player2, game);
			game.powerUps(window, gameBall, windowWidth, windowHeight);
		}
		else if (game.gameState == win) {
			game.displayWin(window);
		}
		else if (game.gameState == restart) {
			player1.reset();
			player2.reset();
			gameBall.reset();
			game.gameState = start;
		}
		
		window.display();
	}
}

