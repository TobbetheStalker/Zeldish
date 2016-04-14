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
	int selected;

public:
	Menu();
	~Menu();
	void Shutdown();
	int Initialize();
	void ChangeSelected(int direction);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

int menu_initialize(lua_State* ls);

int menu_draw(lua_State* ls);

int menu_create(lua_State* ls);

int menu_destroy(lua_State* ls);

int menu_changeselected(lua_State* ls);


void RegisterMenu(lua_State * ls);

#endif