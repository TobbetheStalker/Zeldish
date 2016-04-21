#include "InputChecker.h"

InputChecker::InputChecker()
{
	for (int i = 0; i < 200; i++) {
		this->keys[i] = false;
		this->oldKeys[i] = false;
	}
}

InputChecker::~InputChecker()
{
}

InputChecker& InputChecker::Instance()
{
	static InputChecker* instance = new InputChecker;
	return *instance;
}

void InputChecker::UpdateInput()
{
	for (int i = 0; i < 200; i++) {
		this->oldKeys[i] = this->keys[i];
	}
}

void InputChecker::SetKeyPressed(int keyCode)
{
	this->keys[keyCode] = true;
	return;
}

void InputChecker::SetKeyReleased(int keyCode)
{
	this->keys[keyCode] = false;
	return;
}

int InputChecker::CheckKeyPressed(int keyCode) 
{
	return !this->oldKeys[keyCode] && this->keys[keyCode];
}

int InputChecker::CheckKeyDown(int keyCode)
{
	return this->keys[keyCode];
}

int InputChecker::CheckKeyReleased(int keyCode)
{
	return this->oldKeys[keyCode] && !this->keys[keyCode];
}

int InputChecker::GetMouseX()
{
	return sf::Mouse::getPosition(*window).x;
}

int InputChecker::GetMouseY()
{
	return sf::Mouse::getPosition(*window).y;
}

void InputChecker::ReleaseInstance()
{
	if (this) {
		delete this;
	}
}

//InputChecker* checkInput(lua_State* ls, int n)
//{
//	InputChecker* inputCheckerPtr = nullptr;
//
//	void* ptr = luaL_testudata(ls, n, "MetaInput");
//
//	if (ptr != nullptr) {
//		inputCheckerPtr = *(InputChecker**)ptr;
//	}
//
//	return inputCheckerPtr;
//}

//int input_create(lua_State* ls)
//{
//	InputChecker** input = reinterpret_cast<InputChecker**>(lua_newuserdata(ls, sizeof(InputChecker*)));
//	*input = new InputChecker();
//
//	luaL_getmetatable(ls, "MetaInput");
//	lua_setmetatable(ls, -2);
//
//	std::cout << "[C++] Created InputChecker\n";
//
//	return 1;
//}

int input_checkkeypressed(lua_State* ls)
{
	int isPressed = InputChecker::Instance().CheckKeyPressed(lua_tointeger(ls, 1));

	lua_pushinteger(ls, isPressed);

	return 1;
}

int input_checkkeydown(lua_State* ls)
{
	int isDown = InputChecker::Instance().CheckKeyDown(lua_tointeger(ls, 1));

	lua_pushinteger(ls, isDown);

	return 1;
}

int input_checkkeyreleased(lua_State* ls)
{
	//InputChecker* input = checkInput(ls, 1);
	int isReleased = InputChecker::Instance().CheckKeyReleased(lua_tointeger(ls, 1));

	lua_pushinteger(ls, isReleased);

	return 1;
}

int input_getmouseposx(lua_State* ls)
{
	lua_pushinteger(ls, InputChecker::Instance().GetMouseX());

	return 1;
}

int input_getmouseposy(lua_State* ls)
{
	lua_pushinteger(ls, InputChecker::Instance().GetMouseY());

	return 1;
}

int input_destroy(lua_State* ls) 
{
	InputChecker::Instance().ReleaseInstance();

	return 0;
}

void RegisterInputChecker(lua_State * ls)
{
	// Create a luaL metatable. This metatable is not 
	// exposed to Lua. The "luaL_Foo" label is used by luaL
	// internally to identity things.
	luaL_newmetatable(ls, "MetaInput");
	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metamenu"   |-1


	luaL_Reg sInputRegs[] =
	{
		{ "IsPressed",		input_checkkeypressed },
		{ "IsDown",			input_checkkeydown },
		{ "IsReleased",		input_checkkeyreleased },
		{ "GetMousePosX",	input_getmouseposx },
		{ "GetMousePosY",	input_getmouseposy },
		/*{ "Print",			menu_print },
		{ "Jump",			menu_jump },
		{ "SetPosition",	menu_setPosition },*/
		{ "__gc",			input_destroy },
		{ NULL, NULL }
	};

	// Register the C functions _into_ the metatable we just created.
	luaL_setfuncs(ls, sInputRegs, 0);

	lua_pushvalue(ls, -1);

	// The Lua stack at this point looks like this:
	//     
	//     2| metatable "Metamenu"   |-1
	//     1| metatable "Metamenu"   |-2

	// Set the "__index" field of the metatable to point to itself
	// This pops the stack
	lua_setfield(ls, -1, "__index");

	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "Metamenu"   |-1

	// The luaL_Foo metatable now has the following fields
	//     - __gc
	//     - __index
	//     - add
	//     - print
	//     - new

	// Now we use setglobal to officially expose the luaL_Foo metatable 
	// to Lua. And we use the name "menu".
	//
	// This allows Lua scripts to _override_ the metatable of menu.
	// For high security code this may not be called for but 
	// we'll do this to get greater flexibility.
	lua_setglobal(ls, "Input");
}