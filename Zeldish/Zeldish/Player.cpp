#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

Player* checkPlayer(lua_State* L, int n)
{
	Player* playerPtr = nullptr;

	void* ptr = luaL_testudata(L, n, "MetaPlayer");

	if (ptr != nullptr) {
		playerPtr = *(Player**)ptr;
	}

	return playerPtr;
}


int player_create(lua_State* ls)
{

	return 1;
}

int player_initialize(lua_State* ls)
{
	int result = 0;

	Player* playerPtr = checkPlayer(ls, 1);
	//If not implemented, this will call the parent version of the function
	result = playerPtr->Initialize();

	return result;
}

int player_destroy(lua_State* ls)
{

	return 0;
}

int player_draw(lua_State* ls)
{
	return 0;
}

void RegisterPlayer(lua_State * ls)
{
	// Create a luaL metatable. This metatable is not 
	// exposed to Lua. The "luaL_Foo" label is used by luaL
	// internally to idplayer things.
	luaL_newmetatable(ls, "MetaPlayer");
	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metaplayer"   |-1


	luaL_Reg sPlayerRegs[] =
	{
		{ "New",			player_create },
		{ "Initialize",		player_initialize },
		{ "Draw",			player_draw },
		/*{ "Print",			player_print },*/
		{ "__gc",			player_destroy },
		{ NULL, NULL }
	};

	// Register the C functions _into_ the metatable we just created.
	luaL_setfuncs(ls, sPlayerRegs, 0);

	lua_pushvalue(ls, -1);

	// The Lua stack at this point looks like this:
	//     
	//     2| metatable "MetaPlayer"   |-1
	//     1| metatable "MetaPlayer"   |-2

	// Set the "__index" field of the metatable to point to itself
	// This pops the stack
	lua_setfield(ls, -1, "__index");

	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metaplayer"   |-1

	// The luaL_Foo metatable now has the following fields
	//     - __gc
	//     - __index
	//     - add
	//     - print
	//     - new

	// Now we use setglobal to officially expose the luaL_Foo metatable 
	// to Lua. And we use the name "player".
	//
	// This allows Lua scripts to _override_ the metatable of player.
	// For high security code this may not be called for but 
	// we'll do this to get greater flexibility.
	lua_setglobal(ls, "Player");
}