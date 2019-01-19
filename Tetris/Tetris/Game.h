#ifndef _GAME_H_
#define _GAME_H_
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Tetromino.h"
#include "Point.h"
#include "Board.h"
#include "Score.h"
	
class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;
	Tetromino piece;
	Board board;
	Score score;
	float time;
	float timer = 0, delay = 0.5;
	bool lost = false;

	void processEvents();
	void update();
	void render();

public:
	Point a[4],b[4];

	Game();
	~Game();
	void run();
};

#endif 