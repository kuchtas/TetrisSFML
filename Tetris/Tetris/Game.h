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
	sf::Clock clock;
	float time;
	float timer = 0, delay = 0.6;
	int field[32][16] = { 0 }; //[M][N]

	void processEvents();
	void update();
	void render();


public:
	Point a[4],b[4];


	Game();
	~Game();
	void run();
	
	void copy(Point&, Tetromino);
	bool check();
};

#endif 