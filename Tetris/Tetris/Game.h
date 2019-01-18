#ifndef _GAME_H_
#define _GAME_H_
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Tetromino.h"
#include "Point.h"
#include "Board.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;
	Tetromino piece;
	Board board;
	float time;
	float timer = 0, delay = 0.6;

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