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

	void SetX(int x);
	void SetY(int y);
	void SetPos(int x, int y);
	void SetWidth(int width);
	void SetHeight(int height);

	virtual int Update();

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif