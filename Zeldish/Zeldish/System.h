#ifndef SYSTEM_H
#define SYSTEM_H

#include "Menu.h"
#include "InputChecker.h"
#include "TileMap.h"

class System : public sf::Drawable
{
private:	//Variables
	sf::CircleShape *Circle;
	lua_State* luaState;
public:
	System();
	virtual ~System();
	
	int Initialize();
	int HandleInput();
	int Update(float dT);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:	//Functions

};

#endif