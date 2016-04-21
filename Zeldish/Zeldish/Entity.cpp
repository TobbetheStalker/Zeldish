#include "Entity.h"



Entity::Entity()
{
	this->x = this->y = this->width = this->height = this->animationType = 0;
	this->animationTime = 0.0f;
	this->boundingBox = BoundingVolume();
}


Entity::~Entity()
{
}

int Entity::Initialize()
{
	int result = 0;
	this->animationTime = 0.0f;
	this->animationType = EntityLib::DOWN;
	this->x = 0;
	this->y = 0;
	this->width = EntityLib::PLAYER_WIDTH;
	this->height = EntityLib::PLAYER_HEIGHT;
	this->spriteRect = sf::IntRect(0, 0, EntityLib::PLAYER_WIDTH, EntityLib::PLAYER_HEIGHT);

	this->drawTexture.loadFromFile("../Zeldish/Resources/Textures/RacoonCharacter.png");
	this->mySprite.setTexture(drawTexture);
	this->mySprite.setTextureRect(this->spriteRect);

	return result;
}

void Entity::Shutdown()
{
}

void Entity::SetX(float x)
{
}

void Entity::SetSpriteX(int x)
{
	this->x = x;
}

void Entity::SetY(float y)
{
}

void Entity::SetSpriteY(int y)
{
	this->y = y;
}

void Entity::SetSpritePos(int x, int y)
{
	this->x = x;
	this->y = y;
	this->mySprite.setPosition(sf::Vector2f(x, y));
}

void Entity::SetPos(float x, float y)
{
}

void Entity::SetWidth(int width)
{
	this->boundingBox.SetWidth(width);
}

void Entity::SetHeight(int height)
{
	this->boundingBox.SetHeight(height);
}

void Entity::SetSpriteHeight(int height)
{
	this->height = height;
}

void Entity::SetSpriteWidth(int width)
{
	this->width = width;
}

void Entity::SetDirection(EntityLib::Direction direction)
{
	this->myDirection = direction;
}

int Entity::Update(float dTime)
{
	int result = 0;
	int xDelta = 0, yDelta = 0;
	switch (myDirection)
	{
	case EntityLib::DOWN:
		yDelta++;
		break;
	case EntityLib::LEFT:
		xDelta--;
		break;
	case EntityLib::RIGHT:
		xDelta++;
		break;
	case EntityLib::UP:
		yDelta--;
		break;
	default:
		break;
	}

	//Apply the difference in position
	this->x += xDelta * dTime;
	this->y += yDelta * dTime;

	//Apply the new position to the sprite
	result = this->UpdateSprite(dTime);
	return result;
}

int Entity::UpdateSprite(float dTime)
{
	int result = 1;
	this->mySprite.setPosition(sf::Vector2f(this->x, this->y));
	
	//Update animation time
	this->animationTime = (this->animationTime + dTime);
	//Apply animation bounds
	if (this->animationTime >= EntityLib::ANIMATION_LIMIT)
		this->animationTime -= EntityLib::ANIMATION_LIMIT;
	//Calculate animation frame
	int frame = this->animationTime / EntityLib::FRAME_TIME;
	//Apply animation frame
	this->spriteRect.left = frame * EntityLib::PLAYER_WIDTH;
	//Calculate the animation type to be used
	if (this->myDirection != EntityLib::Direction::NONE)
		this->animationType = this->myDirection;
	//Do Safety correction
	if (this->animationType < 0 || this->animationType > EntityLib::Direction::NONE)
		this->animationType = 0;
	//Apply the animation type
	this->spriteRect.top = (this->animationType * EntityLib::PLAYER_HEIGHT);
	//And finally set our animation to be the one displayed
	this->mySprite.setTextureRect(this->spriteRect);

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

EntityLib::Direction Entity::GetDirection()
{
	return this->myDirection;
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->mySprite, states);

}

Entity* checkEntity(lua_State* L, int n)
{
	Entity* entityPtr = nullptr;

	void* ptr = luaL_testudata(L, n, "MetaEntity");

	if (ptr != nullptr) {
		entityPtr = *(Entity**)ptr;
	}

	return entityPtr;
}

int entity_initialize(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);

	entity->Initialize();
	std::cout << "[C++] initializing Entity\n";

	return 0;
}

int entity_draw(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);
	window->draw(*entity);
	return 0;
}

int entity_create(lua_State* ls)
{
	// Entity is a C++ class defined somewhere...
	Entity** entity = reinterpret_cast<Entity**>(lua_newuserdata(ls, sizeof(Entity*)));
	*entity = new Entity();

	luaL_getmetatable(ls, "MetaEntity");
	lua_setmetatable(ls, -2);

	std::cout << "[C++] Created Entity\n";

	return 1;
}

int entity_destroy(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);
	entity->Shutdown();
	delete entity;

	std::cout << "[C++] Deleted Entity\n";

	return 0;
}


int entity_setPos(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);
	if(entity)
		entity->SetPos(lua_tonumber(ls, 2), lua_tonumber(ls, 3));

	return 0;
}

int entity_setWidth(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);
	if(entity)
		entity->SetPos(lua_tonumber(ls, 2), lua_tonumber(ls, 3));

	return 0;
}

int entity_setHeight(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);
	if(entity)
		entity->SetPos(lua_tonumber(ls, 2), lua_tonumber(ls, 3));

	return 0;
}

int entity_getPos(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);

	int x = -1;
	int y = -1;
	if (entity)
	{
		x = entity->GetX();
		y = entity->GetY();
	}

	lua_pushinteger(ls, x);
	lua_pushinteger(ls, y);
	return 2;
}

int entity_getWidth(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);
	int width = -1;
	if (entity)
	{
		width = entity->GetWidth();
	}

	lua_pushinteger(ls, width);
	return 1;
}

int entity_getHeight(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);
	int height = -1;
	if (entity)
	{
		height = entity->GetHeight();
	}

	lua_pushinteger(ls, height);
	return 1;
}

int entity_update(lua_State* ls)
{
	Entity* entity = checkEntity(ls, 1);
	if (entity)
	{
		entity->Update(lua_tonumber(ls, 2));
	}
	return 0;
}

void RegisterEntity(lua_State * ls)
{
	// Create a luaL metatable. This metatable is not 
	// exposed to Lua. The "luaL_Foo" label is used by luaL
	// internally to identity things.
	luaL_newmetatable(ls, "MetaEntity");
	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metaentity"   |-1


	luaL_Reg sEntityRegs[] =
	{
		{ "New",			entity_create },
		{ "Initialize",		entity_initialize },
		{ "Draw",			entity_draw },
		{ "SetPos",			entity_setPos },
		{ "SetWidth",		entity_setWidth },
		{ "SetHeight",		entity_setHeight },
		{ "GetPos",			entity_getPos },
		{ "GetWidth",		entity_getWidth },
		{ "GetHeight",		entity_getHeight },
		{ "Update",			entity_update },
		{ "__gc",			entity_destroy },
		{ NULL, NULL }
	};

	// Register the C functions _into_ the metatable we just created.
	luaL_setfuncs(ls, sEntityRegs, 0);

	lua_pushvalue(ls, -1);

	// The Lua stack at this point looks like this:
	//     
	//     2| metatable "MetaEntity"   |-1
	//     1| metatable "MetaEntity"   |-2

	// Set the "__index" field of the metatable to point to itself
	// This pops the stack
	lua_setfield(ls, -1, "__index");

	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metaentity"   |-1

	// The luaL_Foo metatable now has the following fields
	//     - __gc
	//     - __index
	//     - add
	//     - print
	//     - new

	// Now we use setglobal to officially expose the luaL_Foo metatable 
	// to Lua. And we use the name "entity".
	//
	// This allows Lua scripts to _override_ the metatable of entity.
	// For high security code this may not be called for but 
	// we'll do this to get greater flexibility.
	lua_setglobal(ls, "Entity");
}