#ifndef _TETROMINO_H
#define _TETROMINO_H_
#include <SFML/Graphics.hpp>

class Tetromino : public sf::Drawable, public sf::Transformable
{
private:
	sf::RectangleShape block;

public:
	Tetromino();
	~Tetromino();
	int dx = 0;
	int rotate = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	struct Point
	{
		int x, y;
	} a[4], b[4];

	void rotation(Point);
};
#endif