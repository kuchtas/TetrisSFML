#include "Game.h"
#include <iostream>

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
		case sf::Event::Closed: window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)	window.close();
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
	if (!board.check_collisions(piece))
	{
		for (int i = 0; i < 4; i++)
		{
			piece.a[i] = piece.b[i];
		}
	}
	////ROTATE////
	if (piece.rotate) //if up arrow has been pressed
	{
		Point point;
	//	copy(point,piece);
		point.copy(piece);
		piece.rotation(point);
		if (!board.check_collisions(piece))
		{	
			for (int i = 0; i < 4; i++)
			{
				piece.a[i] = piece.b[i];
			}
		}
	}
	/////TICK/////
	if (timer > delay) //the piece changes it's position after set amount of time
	{
		piece.lower(); //makes the Tetromino go down by one block 
		if (!board.check_collisions(piece)) 
		{
			for (int i = 0; i < 4; i++)
			{
				board.field[piece.b[i].y][piece.b[i].x] = piece.colorNum; //piece places itself, we lose control over it
			}
			piece.create(); //we need to create a new Tetromino 
		}
		timer = 0; //reseting the timer since the Tetromino moved 
	}
	///////CHECKING THE LINES//////
	board.linecheck();
	/////////GAME OVER/////////
	board.gameover(piece);
		
	piece.dx = 0;
	piece.rotate = 0;	
	delay = 0.3;
}

void Game::render()
{
	window.clear(sf::Color::Black);

	for (int i = 0; i < HEIGHT_IN_BLOCKS; i++)
	{
		for (int j = 0; j < WIDTH_IN_BLOCKS; j++)
		{
			if (board.field[i][j] == 0) continue;
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