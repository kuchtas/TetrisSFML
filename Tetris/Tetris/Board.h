#ifndef _BOARD_H_
#define _BOARD_H_
#include "Constants.h"
#include "Tetromino.h"
class Board	//class responsible for all of the collisions on board, checking wheter the player has not lost or if filled a whole line and such
{
public:
	Board();
	~Board();
	int field[HEIGHT_IN_BLOCKS][WIDTH_IN_BLOCKS] = { 0 };

	void linecheck();
	void gameover(Tetromino);
	bool check_collisions(Tetromino);
};

#endif 