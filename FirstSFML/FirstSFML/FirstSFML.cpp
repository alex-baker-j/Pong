
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "inputHandler.h"
#include "ball.h"


using namespace std;

int main(){

	//Define window size
	const int windowHeight = 600;
	const int windowWidth = 800;

	//Create players
	Player player1(1, windowHeight, windowWidth);
	Player player2(2, windowHeight, windowWidth);

	//Create ball
	ball gameBall(windowWidth, windowHeight);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Works");
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//Handle key inputs
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
				handleInput(event, player1, player2);
			}
		}
		window.clear();
		player1.update(window);
		player2.update(window);
		gameBall.update(window);
		window.display();
	}
}

