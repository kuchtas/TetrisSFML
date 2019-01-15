#include "Game.h"


Game::Game(): window(sf::VideoMode(WIDTH, HEIGHT), "Tetris",sf::Style::Titlebar|sf::Style::Close)
{
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(true);
}

Game::~Game()
{
	window.close();
}

void Game::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.key.code == sf::Keyboard::Up)
				piece.rotate = true;
			if (event.key.code == sf::Keyboard::Right)
				piece.dx = 1;
			if (event.key.code == sf::Keyboard::Left)
				piece.dx = -1;
			break;
			
		}
	}
}
void Game::update()
{
	for (int i = 0; i < 4; i++)
		piece.a[i].x += piece.dx;

	if (piece.rotate)
	{
		Point point;// = piece.a[1]; //=a[1]; //center of rotation
		copy(point,piece);
		piece.rotation(point);
	}

	int n = 3;

	if (piece.a[0].x == 0)
	{
		piece.construct(n); // i dont know what it does XD
	}
		
	piece.dx = 0;
	piece.rotate = 0;	
}

void Game::render()
{
	window.clear(sf::Color::Black);

	for (int i = 0; i < 4; i++)
	{
		piece.setPosition(piece.a[i].x * BLOCK_SIZE, piece.a[i].y * BLOCK_SIZE);
		window.draw(piece);
	}

	window.display();
}

void Game::copy(Point& point, Tetromino piece)
{
	point.x = piece.a[1].x;
	point.y = piece.a[1].y;
}
