#ifndef COLLISIONMAP_H
#define COLLISIONMAP_H

#include <sstream>
#include <string>
#include "SFML\Graphics.hpp"
#include "lua.hpp"
#include "WindowLib.h"

class CollisionMap : public sf::Transformable
{

private:
	int size;
	int tiles[];

public:
	CollisionMap();
	~CollisionMap();

	bool load(std::string filename);


};

#endif
