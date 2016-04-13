#include "System.h"
#include "WindowLib.h"

int main()
{
	sf::RenderWindow tWindow(sf::VideoMode(600, 600), "SFML works!");
	window = &tWindow;

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
	window = nullptr;
	return 0;
}