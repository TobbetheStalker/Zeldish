#include "Entity.h"



Entity::Entity()
{
	this->x = this->y = this->width = this->height = 0;
	this->boundingBox = BoundingVolume();
}


Entity::~Entity()
{
}

int Entity::Initialize()
{
	int result = 0;

	this->x = 0;
	this->y = 0;
	this->width = 32;
	this->height = 32;
	this->spriteRect = sf::IntRect(0, 0, 32, 32);

	this->drawTexture.loadFromFile("../Zeldish/Resources/Textures/RacoonCharacter.png");
	this->mySprite.setTexture(drawTexture);
	this->mySprite.setTextureRect(this->spriteRect);

	return result;
}

void Entity::SetX(int x)
{
	this->x = x;
}

void Entity::SetY(int y)
{
	this->y = y;
}

void Entity::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Entity::SetWidth(int width)
{
	this->width = width;
}

void Entity::SetHeight(int height)
{
	this->height = height;
}

int Entity::Update()
{
	int result = 0;



	return result;
}

int Entity::GetX()
{
	return this->x;
}

int Entity::GetY()
{
	return this->y;
}

int Entity::GetWidth()
{
	return this->width;
}

int Entity::GetHeight()
{
	return this->height;
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->mySprite, states);

}
