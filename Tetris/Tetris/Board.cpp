#include "Board.h"
#include <iostream>

Board::Board()
{
}


Board::~Board()
{
}

void Board::linecheck(Score& score)
{
	int k = HEIGHT_IN_BLOCKS - 1;
	for (int i = HEIGHT_IN_BLOCKS - 1; i > 0; i--)	//going through every row starting from the bottom
	{
		int count = 0;
		for (int j = 0; j < WIDTH_IN_BLOCKS; j++)	//going through every collumn starting from the left
		{
			if (field[i][j]) count++;	//if a block is occupied we add one to the counter
			if (count == WIDTH_IN_BLOCKS) score.addtoscore(); //player scores points for completing a full row
			field[k][j] = field[i][j];
			
		}
		if (count < WIDTH_IN_BLOCKS) k--;
	}
}

bool Board::gameover(Tetromino piece)
{
	for (int i = 0; i < 4; i++)
	{
		if (field[piece.a[i].y][piece.a[i].x])//if any block is inside another the player has lost
		{
			return 0;
		}
	}
	return 1;
}

bool Board::check_collisions(Tetromino piece)	//this functions checks if we are not outside of the game bounds or inside another block
{
	for (int i = 0; i < 4; i++)
	{
		if (piece.a[i].x < 0 || piece.a[i].x >= WIDTH_IN_BLOCKS || piece.a[i].y >= HEIGHT_IN_BLOCKS) return 0;
		else if (field[piece.a[i].y][piece.a[i].x]) return 0;
	}
	return 1;
}