#ifndef COLLISIONMAP_H
#define COLLISIONMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include "SFML\Graphics.hpp"
#include "lua.hpp"
#include "WindowLib.h"

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
	int getTile(int index);
	void setTile(int value, int index);

};

#endif
