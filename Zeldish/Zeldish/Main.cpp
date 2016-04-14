#include "System.h"
#include "WindowLib.h"

int main()
{
	sf::RenderWindow tWindow(sf::VideoMode(600, 600), "SFML works!");
	window = &tWindow;

	sf::Clock gameTimer;


	System zeldish;
	int result = zeldish.Initialize();
	if (result == -1) {
		window->close();
	}

	while (window->isOpen())
	{
		InputChecker::Instance().UpdateInput();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed) {
				InputChecker::Instance().SetKeyPressed(event.key.code);
			}
			if (event.type == sf::Event::KeyReleased) {
				InputChecker::Instance().SetKeyReleased(event.key.code);
			}
		}
		
		window->clear();
		zeldish.HandleInput();
		zeldish.Update(1.0f);
		window->display();
	}

	//delete &InputChecker::Instance();
	window = nullptr;
	system("pause");
	return 0;
}