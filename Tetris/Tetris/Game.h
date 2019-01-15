#ifndef _GAME_H
#define _GAME_H_
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Tetromino.h"
class Game
{
private:
	sf::RenderWindow window;
	Tetromino piece;
	void processEvents();
	void update();
	void render();

public:
	struct Point
	{
		int x, y;
	} a[4], b[4];

	Game();
	~Game();
	void run();
	int figures[7][4] =
	{
		1,3,5,7, // I
		2,4,5,7, // Z
		3,5,4,6, // S
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
	};

	
	void copy(Point&, Tetromino);
};

#endif 