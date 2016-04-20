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

int System::Initialize()
{
	int result = 0;

	this->luaState = luaL_newstate();
	luaL_openlibs(this->luaState);

	RegisterMenu(this->luaState);
	RegisterInputChecker(this->luaState);
	RegisterTileMap(this->luaState);

	int error = luaL_loadfile(this->luaState, "LuaUpdate.lua")
		|| lua_pcall(this->luaState, 0, 0, 0);
	if (error) {
		std::cout << "Unable to run:" << lua_tostring(this->luaState, 1);
		lua_pop(this->luaState, 1);
	}

	lua_getglobal(this->luaState, "InitMenu");
	error = lua_pcall(this->luaState, 0, 1, 0);
	if (!error) {
		std::cout << "[C++] " << "Initialized Menu!" << std::endl;
	}
	else {
		std::cerr << lua_tostring(this->luaState, -1) << "\n";
	}

	lua_getglobal(this->luaState, "LoadTileMap");
	error = lua_pcall(this->luaState, 0, 1, 0);
	if (!error) {
		std::cout << "[C++] " << "Initialized TileMap!" << std::endl;
	}
	else {
		std::cerr << lua_tostring(this->luaState, -1) << "\n";
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
	lua_getglobal(this->luaState, "Update");
	int error = lua_pcall(this->luaState, 0, 2, 0);
	if (error) {
		std::cerr << lua_tostring(this->luaState, -1) << "\n";
	}
	result = lua_tonumber(this->luaState, -2);
	
	//Render
	//window->draw(*this->Circle);
	return result;
}

void System::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*this->Circle, states);
}