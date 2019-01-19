#include "Menu.h"

Menu::Menu(): menuWindow(sf::VideoMode(WIDTH, HEIGHT), "Tetris", sf::Style::Titlebar | sf::Style::Close)
{
	try
	{
		font.loadFromFile("arial.ttf");
	}
	catch (sf::Font font)
	{

	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[0].setPosition(sf::Vector2f(WIDTH / 3+30, HEIGHT / 4));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("EXIT");
	menu[1].setPosition(sf::Vector2f(WIDTH / 3+30, HEIGHT / 3));

	selectedItemIndex = 0;
}

Menu::~Menu()
{
	menuWindow.close();
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < NUMBER_OF_CHOICES; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < NUMBER_OF_CHOICES)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
int  Menu::GetPressedItem() 
{
	return selectedItemIndex;
}

void Menu::start()
{
	while (menuWindow.isOpen())
	{
		sf::Event event;
		while (menuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					menuWindow.close();
					break;

				case sf::Keyboard::Up:
					MoveUp();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					break;

				case sf::Keyboard::Enter:
					switch (GetPressedItem())
					{
					case 0:
					{
						srand(time(NULL));
						Game game;
						game.run();
					}
					break;

					case 1:
						menuWindow.close();
						break;
					}
					break;
				}

				break;
			case sf::Event::Closed:
				menuWindow.close();

				break;

			}
		}
		menuWindow.clear(sf::Color::Black);
		draw(menuWindow);
		menuWindow.display();
	}
}