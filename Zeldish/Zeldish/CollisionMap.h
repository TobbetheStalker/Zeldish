#ifndef COLLISIONMAP_H
#define COLLISIONMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include "SFML\Graphics.hpp"
#include "lua.hpp"
#include "WindowLib.h"
#include "BoundingVolume.h"

class CollisionMap : public sf::Transformable
{

private:
	int width;
	int height;
	int size;
	int* tiles;

public:
	CollisionMap();
	~CollisionMap();

	bool Load(std::string filename);
	bool Save(std::string filename);
	int getTile(int indexX, int indexY);
	void setTile(int value, int indexX, int indexY);
	bool checkCollision(BoundingVolume* bv, int& correctionX, int& correctionY);

};
int collisionMap_create(lua_State* ls);

int collisionMap_load(lua_State* ls);

int collisionMap_save(lua_State* ls);

int collisionMap_destroy(lua_State* ls);

int collisionMap_set(lua_State* ls);

int collisionMap_get(lua_State* ls);

int collisionMap_checkCollision(lua_State* ls);

void RegisterCollisionMap(lua_State* ls);
#endif
