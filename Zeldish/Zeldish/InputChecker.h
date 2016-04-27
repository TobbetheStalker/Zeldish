#ifndef INPUTCHECKER_H
#define INPUTCHECKER_H

#include "SFML\Graphics.hpp"
#include "lua.hpp"
#include <iostream>
#include "WindowLib.h"

class InputChecker {
private:
	static InputChecker* instance_;
	bool keys[200];
	bool oldKeys[200];
	bool leftMouse;
	bool rightMouse;
	bool oldLeftMouse;
	bool oldRightMouse;
	InputChecker();
	

public:
	~InputChecker();

	static InputChecker& Instance();
	
	void UpdateInput();
	void SetKeyPressed(int keyCode);
	void SetKeyReleased(int keyCode);
	int CheckKeyPressed(int keyCode);
	int CheckKeyDown(int keyCode);
	int CheckKeyReleased(int keyCode);
	int GetMouseX();
	int GetMouseY();
	void SetLeftMousePressed();
	void SetLeftMouseReleased();
	int CheckLeftMousePressed();
	void SetRightMousePressed();
	void SetRightMouseReleased();
	int CheckRightMousePressed();

	void ReleaseInstance();
};

int input_create(lua_State* ls);

int Input_checkkey(lua_State* ls);

void RegisterInputChecker(lua_State* ls);

#endif