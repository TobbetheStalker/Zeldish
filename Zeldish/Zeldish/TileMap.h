#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>
#include "SFML\Graphics.hpp"
#include "lua.hpp"
#include "WindowLib.h"

class TileMap : public sf::Drawable, sf::Transformable {

private:
	sf::Texture tileSet;
	sf::VertexArray vertices;

public:
	TileMap();
	~TileMap();

	bool load(const std::string& tileSet, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

int tileMap_create(lua_State* ls);

int tileMap_load(lua_State* ls);

int tileMap_draw(lua_State* ls);

void RegisterTileMap(lua_State* ls);


#endif