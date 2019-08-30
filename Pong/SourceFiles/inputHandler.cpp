#include "pch.h"
#include "inputHandler.h"
#include "game.h"
#include <iostream>

void handleGameInput(sf::Event input, Player &player1, Player &player2) {

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
		//Player 1 rotate right
		else if (input.key.code == sf::Keyboard::W) {
			player1.rotateRight();
		}
		//Player 1 rotate left
		else if (input.key.code == sf::Keyboard::S) {
			player1.rotateLeft();
		}
		//Player 1 use power
		else if (input.key.code == sf::Keyboard::LShift) {
			player1.usePower();
		}
		//Player 2 left
		else if (input.key.code == sf::Keyboard::J) {
			player2.moveLeft();
		}
		//Player 2 right
		else if (input.key.code == sf::Keyboard::L) {
			player2.moveRight();
		}
		//Player 2 rotate right
		else if (input.key.code == sf::Keyboard::I) {
			player2.rotateRight();
		}
		//Player 2 rotate left
		else if (input.key.code == sf::Keyboard::K) {
			player2.rotateLeft();
		}
		//Player 2 use power
		else if (input.key.code == sf::Keyboard::RShift) {
			player2.usePower();
		}

	}

	//Handle key releases
	else if (input.type == sf::Event::KeyReleased) {
		//Player 1 stops when moving left
		if (input.key.code == sf::Keyboard::A) {
			if (player1.isMovingLeft()) {
				player1.stopMoving();
			}
		}
		//Player 1 stops when moving right
		else if (input.key.code == sf::Keyboard::D) {
			if (player1.isMovingRight()) {
				player1.stopMoving();
			}
		}
		//Player 1 stops when rotating right
		else if (input.key.code == sf::Keyboard::W) {
			if (player1.isRotatingRight()) {
				player1.stopRotating();
			}
		}
		//Player1 stops when rotating left
		else if (input.key.code == sf::Keyboard::S) {
			if (player1.isRotatingLeft()) {
				player1.stopRotating();
			}
		}
		//Player 2 stops when moving left
		else if (input.key.code == sf::Keyboard::J) {
			if (player2.isMovingLeft()) {
				player2.stopMoving();
			}
		}
		//Player 2 stops when moving right
		else if (input.key.code == sf::Keyboard::L) {
			if (player2.isMovingRight()) {
				player2.stopMoving();
			}
		}
		//Player 2 stops when rotating right
		else if (input.key.code == sf::Keyboard::I) {
			if (player2.isRotatingRight()) {
				player2.stopRotating();
			}
		}
		//Player2 stops when rotating left
		else if (input.key.code == sf::Keyboard::K) {
			player2.stopRotating();
		}
	}

}

void handleMenuInput(sf::Event event, game &theGame, sf::RenderWindow &window) {
	if (theGame.gameState == start) {
		if (theGame.getPlayButton()->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			theGame.gameState = play;
		}
	}
	else if (theGame.gameState == win) {
		theGame.gameState = restart;
	}
	
}