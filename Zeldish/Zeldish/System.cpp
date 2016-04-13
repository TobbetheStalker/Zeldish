#include "System.h"



System::System()
{
	this->Circle = new sf::CircleShape(100.0f);
	this->Circle->setFillColor(sf::Color::Green);
}


System::~System()
{
	delete this->Circle;
	this->Circle = NULL;
}

int System::HandleInput()
{
	return 0;
}

int System::Update()
{
	return 0;
}

void System::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*this->Circle, states);
}
