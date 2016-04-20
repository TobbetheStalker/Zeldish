#ifndef ENTITY_H
#define ENTITY_H
#include "BoundingVolume.h"
#include "SFML\Graphics.hpp"
class Entity : public sf::Drawable , sf::Transformable
{
protected:

public:
	Entity();
	virtual ~Entity();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif