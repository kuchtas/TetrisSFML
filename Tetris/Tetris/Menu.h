#ifndef _MENU_H_
#define _MENU_H_
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"

class Menu
{
public:
	Menu();
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void start();

	sf::RenderWindow menuWindow;

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[NUMBER_OF_CHOICES];
};

#endif