#pragma once
#include<SFML/Graphics.hpp>
#include "Player.h"

void handleGameInput(sf::Event input, Player &player1, Player &player2);

void handleMenuInput(sf::Event event, game &theGame, sf::RenderWindow &window);
