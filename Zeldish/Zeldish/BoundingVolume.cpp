#include "BoundingVolume.h"



BoundingVolume::BoundingVolume()
{
	this->m_x = this->m_y = this->m_width = this->m_height = 0;
}


BoundingVolume::~BoundingVolume()
{
}

void BoundingVolume::ShutDown()
{
}

int BoundingVolume::Initialize(float x, float y, int width, int height)
{
	this->m_x = x;
	this->m_y = y;
	this->m_width = width;
	this->m_height = height;
	return 1;
}

int BoundingVolume::SetPosition(float x, float y)
{
	int result = 1;

	this->m_x = x;
	this->m_y = y;

	return result;
}

//0 if outside, 1 if intersection, 2 if contained
int BoundingVolume::CheckAgainst(BoundingVolume * other)
{
	int result = 1;

	if (this->m_x > other->m_x + other->m_width || this->m_x + this->m_width < other->m_x ||
		this->m_y > other->m_y + other->m_height || this->m_y + this->m_height < other->m_y)
	{
		//False
		result = 0;
	}
	else
	{
		//Intersection
		result = 1;
		//Add check for containing
	}
	
	return result;
}

void BoundingVolume::GetPosition(int& x, int& y)
{
	x = this->m_x;
	y = this->m_y;

	return;
}

int BoundingVolume::GetWidth()
{
	return this->m_width;
}

int BoundingVolume::GetHeight()
{
	return this->m_height;
}


BoundingVolume* checkBoundingVolume(lua_State* L, int n)
{
	BoundingVolume* BoundingVolumePtr = nullptr;

	void* ptr = luaL_testudata(L, n, "MetaBoundingVolume");

	if (ptr != nullptr) {
		BoundingVolumePtr = *(BoundingVolume**)ptr;
	}

	return BoundingVolumePtr;
}

int BoundingVolume_initialize(lua_State* ls)
{
	BoundingVolume* BoundingVolume = checkBoundingVolume(ls, 1);

	BoundingVolume->Initialize(lua_tointeger(ls, 2), lua_tointeger(ls, 3), lua_tointeger(ls, 4), lua_tointeger(ls, 5));
	std::cout << "[C++] initialized BoundingVolume\n";

	return 0;
}

int BoundingVolume_create(lua_State* ls)
{
	// Menu is a C++ class defined somewhere...
	BoundingVolume** boundingVolume = NULL;
	boundingVolume = reinterpret_cast<BoundingVolume**>(lua_newuserdata(ls, sizeof(BoundingVolume*)));
	*boundingVolume = new BoundingVolume();
	luaL_getmetatable(ls, "MetaBoundingVolume");
	lua_setmetatable(ls, -2);

	std::cout << "[C++] Created BoundingVolume\n";

	return 1;
}

int BoundingVolume_CheckAgainst(lua_State* ls)
{
	BoundingVolume* first = checkBoundingVolume(ls, 1);
	BoundingVolume* second = checkBoundingVolume(ls, 2);

	int result = first->CheckAgainst(second);
	lua_pushinteger(ls, result);
	return 1;
}

int BoundingVolume_GetWidth(lua_State* ls)
{
	BoundingVolume* BoundingVolume = checkBoundingVolume(ls, 1);

	int width = BoundingVolume->GetWidth();
	
	lua_pushinteger(ls, width);

	return 0;
}

int BoundingVolume_GetHeight(lua_State* ls)
{
	BoundingVolume* BoundingVolume = checkBoundingVolume(ls, 1);

	int height = BoundingVolume->GetWidth();

	lua_pushinteger(ls, height);

	return 0;
}

int BoundingVolume_GetPosition(lua_State* ls)
{
	BoundingVolume* BoundingVolume = checkBoundingVolume(ls, 1);

	int x = -1;
	int y = -1;

	BoundingVolume->GetPosition(x, y);

	lua_pushinteger(ls, x);
	lua_pushinteger(ls, y);

	return 0;
}


int BoundingVolume_setPosition(lua_State* ls) {
	int result = 0;

	BoundingVolume* BoundingVolume = checkBoundingVolume(ls, 1);
	result = BoundingVolume->SetPosition(lua_tointeger(ls, 2), lua_tointeger(ls, 3));

	return 0;
}

int BoundingVolume_destroy(lua_State* ls)
{
	BoundingVolume* myVolume = checkBoundingVolume(ls, 1);
	myVolume->ShutDown();
	delete myVolume;

	std::cout << "[C++] Deleted BoundingVolume\n";

	return 0;
}

void RegisterBoundingVolume(lua_State * ls)
{
	// Create a luaL metatable. This metatable is not 
	// exposed to Lua. The "luaL_Foo" label is used by luaL
	// internally to identity things.
	luaL_newmetatable(ls, "MetaBoundingVolume");
	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "MetaBoundingVolume"   |-1


	luaL_Reg sBoundingVolumeRegs[] =
	{
		{ "New",			BoundingVolume_create },
		{ "Initialize",		BoundingVolume_initialize },
		{ "CheckAgainst",	BoundingVolume_CheckAgainst },
		{ "GetWidth",			BoundingVolume_GetWidth },
		{ "GetHeight",			BoundingVolume_GetHeight },
		{ "GetPosition",		BoundingVolume_GetPosition },
		{ "SetPosition",	BoundingVolume_setPosition },
		{ "__gc",			BoundingVolume_destroy },
		{ NULL, NULL }
	};

	// Register the C functions _into_ the metatable we just created.
	luaL_setfuncs(ls, sBoundingVolumeRegs, 0);

	lua_pushvalue(ls, -1);

	// The Lua stack at this point looks like this:
	//     
	//     2| metatable "MetaBoundingVolume"   |-1
	//     1| metatable "MetaBoundingVolume"   |-2

	// Set the "__index" field of the metatable to point to itself
	// This pops the stack
	lua_setfield(ls, -1, "__index");

	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "MetaBoundingVolume"   |-1

	// The luaL_Foo metatable now has the following fields
	//     - __gc
	//     - __index
	//     - add
	//     - print
	//     - new

	// Now we use setglobal to officially expose the luaL_Foo metatable 
	// to Lua. And we use the name "BoundingVolume".
	//
	// This allows Lua scripts to _override_ the metatable of BoundingVolume.
	// For high security code this may not be called for but 
	// we'll do this to get greater flexibility.
	lua_setglobal(ls, "BoundingVolume");
}