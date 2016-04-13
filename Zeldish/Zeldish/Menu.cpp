#include "Menu.h"



Menu::Menu()
{
	this->menuFont = sf::Font();

}


Menu::~Menu()
{
}

void Menu::Shutdown()
{
	for (int i = 0; i < OPTION_COUNT; i++)
	{
	}
}

int Menu::Initialize()
{
	this->menuFont.loadFromFile("../Zeldish/Resources/Fonts/Arimo-Regular.ttf");
	


	for (int i = 0; i < OPTION_COUNT; i++) {
		this->optionTexts[i].setFont(this->menuFont);
		this->optionTexts[i].setCharacterSize(18.f);
		this->optionTexts[i].setPosition(sf::Vector2f(100.f , (100 + i*30)));
		this->optionTexts[i].setColor(sf::Color::Red);

	}
	this->optionTexts[0].setString("Start");
	this->optionTexts[1].setString("Level Editor");
	this->optionTexts[2].setString("Quit");

	this->optionTexture.loadFromFile("../Zeldish/Resources/Textures/Menu_Background.jpg");
	this->optionSprite.setTexture(this->optionTexture);
	this->optionSprite.setScale(sf::Vector2f(1, 1));

	this->rect.setSize(sf::Vector2f(600.0f, 600.0f));
	this->rect.setTexture(&optionTexture);
	
	return 0;
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
	std::cout << "[C++] initialized Menu\n";

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
	// Monster is a C++ class defined somewhere...
	Menu** menu = reinterpret_cast<Menu**>(lua_newuserdata(ls, sizeof(Menu*)));
	*menu = new Menu();

	luaL_getmetatable(ls, "MetaMenu");
	lua_setmetatable(ls, -2);

	std::cout << "[C++] Created Menu\n";

	return 0;
}

