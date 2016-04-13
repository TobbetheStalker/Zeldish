#include <SFML/Graphics.hpp>
#include "lua.hpp"
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int error = luaL_loadfile(L, "test.lua")
		|| lua_pcall(L, 0, 0, 0);
	if (error) {
		std::cout << "Unable to run:" << lua_tostring(L, 1);
		lua_pop(L, 1);
	}

	lua_getglobal(L, "date");
	error = lua_pcall(L, 0, 1, 0);
	if (!error) {
		std::cout << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}

	std::cout << std::endl;

	lua_getglobal(L, "date");
	error = lua_pcall(L, 0, 1, 0);
	if (!error) {
		std::cout << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}

	lua_close(L);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}