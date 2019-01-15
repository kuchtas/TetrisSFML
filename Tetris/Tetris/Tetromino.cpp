#include "Tetromino.h"

Tetromino::Tetromino()
{
	block.setSize(sf::Vector2f(50, 50));
	block.setFillColor(sf::Color::Blue);
}

Tetromino::~Tetromino()
{
}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const // the drawing of the ship
{
	states.transform *= getTransform();
	target.draw(block, states);
}

void Tetromino::rotation(Point rotationpoint)
{
	
}