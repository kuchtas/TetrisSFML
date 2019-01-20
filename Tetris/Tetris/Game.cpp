#include "Game.h"
Game::Game(): window(sf::VideoMode(WIDTH, HEIGHT), "Tetris",sf::Style::Titlebar|sf::Style::Close)
{
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(true);
	try
	{
		font.loadFromFile("ARCADECLASSIC.ttf");
	}
	catch (sf::Font font)
	{
	}
}

Game::~Game()
{
	window.close();
}

void Game::GameOver(sf::Font font, sf::Text GameOver) //GAME OVER SCREEN
{
	window.clear(sf::Color::Black);

	GameOver.setFont(font);
	GameOver.setCharacterSize(30);
	GameOver.setPosition(WIDTH/13.5 , HEIGHT / 4);
	GameOver.setString("\nYour  score  has  been\n    saved  to  the  file!\n       Maybe  try  again\n\n         Press  Enter  to\n       go  back  to  menu!");
	window.draw(GameOver);
	window.display();
}

void Game::run()
{
	while (window.isOpen())
	{
		if(!lost) processEvents();
		if(!lost) update();
		else
		{
			GameOver(font, GameOverText);
			lost = true;
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:

					if (event.key.code == sf::Keyboard::Enter)
					{
						lost = false;
						score.streamscore();
						score.resetscore();
						window.close();
					}	
					break;
				}
			}
		}
		if(!lost) render();
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

		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
			{
				score.streamscore();
				window.close();
			}
			break;
		case sf::Event::KeyPressed:
			{
			if (event.key.code == sf::Keyboard::Up)		piece.rotate = true;
			if (event.key.code == sf::Keyboard::Right)	piece.dx = 1;
			if (event.key.code == sf::Keyboard::Left)	piece.dx = -1;
			break;
			}
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
	board.linecheck(score);

	/////////GAME OVER/////////
	if (!board.gameover(piece))
	{
		lost = true;
	}
		
	piece.dx = 0; //move only once per registered press
	piece.rotate = 0;	//rotate only once per registered press
	delay = 0.5; //set the delay back to initial value
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