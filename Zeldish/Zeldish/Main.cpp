#include "System.h"
#include "WindowLib.h"

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(600, 600), "SFML works!");

int main()
{
	window->setFramerateLimit(60);
	sf::Clock gameTimer;

	System zeldish;
	zeldish.Initialize();

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		zeldish.HandleInput();
		zeldish.Update(1.0f);
		window->display();
	}

	return 0;
}