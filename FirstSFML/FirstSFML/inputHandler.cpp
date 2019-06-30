#include "pch.h"
#include "inputHandler.h"

void handleInput(sf::Event input, Player &player1, Player &player2) {

	//Handle key presses
	if (input.type == sf::Event::KeyPressed) {
		//Player 1 left
		if (input.key.code == sf::Keyboard::A) {
			player1.moveLeft();
		}
		//Player 1 right
		else if (input.key.code == sf::Keyboard::D) {
			player1.moveRight();
		}
		//Player 2 left
		else if (input.key.code == sf::Keyboard::J) {
			player2.moveLeft();
		}
		//Player 2 right
		else if (input.key.code == sf::Keyboard::L) {
			player2.moveRight();
		}
	}

	//Handle key releases
	else if (input.type == sf::Event::KeyReleased) {
		//Player 1 stops when moving left
		if (input.key.code == sf::Keyboard::A) {
			if (player1.isMovingLeft()) {
				player1.stop();
			}
		}
		//Player 1 stops when moving right
		else if (input.key.code == sf::Keyboard::D) {
			if (player1.isMovingRight()) {
				player1.stop();
			}
		}
		
		//Player 2 stops when moving left
		else if (input.key.code == sf::Keyboard::J) {
			if (player2.isMovingLeft()) {
				player2.stop();
			}
		}
		//Player 2 stops when moving right
		else if (input.key.code == sf::Keyboard::L) {
			if (player2.isMovingRight()) {
				player2.stop();
			}
		}
	}

}