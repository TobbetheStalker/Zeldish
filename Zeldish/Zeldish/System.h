#ifndef SYSTEM_H
#define SYSTEM_H

#include "SFML\Graphics.hpp"
	
class System : public sf::Drawable
{
private:	//Variables
	sf::CircleShape *Circle;
public:
	System();
	virtual ~System();

	int HandleInput();
	int Update(float dT);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:	//Functions

};

#endif