#include "CollisionGround.h"

CollisionGround::CollisionGround()
{
	this->size = 32 * 32;
	this->tiles[size];

	for (int i = 0; i < this->size; i++) {
		this->tiles[i] = 0;
	}

}

CollisionGround::~CollisionGround()
{

}

bool CollisionGround::load()
{

}