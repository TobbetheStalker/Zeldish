#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "lua.hpp"
#include "SFML\Graphics.hpp"
#include "WindowLib.h"

static const int OPTION_COUNT = 3;

class Menu : public sf::Drawable , sf::Transformable
{
private:
	sf::Font menuFont;

	sf::Texture optionTexture;
	sf::Sprite optionSprite;
	sf::RectangleShape rect;
	sf::Text optionTexts[OPTION_COUNT];
public:
	Menu();
	~Menu();
	void Shutdown();
	int Initialize();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

int menu_initialize(lua_State* ls);

int menu_draw(lua_State* ls);

int menu_create(lua_State* ls);



void RegisterMenu(lua_State * ls)
{
	// Create a luaL metatable. This metatable is not 
	// exposed to Lua. The "luaL_Foo" label is used by luaL
	// internally to identity things.
	luaL_newmetatable(ls, "MetaMenu");
	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metamenu"   |-1


	luaL_Reg sMenuRegs[] =
	{
		{ "New",			menu_create },
		{ "Initialize",		menu_initialize },
		{ "Draw",			menu_draw },
		/*{ "Print",			menu_print },
		{ "Jump",			menu_jump },
		{ "SetPosition",	menu_setPosition },
		{ "__gc",			menu_destroy },*/
		{ NULL, NULL }
	};

	// Register the C functions _into_ the metatable we just created.
	luaL_setfuncs(ls, sMenuRegs, 0);

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
	lua_setglobal(ls, "Menu");
}

#endif