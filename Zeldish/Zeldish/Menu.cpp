#include "Menu.h"



Menu::Menu()
{
	this->menuFont = sf::Font();
	this->selected = 0;
}


Menu::~Menu()
{

}

void Menu::Shutdown()
{

}

int Menu::Initialize()
{
	this->menuFont.loadFromFile("../Zeldish/Resources/Fonts/Arimo-Regular.ttf");
	
	const float TEXT_SIZE = 40.0f;
	const float TEXT_SPACE = 10.0f;

	for (int i = 0; i < OPTION_COUNT; i++) {
		this->optionTexts[i].setFont(this->menuFont);
		this->optionTexts[i].setCharacterSize(TEXT_SIZE);
		this->optionTexts[i].setPosition(sf::Vector2f(window->getSize().x / 5, (window->getSize().y / 8 + i*(TEXT_SIZE + TEXT_SPACE))));
		this->optionTexts[i].setColor(sf::Color::Red);

	}
	this->optionTexts[0].setColor(sf::Color::White);
	this->optionTexts[0].setString("Start");
	this->optionTexts[1].setString("Level Editor");
	this->optionTexts[2].setString("Quit");

	this->optionTexture.loadFromFile("../Zeldish/Resources/Textures/Menu_Background.jpg");
	this->optionSprite.setTexture(this->optionTexture);
	this->optionSprite.setScale(sf::Vector2f(1, 1));

	this->rect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->rect.setTexture(&optionTexture);
	
	return 0;
}

void Menu::ChangeSelected(int direction)
{

	this->optionTexts[this->selected].setColor(sf::Color::Red);
	this->selected = (this->selected + direction) % OPTION_COUNT;
	if (this->selected < 0)
		this->selected = OPTION_COUNT - 1;
	this->optionTexts[this->selected].setColor(sf::Color::White);
}

int Menu::GetSelected()
{
	return this->selected;
}

void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	
	target.draw(this->rect, states);
	for (int i = 0; i < OPTION_COUNT; i++) {
		target.draw(optionTexts[i], states);
	}
}

Menu* checkMenu(lua_State* L, int n)
{
	Menu* menuPtr = nullptr;

	void* ptr = luaL_testudata(L, n, "MetaMenu");

	if (ptr != nullptr) {
		menuPtr = *(Menu**)ptr;
	}

	return menuPtr;
}

int menu_initialize(lua_State* ls)
{
	Menu* menu = checkMenu(ls, 1);
	
	menu->Initialize();
	std::cout << "[C++] initializing Menu\n";

	return 0;
}

int menu_draw(lua_State* ls)
{
	Menu* menu = checkMenu(ls, 1);
	window->draw(*menu);
	return 0;
}

int menu_create(lua_State* ls)
{
	// Menu is a C++ class defined somewhere...
	Menu** menu = reinterpret_cast<Menu**>(lua_newuserdata(ls, sizeof(Menu*)));
	*menu = new Menu();

	luaL_getmetatable(ls, "MetaMenu");
	lua_setmetatable(ls, -2);

	std::cout << "[C++] Created Menu\n";

	return 1;
}

int menu_destroy(lua_State* ls)
{
	Menu* menu = checkMenu(ls, 1);
	menu->Shutdown();
	delete menu;

	std::cout << "[C++] Deleted Menu\n";

	return 0;
}

int menu_changeselected(lua_State* ls) 
{
	Menu* menu = checkMenu(ls, 1);
	menu->ChangeSelected(lua_tointeger(ls, 2));

	std::cout << "[C++] Moved Menu Select\n";

	return 0;
}

int menu_getSelected(lua_State* ls)
{
	Menu* menu = checkMenu(ls, 1);

	int result = menu->GetSelected();
	lua_pushinteger(ls, result);

	std::cout << "[C++] Menu Get Select\n";

	return 1;
}

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
		{ "Select",			menu_changeselected },
		{ "Draw",			menu_draw },
		{ "GetSelected",	menu_getSelected },
		/*{ "Print",			menu_print },
		{ "Jump",			menu_jump },
		{ "SetPosition",	menu_setPosition },*/
		{ "__gc",			menu_destroy },
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