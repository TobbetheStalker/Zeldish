#include "TileMap.h"
TileMap::TileMap()
{
	this->vertices;
}

TileMap::~TileMap()
{

}


bool TileMap::load(const std::string & tileSet, sf::Vector2u tileSize, const int * tiles, unsigned int width, unsigned int height)
{

	//Load the tileSt texture
	if (!this->tileSet.loadFromFile(tileSet)) {
		return false;
	}

	//Re-size the vertex array 
	this->vertices.setPrimitiveType(sf::Quads);
	this->vertices.resize(width * height * 4);

	//Create the vertices, with one quad per tile
	for (int i = 0; i < width; i++) {

		for (int j = 0; j < height; j++) {

			//Tile number (in what order the texture is in the tileSet)
			int tileNr = tiles[i + j * width];

			//Find the tiles position
			int tu = tileNr % (this->tileSet.getSize().x / tileSize.x);
			int tv = tileNr / (this->tileSet.getSize().x / tileSize.x);

			//Get the pointer to the current tile's quad
			sf::Vertex* quad = &this->vertices[(i + j *width) *4];

			//defines its 4 cornners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);	//Uper Left
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);	//Uper Right
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);	//Lower right
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);	//Lower Left

			//define its 4 texture coords
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);	//Uper Left
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);	//Uper Left
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);	//Uper Left
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);	//Uper Left


		}

	}

	return true;

}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//Apply transformation
	states.transform *= this->getTransform();

	//Apply the tileSet texture
	states.texture = &this->tileSet;

	//draw the vertex array
	target.draw(this->vertices, states);

}
