#ifndef SYSTEM_H
#define SYSTEM_H

#include "SFML\Graphics.hpp"

class System : public sf::Drawable
{
public:
	System();
	virtual ~System();

	int HandleInput();
	int Update();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif