#include "TileMap.h"
TileMap::TileMap()
{

}

TileMap::~TileMap()
{

}


bool TileMap::load(const std::string & tileSet, sf::Vector2u tileSize, const int * tiles, unsigned int width, unsigned int height)
{
	std::string path = "..\\Zeldish\\Resources\\TileSets\\" + tileSet;
	//Load the tileSt texture
	if (!this->tileSet.loadFromFile(path)) {
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

			int dX, dY;
			dX = window->getSize().x / width;
			dY = window->getSize().y / height;

			//defines its 4 corners
			quad[0].position = sf::Vector2f(i * dX, j * dY);	//Uper Left
			quad[1].position = sf::Vector2f((i + 1) * dX, j * dY);	//Uper Right
			quad[2].position = sf::Vector2f((i + 1) * dX, (j + 1) * dY);	//Lower right
			quad[3].position = sf::Vector2f(i * dX, (j + 1) * dY);	//Lower Left//defines its 4 corners
			//quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);	//Uper Left
			//quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);	//Uper Right
			//quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);	//Lower right
			//quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);	//Lower Left

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

TileMap* checkTileMap(lua_State* ls, int n)
{
	TileMap* tileMapPtr = nullptr;

	void* ptr = luaL_testudata(ls, n, "MetaTileMap");

	if (ptr != nullptr) {
		tileMapPtr = *(TileMap**)ptr;
	}

	return tileMapPtr;
}

int tileMap_create(lua_State* ls)
{
	TileMap** tileMap = reinterpret_cast<TileMap**>(lua_newuserdata(ls, sizeof(TileMap*)));

	*tileMap = new TileMap();

	luaL_getmetatable(ls, "MetaTileMap");
	lua_setmetatable(ls, -2);

	std::cout << "[C++] Created TileMap\n";

	return 1;
}

int tileMap_load(lua_State* ls)
{
	TileMap* tileMapPtr = checkTileMap(ls, 1);
	std::string tileSet = lua_tostring(ls, 2);
	sf::Vector2u tileSize = sf::Vector2u(lua_tonumber(ls, 3), lua_tonumber(ls, 4));
	
	unsigned int width = lua_tointeger(ls, 5);
	unsigned int height = lua_tointeger(ls, 6);
	
	const int size = 32 * 32;
	int tiles[size];
	int count = 0;
	lua_pushnil(ls);
	
	while (lua_next(ls,-2)) {
		
		if (lua_isnumber(ls, -1) ){
			tiles[count] = (int)lua_tointeger(ls,  -1);
		}

		lua_pop(ls, 1);

		count++;
	}
	lua_pop(ls, 1);

	if (tileMapPtr->load(tileSet, tileSize, tiles, width, height)){
		std::cout << "[C++] Loaded the tileMap\n";
	}
	else {
		std::cout << "[C++] Could not load the tileMap\n";
	}

	return 0;
}

int tileMap_draw(lua_State* ls)
{
	TileMap* tileMap = checkTileMap(ls, 1);
	window->draw(*tileMap);

	return 0;
}

int tileMap_destroy(lua_State* ls)
{
	TileMap* tileMap = checkTileMap(ls, 1);
	
	delete tileMap;

	return 0;
}


void RegisterTileMap(lua_State* ls)
{
	// Create a luaL metatable. This metatable is not 
	// exposed to Lua. The "luaL_Foo" label is used by luaL
	// internally to identity things.
	luaL_newmetatable(ls, "MetaTileMap");
	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metamenu"   |-1


	luaL_Reg sTileMapRegs[] =
	{
		{ "New",			tileMap_create },
		{ "Load",			tileMap_load },
		{ "Draw",			tileMap_draw },
		{ "__gc",			tileMap_destroy },
		{ NULL, NULL }
	};

	// Register the C functions _into_ the metatable we just created.
	luaL_setfuncs(ls, sTileMapRegs, 0);

	lua_pushvalue(ls, -1);

	// The Lua stack at this point looks like this:
	//     
	//     2| metatable "Metamenu"   |-1
	//     1| metatable "Metamenu"   |-2

	// Set the "__index" field of the metatable to point to itself
	// This pops the stack
	lua_setfield(ls, -1, "__index");

	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metamenu"   |-1

	// The luaL_Foo metatable now has the following fields
	//     - __gc
	//     - __index
	//     - add
	//     - print
	//     - new

	// Now we use setglobal to officially expose the luaL_Foo metatable 
	// to Lua. And we use the name "menu".
	//
	// This allows Lua scripts to _override_ the metatable of menu.
	// For high security code this may not be called for but 
	// we'll do this to get greater flexibility.
	lua_setglobal(ls, "TileMap");
}


