#ifndef COLLISIONGROUND_H
#define COLLISIONGROUND_H

#include <sstream>
#include <string>
#include "SFML\Graphics.hpp"
#include "lua.hpp"
#include "WindowLib.h"

class CollisionGround : public sf::Transformable
{

private:
	int size;
	int tiles[];

public:
	CollisionGround();
	~CollisionGround();

	bool load(std::string filename);


};

#endif
