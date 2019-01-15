#ifndef _GAME_H
#define _GAME_H_
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Tetromino.h"
#include "Point.h"
class Game
{
private:
	sf::RenderWindow window;
	Tetromino piece;
	void processEvents();
	void update();
	void render();

public:
	Point a[4],b[4];

	Game();
	~Game();
	void run();
	
	void copy(Point&, Tetromino);
};

#endif 