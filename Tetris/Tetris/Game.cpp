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
			if (event.key.code == sf::Keyboard::Up)		piece.rotate = true;
				
			if (event.key.code == sf::Keyboard::Right)	piece.dx = 1;
				
			if (event.key.code == sf::Keyboard::Left)	piece.dx = -1;
			
			break;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;
	}
}
void Game::update()
{
	time= clock.getElapsedTime().asSeconds();
	clock.restart();
	timer += time;
	///////MOVE///////
	for (int i = 0; i < 4; i++)
	{
		piece.b[i] = piece.a[i];
		piece.a[i].x += piece.dx;
	}
	if (!check())
	{
		for (int i = 0; i < 4; i++)
		{
			piece.a[i] = piece.b[i];
		}
	}
	////ROTATE////
	if (piece.rotate)
	{
		Point point;
		copy(point,piece);
		piece.rotation(point);
		if (!check())
		{	
			for (int i = 0; i < 4; i++)
			{
				piece.a[i] = piece.b[i];
			}
		}
	}
	////TICK/////
	if (timer > delay)
	{
		for (int i = 0; i < 4; i++)
		{
			piece.b[i] = piece.a[i];	
			piece.a[i].y += 1;
		}
		if (!check())
		{
			for (int i = 0; i < 4; i++)
			{
				field[piece.b[i].y][piece.b[i].x] = piece.colorNum;
			}
			piece.colorNum = 1 + rand() % 7;
			int n = rand() % 7;
			piece.construct(n);
		}
		timer = 0;
	}
		
	piece.dx = 0;
	piece.rotate = 0;	
	delay = 0.3;
}

void Game::render()
{
	window.clear(sf::Color::Black);

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (field[i][j] == 0) continue;
			piece.setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
			window.draw(piece);
		}
	}


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

bool Game::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (piece.a[i].x < 0 || piece.a[i].x>=16 || piece.a[i].y >= 32) return 0;
		else if (field[piece.a[i].y][piece.a[i].x]) return 0;
	}
	return 1;
}