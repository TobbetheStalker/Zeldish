#include <SFML/Graphics.hpp>
#include "System.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	System zeldish;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(zeldish);
		window.display();
	}

	return 0;
}