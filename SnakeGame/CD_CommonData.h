#pragma once
//================================================================================================
//..Project       : Snake Game
//..Module        : Common
//..Description   : defines\includes for project
//..Author        : Innoox
//..Created       : 2021.02.10
//================================================================================================
//..include section
#include <iostream>
//================================================================================================
namespace CD
{
	//..data type definition
	using i16 = int16_t;
	using i32 = int32_t;
	using u32 = uint32_t;
	//..direction definition
	enum class Direction
	{
		STOP = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};
	//..game state definition
	enum class GameState
	{
		MAINMENU = 0,
		START = 1,
		GAMEOVER = 2,
		PAUSE = 3,
		QUIT = 4
	};
}