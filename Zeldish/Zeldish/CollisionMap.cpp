#include "CollisionMap.h"

CollisionMap::CollisionMap()
{
	this->size = 32 * 32;
	this->tiles[size];

	for (int i = 0; i < this->size; i++) {
		this->tiles[i] = 0;
	}

}

CollisionMap::~CollisionMap()
{

}

bool CollisionMap::load(std::string filename)
{

	return true;
}