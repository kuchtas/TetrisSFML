#ifndef _TETROMINO_H
#define _TETROMINO_H_
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Constants.h"
class Tetromino : public sf::Drawable, public sf::Transformable
{
private:
	sf::RectangleShape block;

public:
	int figures[7][4] =
	{
		1,3,5,7, // I 0
		2,4,5,7, // Z 1
		3,5,4,6, // S 2
		3,5,4,7, // T 3
		2,3,5,7, // L 4
		3,5,7,6, // J 5
		2,3,4,5, // O 6
	};
	Tetromino();
	~Tetromino();
	int dx = 0;
	int rotate = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	Point a[4],b[4];

	void rotation(Point);
	void construct(int);
};
#endif