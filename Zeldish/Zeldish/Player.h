#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player :
	public Entity
{
private:	//Variables



public:
	Player();
	virtual ~Player();



private:	//Functions

};


int player_create(lua_State* ls);

int player_destroy(lua_State* ls);

int player_draw(lua_State* ls);

void RegisterPlayer(lua_State * ls);


#endif