#include "CollisionMap.h"

CollisionMap::CollisionMap()
{
	this->width = 0;
	this->height = 0;
	this->size = 0;
	this->tiles = nullptr;

}

CollisionMap::~CollisionMap()
{
	if (this->tiles) {
		delete[] this->tiles;
	}
}

bool CollisionMap::Create(int width, int height)
{
	this->width = width;
	this->height = height;
	int size = width * height;
	this->tiles = new int[size];

	for (int i = 0; i < size; i++) {
		this->tiles[i] = 0;
	}

	return true;
}

bool CollisionMap::Load(std::string filename)
{
	std::string path = "..\\Zeldish\\Resources\\CollisionMaps\\" + filename + ".txt";
	std::ifstream readFile;
	int counter = 0;
	readFile.open(path);

	if (!readFile.is_open()) {
		std::cout << "[C++] Could not open file for reading" << std::endl;
		return false;
	}
	else {
		if (this->tiles) {
			delete[] this->tiles;
		}
		readFile >> this->width;
		readFile >> this->height;

		this->size = this->width * this->height;
		this->tiles = new int[this->size];
		for (int i = 0; i < this->size; i++)
			tiles[i] = 0;

		while (!readFile.eof() && counter < this->size) {

			readFile >> this->tiles[counter];
			counter++;

		}

		readFile.close();
	}


	return true;
}

bool CollisionMap::Save(std::string filename)
{
	std::string path = "..\\Zeldish\\Resources\\CollisionMaps\\" + filename + ".txt";
	std::ofstream writeFile;
	int counter = 0;
	writeFile.open(path);

	if (!writeFile.is_open()) {
		std::cout << "[C++] Could not open file for writing" << std::endl;
		return false;
	}
	else {
		writeFile << this->width << " " << this->height << " \r\n";

		for (int i = 0; i < this->height; i++) {

			for (int j = 0; j < this->width; j++) {
				writeFile << this->tiles[(i * this->width) + j] << " ";
			}
			writeFile << "\r\n";

		}

		writeFile.close();
	}


	return true;
}

int CollisionMap::getTile(int indexX, int indexY)
{
	return this->tiles[(indexY * this->width) + indexX];
}

void CollisionMap::setTile(int value, int indexX, int indexY)
{
	this->tiles[(indexY * this->width) + indexX] = value;
}

bool CollisionMap::checkCollision(Entity* entity, int& correctionX, int& correctionY)
{
	bool result = false;
	
	float x, y;
	int width, height;
	float difX, difY;
	float totalX = 0;
	float totalY = 0;

	BoundingVolume* bv = entity->GetBoundingVolume();

	bv->GetPosition(x,y);
	width = bv->GetWidth();
	height = bv->GetHeight();

	//Return if we are out of bounds
	if ((x < 0 || x > 640 - width) || (y < 0 || y > 640 - height)) {
		if (x < 0)
			correctionX = 0 - x;
		
		else if (x > 640 - width)
			correctionX = 640 - (x + width);
		
		if (y < 0)
			correctionY = 0 - y;

		else if (y > 640 - height)
			correctionY = 640 - (y + height);

		return true;
	}

	int minX = x;
	int minY = y;
	int maxX = (x + width);
	int maxY = (y + height);

	int tileX = (minX+1) / 20;
	int tileY = (minY+1) / 20;

	int tileMinX = 0;
	int tileMaxX = 0;
	int tileMinY = 0;
	int tileMaxY = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (this->tiles[(tileY + j) * this->width + (tileX + i)] != 0) {
				tileMinX = (tileX + i) * 20;
				tileMaxX = tileMinX + 20;
				tileMinY = (tileY + j) * 20;
				tileMaxY = tileMinY + 20;
				if (!(minX > tileMaxX || maxX < tileMinX ||
					minY > tileMaxY || maxY < tileMinY)) {
					result = true;
					int bestX = std::min(std::abs(minX - tileMaxX), std::abs(tileMinX - maxX));
					int bestY = std::min(std::abs(minY - tileMaxY), std::abs(tileMinY - maxY));
					if (bestX < bestY) {
						if (std::abs(minX - tileMaxX) < std::abs(tileMinX - maxX)) {
							correctionX += std::abs(minX - tileMaxX);
						}
						else {
							correctionX += std::abs(tileMinX - maxX) * -1;
						}
					}
					else {
						if (std::abs(minY - tileMaxY) < std::abs(tileMinY - maxY)) {
							correctionY += std::abs(minY - tileMaxY);
						}
						else {
							correctionY += std::abs(tileMinY - maxY) * -1;
						}
					}
				}
			}
		}
	}

	////Calculate the tile that the position is in
	//int startTileX = (x / 20);
	//int startTileY = (y / 20);
	//int endTileX = (x + width / 20);
	//int endTileY = (y + height / 20);

	////Loop through all tiles that the volume intersects 
	//for (int i = startTileY; i <= endTileY; i++) {
	//	for (int j = startTileX; j <= endTileX; j++) {

	//		//check if the tile is not free
	//		if (!this->tiles[(i * this->width) + j] == 0) {
	//			result = true;
	//			
	//			difX = ((x + width) / 2) - (j + 10);
	//			difY = ((y + height) / 2) - (i + 10);

	//			if (difX < difY) {
	//				totalY += difY;
	//			}
	//			else{
	//				totalX += difX;
	//			}

	//		}

	//	}

	//}

	//correctionX = totalX;
	//correctionY = totalY;


	return result;
}

CollisionMap* checkCollisionMap(lua_State* ls, int n)
{
	CollisionMap* collisionMapPtr = nullptr;

	void* ptr = luaL_testudata(ls, n, "MetaCollisionMap");

	if (ptr != nullptr) {
		collisionMapPtr = *(CollisionMap**)ptr;
	}

	return collisionMapPtr;
}

int collisionMap_create(lua_State* ls)
{
	CollisionMap** collisionMap = reinterpret_cast<CollisionMap**>(lua_newuserdata(ls, sizeof(CollisionMap*)));

	*collisionMap = new CollisionMap();

	luaL_getmetatable(ls, "MetaCollisionMap");
	lua_setmetatable(ls, -2);

	std::cout << "[C++] Created CollisionMap\n";

	return 1;
}

int collisionMap_createempty(lua_State* ls)
{
	CollisionMap* collisionMapPtr = checkCollisionMap(ls, 1);

	if (collisionMapPtr->Create(lua_tointeger(ls, 2), lua_tointeger(ls, 3))) {
		std::cout << "[C++] Created empty collisionMap\n";
	}
	else {
		std::cout << "[C++] Could not create empty collisionMap\n";
	}

	return 0;
}

int collisionMap_load(lua_State* ls)
{
	CollisionMap* collisionMapPtr = checkCollisionMap(ls, 1);
	std::string file = lua_tostring(ls, 2);

	if (collisionMapPtr->Load(file)) {
		std::cout << "[C++] Loaded the collisionMap\n";
	}
	else {
		std::cout << "[C++] Could not load the collisionMap\n";
	}

	return 0;

}

int collisionMap_save(lua_State* ls)
{
	CollisionMap* collisionMapPtr = checkCollisionMap(ls, 1);
	std::string file = lua_tostring(ls, 2);

	if (collisionMapPtr->Save(file)) {
		std::cout << "[C++] Loaded the collisionMap\n";
	}
	else {
		std::cout << "[C++] Could not load the collisionMap\n";
	}

	return 0;
}

int collisionMap_destroy(lua_State* ls)
{
	CollisionMap* collisionMapPtr = checkCollisionMap(ls,1);
	
	delete collisionMapPtr;

	return 0;
}

int collisionMap_set(lua_State* ls)
{
	CollisionMap* collisionMapPtr = checkCollisionMap(ls, 1);
	int value = lua_tointeger(ls, 2);
	int indexX = lua_tointeger(ls, 3);
	int indexY = lua_tointeger(ls, 4);

	collisionMapPtr->setTile(value, indexX, indexY);

	return 0;
}

int collisionMap_get(lua_State* ls)
{
	CollisionMap* collisionMapPtr = checkCollisionMap(ls, 1);
	int indexX = lua_tointeger(ls, 2);
	int indexY = lua_tointeger(ls, 3);
	int value = collisionMapPtr->getTile(indexX, indexY);
	lua_pushinteger(ls, value);
	
	return 1;
}

int collisionMap_checkCollision(lua_State* ls)
{
	CollisionMap* collisionMapPtr = checkCollisionMap(ls, 1);
	Entity* entityPtr = checkEntity(ls, 2);

	int x = 0;
	int y = 0;
	bool result = false;

	result = collisionMapPtr->checkCollision(entityPtr, x, y);

	lua_pushboolean(ls, result);
	lua_pushinteger(ls, x);
	lua_pushinteger(ls, y);

	return 3;
}

void RegisterCollisionMap(lua_State* ls)
{
	// Create a luaL metatable. This metatable is not 
	// exposed to Lua. The "luaL_Foo" label is used by luaL
	// internally to identity things.
	luaL_newmetatable(ls, "MetaCollisionMap");
	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metamenu"   |-1


	luaL_Reg sCollisionMapRegs[] =
	{
		{ "New",			collisionMap_create },
		{ "Empty",			collisionMap_createempty },
		{ "Load",			collisionMap_load },
		{ "Save",			collisionMap_save},
		{ "Get",			collisionMap_get },
		{ "Set",			collisionMap_set },
		{ "CheckCollision",	collisionMap_checkCollision },
		{ "__gc",			collisionMap_destroy },
		{ NULL, NULL }
	};

	// Register the C functions _into_ the metatable we just created.
	luaL_setfuncs(ls, sCollisionMapRegs, 0);

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
	lua_setglobal(ls, "CollisionMap");
}
