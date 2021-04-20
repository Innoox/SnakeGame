#pragma once
//================================================================================================
//..Project       : Snake Game
//..Module        : Data
//..Description   : Game data class holder
//..Author        : Innoox
//..Created       : 2021.02.10
//================================================================================================
//..include section
#include "CD_CommonData.h"
#include "SD_SnakeData.h"
using namespace CD;
using namespace SD;
//================================================================================================
namespace GD
{
	class GameData
	{
	public:
		//..constructor
		GameData();
		//..methods section
		//..getters
		inline i32 getScore() const { return this->_Score; };
		//..setters
		inline void setScore() { this->_Score++; };
	private:
		//..key input logic
		void _KeyLogic();
		//..main menu
		void _MainMenu();
		//..main game init
		void _GameInit();
		//..game logic
		void _GameLogic();
		//..supportive methods
		void _ClearScreen() const;
		void _VertBorder(std::string inner, std::string outter) const;
		void _VertBorderWithText(std::string inner, std::string text, std::string outter) const;
		//..checkers
		void isWall();
		void isBody();
		void isTarget();
		//..play sound
		void playTrack(std::string soundName, GameState givenState);
	private:
		//..game board size
		const i32 _BoardWidth{ 60 };
		const i32 _BoardHeight{ 20 };
		//..game state holder
		GameState _GS{ GameState::MAINMENU };
		//..direction holder
		Direction _Dir{ Direction::STOP };
		//..current score
		i32 _Score{ 0 };
		//..snake holder
		Snake _snake{ this->_BoardWidth / 2, this->_BoardHeight / 2, 100, 100 };
		Snake _target{ rand() % this->_BoardWidth, rand() % this->_BoardHeight };
		//..game conditions
		i32 _GameSpeed{ 100 };
		//..gamestate holder for the track selection
		GameState prev{ GameState::PAUSE };
	};
}