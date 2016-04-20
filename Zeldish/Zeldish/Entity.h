#ifndef ENTITY_H
#define ENTITY_H
#include "BoundingVolume.h"
#include "SFML\Graphics.hpp"
#include "WindowLib.h"
class Entity : public sf::Drawable , sf::Transformable
{
protected:
	int x, y, width, height;
	sf::IntRect spriteRect;

	BoundingVolume boundingBox;
	sf::Texture drawTexture;
	sf::Sprite mySprite;

public:
	Entity();
	virtual ~Entity();
	virtual int Initialize();

	virtual void Shutdown();

	void SetX(int x);
	void SetY(int y);
	void SetPos(int x, int y);
	void SetWidth(int width);
	void SetHeight(int height);

	virtual int Update(float dTIme);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

int entity_initialize(lua_State* ls);

int entity_draw(lua_State* ls);

int entity_create(lua_State* ls);

int entity_destroy(lua_State* ls);

int entity_SetPos(lua_State* ls);

int entity_SetWidth(lua_State* ls);

int entity_SetHeight(lua_State* ls);

void RegisterEntity(lua_State * ls);


#endif