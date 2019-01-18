#ifndef _POINT_H_
#define _POINT_H_
class Tetromino;
class Point
{
public:
	int x, y;

	void copy(Tetromino);
};
#endif 