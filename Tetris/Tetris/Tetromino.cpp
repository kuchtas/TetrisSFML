#include "Tetromino.h"

Tetromino::Tetromino()
{
	block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
	block.setFillColor(sf::Color::Blue);
	construct(type);
}

Tetromino::~Tetromino()
{
}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const // 
{
	states.transform *= getTransform();
	target.draw(block, states);
}

void Tetromino::rotation(Point rotationpoint)
{
	for (int i = 0; i < 4; i++)
	{
		int x = a[i].y - rotationpoint.y;
		int y = a[i].x - rotationpoint.x;
		a[i].x = rotationpoint.x - x;
		a[i].y = rotationpoint.y + y;
	}
}

void Tetromino::construct(int n)
{
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
}

void Tetromino::create()
{
	colorNum = 1 + rand() % 7;
	int n = rand() % 7;
	while (n == type) n = rand() % 7;
	type = n;
	construct(type);
}

void Tetromino::lower()
{
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].y += 1;
	}
}