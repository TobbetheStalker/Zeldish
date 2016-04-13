#include "System.h"

System::System()
{
	this->Circle = new sf::CircleShape(100.0f);
	this->Circle->setFillColor(sf::Color::Green);
}


System::~System()
{
	lua_close(this->luaState);
	delete this->Circle;
	this->Circle = NULL;
}

int System::Initialize(sf::RenderWindow * window)
{
	int result = 0;
	this->window = window;

	this->luaState = luaL_newstate();
	luaL_openlibs(this->luaState);

	int error = luaL_loadfile(this->luaState, "test.lua")
		|| lua_pcall(this->luaState, 0, 0, 0);
	if (error) {
		std::cout << "Unable to run:" << lua_tostring(this->luaState, 1);
		lua_pop(this->luaState, 1);
	}

	return result;
}

int System::HandleInput()
{
	return 0;
}

int System::Update(float dT)
{
	int result = 0;

	//Update Content
	lua_getglobal(this->luaState, "date");
	int error = lua_pcall(this->luaState, 0, 1, 0);
	if (!error) {
		std::cout << lua_tostring(this->luaState, -1) << std::endl;
		lua_pop(this->luaState, 1);
	}

	std::cout << std::endl;

	//Render
	window->draw(*this->Circle);
	return result;
}

void System::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*this->Circle, states);
}
