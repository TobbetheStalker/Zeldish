#include "lua.hpp"
#include <iostream>
#include "System.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	window.setFramerateLimit(60);

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