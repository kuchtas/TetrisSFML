#include "Point.h"
#include "Tetromino.h"
void Point::copy(Tetromino piece)
{
	this->x = piece.a[1].x;
	this->y = piece.a[1].y;
}