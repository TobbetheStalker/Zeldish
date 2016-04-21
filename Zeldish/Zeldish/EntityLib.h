#pragma once

namespace EntityLib{
	enum Direction {
		DOWN = 0,
		LEFT = 1,
		RIGHT = 2,
		UP = 3,
		NONE = 4
	};

	static const float SPEED = 5.0f;

	static const float FRAME_TIME = 1.2f;
	static const int FRAME_COUNT = 3;
	static const float ANIMATION_LIMIT = FRAME_TIME * FRAME_COUNT;

	static const int ENTITY_WIDTH = 32;
	static const int ENTITY_HEIGHT = 32;
	//2 from left edge and 2 from right endge
	static const int PLAYER_WIDTH = ENTITY_WIDTH - 2 - 2;
	static const int PLAYER_HEIGHT = ENTITY_HEIGHT;
	//
	static const int PROJECTILE_WIDTH = ENTITY_WIDTH - 2 - 2;
	static const int PROJECTILE_HEIGHT = ENTITY_HEIGHT - 6 - 6;
}