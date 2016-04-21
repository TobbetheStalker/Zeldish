#pragma once

namespace EntityLib{
	enum Direction {
		DOWN = 0,
		LEFT = 1,
		RIGHT = 2,
		UP = 3,
		NONE = 4
	};

	static const int SPEED = 10;
	static const int X_SPEED = SPEED;
	static const int Y_SPEED = SPEED;

	static const float FRAME_TIME = 1.2f;
	static const int FRAME_COUNT = 3;
	static const float ANIMATION_LIMIT = FRAME_TIME * FRAME_COUNT;


	static const int PLAYER_WIDTH = 32;
	static const int PLAYER_HEIGHT = 32;
}