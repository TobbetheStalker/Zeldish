#include "System.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	window.setFramerateLimit(60);

	System zeldish;
	zeldish.Initialize(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		zeldish.Update(1.0f);
		window.display();
	}

	return 0;
}