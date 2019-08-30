#include "pch.h"
#include "powerUp.h"


powerUp::powerUp()
{
	//Set item properties
	item.setRadius(25);
	item.setOrigin(sf::Vector2f(25, 25));
	state = "deactivated";
}

void powerUp::setLocation(int windowWidth, int windowHeight) {
	std::random_device rd;
	int x = rd() % windowWidth;
	int y = 80 + (rd() % (windowHeight - 130));
	item.setPosition(sf::Vector2f(x, y));
}

string powerUp::getState() {
	return state;
}

void powerUp::setState(string setState) {
	state = setState;
}


