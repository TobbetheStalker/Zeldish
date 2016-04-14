#ifndef TILEMAP_H
#define TILEMAP_H

#include "SFML\Graphics.hpp"
#include "lua.hpp"

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


#endif