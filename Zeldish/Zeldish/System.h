#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include "lua.hpp"
#include "SFML\Graphics.hpp"

class System : public sf::Drawable
{
private:	//Variables
	sf::CircleShape *Circle;
	sf::RenderWindow* window;
	lua_State* luaState;
public:
	System();
	virtual ~System();
	
	int Initialize(sf::RenderWindow* window);
	int HandleInput();
	int Update(float dT);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:	//Functions

};

#endif