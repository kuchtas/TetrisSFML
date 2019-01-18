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
	if (!check_collisions())
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
		copy(point,piece);
		piece.rotation(point);
		if (!check_collisions())
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
		if (!check_collisions()) 
		{
			for (int i = 0; i < 4; i++)
			{
				field[piece.b[i].y][piece.b[i].x] = piece.colorNum; //piece places itself, we lose control over it
			}
			piece.create(); //we need to create a new Tetromino 
		}
		timer = 0; //reseting the timer since the Tetromino moved 
	}
	///////CHECKING THE LINES//////
	linecheck();
	/////////GAME OVER/////////
	gameover();
		
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

void Game::copy(Point& point, Tetromino piece)	//function copies the rotation point for each type of Tetromino
{
	point.x = piece.a[1].x;
	point.y = piece.a[1].y;
}

bool Game::check_collisions()	//this functions checks if we are not outside of the game bounds or inside another block
{
	for (int i = 0; i < 4; i++)
	{
		if (piece.a[i].x < 0 || piece.a[i].x>=WIDTH_IN_BLOCKS || piece.a[i].y >= HEIGHT_IN_BLOCKS) return 0;
		else if (field[piece.a[i].y][piece.a[i].x]) return 0;
	}	
	return 1;
}

void Game::linecheck()
{
	int k = HEIGHT_IN_BLOCKS - 1; 
	for (int i = HEIGHT_IN_BLOCKS - 1; i > 0; i--)	//going through every row starting from the bottom
	{
		int count = 0;
		for (int j = 0; j < WIDTH_IN_BLOCKS; j++)	//going through every collumn starting from the left
		{
			if (field[i][j]) count++;	//if a block is occupied we add one to the counter
			field[k][j] = field[i][j];
		}
		if (count < WIDTH_IN_BLOCKS) k--;
	}
}

void Game::gameover()
{
	for (int i = 0; i < 4; i++)
	{
		if (field[piece.a[i].y][piece.a[i].x]) std::cout << "Game over"; //if any block is inside another the player has lost
	}
}