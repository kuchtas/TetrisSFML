#ifndef _BOARD_H
#define _BOARD_H_

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Tetromino.h"
class Board
{
private:
	int field[HEIGHT][WIDTH] = {0};
public:
	Board();
	~Board();
};

#endif