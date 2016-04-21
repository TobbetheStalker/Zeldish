#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include <iostream>
#include "lua.hpp"

class BoundingVolume
{
private:
	float m_x, m_y;
	int m_width, m_height;
public:
	BoundingVolume();
	~BoundingVolume();
	void ShutDown();
	int Initialize(float x, float y, int width, int height);

	int SetPosition(float x, float y);

	int CheckAgainst(BoundingVolume* other);
};


int BoundingVolume_initialize(lua_State* ls);

int BoundingVolume_create(lua_State* ls);

int BoundingVolume_CheckAgainst(lua_State* ls);

int BoundingVolume_setPosition(lua_State* ls);

int BoundingVolume_destroy(lua_State* ls);

void RegisterBoundingVolume(lua_State * ls);

#endif