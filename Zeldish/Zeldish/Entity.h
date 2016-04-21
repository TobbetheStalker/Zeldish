#ifndef ENTITY_H
#define ENTITY_H
#include "BoundingVolume.h"
#include "SFML\Graphics.hpp"
#include "WindowLib.h"
#include "lua.hpp"
#include "EntityLib.h"
class Entity : public sf::Drawable , sf::Transformable
{
protected:
	int x, y, width, height;
	int animationType;
	float animationTime;
	int animationWidth;
	sf::IntRect spriteRect;

	BoundingVolume boundingBox;
	sf::Texture drawTexture;
	sf::Sprite mySprite;
	EntityLib::Direction myDirection;
public:
	Entity();
	virtual ~Entity();
	virtual int Initialize(std::string texturePath);

	virtual void Shutdown();

#pragma region
	void SetX(float x);
	void SetSpriteX(int x);
	void SetY(float y);
	void SetSpriteY(int y);
	void SetSpritePos(int x, int y);
	void SetPos(float x, float y);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetSpriteHeight(int height);
	void SetSpriteWidth(int width);
	void SetDirection(EntityLib::Direction direction);
#pragma endregion getters & setters

	virtual int Update(float dTIme);
	virtual int UpdateSprite(float dTime);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	EntityLib::Direction GetDirection();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

int entity_initialize(lua_State* ls);

int entity_draw(lua_State* ls);

int entity_create(lua_State* ls);

int entity_destroy(lua_State* ls);

int entity_setPos(lua_State* ls);

int entity_setWidth(lua_State* ls);

int entity_setHeight(lua_State* ls);

int entity_getPos(lua_State* ls);

int entity_getWidth(lua_State* ls);

int entity_getHeight(lua_State* ls);

int entity_update(lua_State* ls);

void RegisterEntity(lua_State * ls);


#endif