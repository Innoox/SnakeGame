#pragma once
//================================================================================================
//..Project       : Snake Game
//..Module        : Data
//..Description   : Snake data class holder
//..Author        : Innoox
//..Created       : 2021.02.10
//================================================================================================
//..include section
#include <vector>

#include "CD_CommonData.h"
using namespace CD;
//================================================================================================
namespace SD
{
	//.. basic data holder
	class Snake
	{
	public:
		//..constructors section
		Snake() : _XPos(0), _YPos(0) {};
		//Snake(i32 gXPos, i32 gYPos, i32 gTailX = 0, i32 gTailY = 0) : _XPos(gXPos), _YPos(gYPos), _SnakeTailX(new int[gTailX]), _SnakeTailY(new int[gTailY]) {};
		Snake(i32 gXPos, i32 gYPos, i32 gTailX = 0, i32 gTailY = 0) : _XPos(gXPos), _YPos(gYPos) {};
		//..destructor
		//~Snake() { delete[] this->_SnakeTailX; delete[] this->_SnakeTailY; };
		//..getters section
		inline i32 getXPos() const { return this->_XPos; };
		inline i32 getYPos() const { return this->_YPos; };
		//inline i32 getSnakeTailX(i32 pos) const { return this->_SnakeTailX[pos]; };
		//inline i32 getSnakeTailY(i32 pos) const { return this->_SnakeTailY[pos]; };
		inline i32 getTailSize() const { return this->_TailSize; };
		//..setters section
		inline void setXPos(i32 sXPos) { this->_XPos = sXPos; };
		inline void setYPos(i32 sYPos) { this->_YPos = sYPos; };
		//inline void setTailX(i32 xPos, i32 xVal) { this->_SnakeTailX[xPos] = xVal; };
		//inline void setTailY(i32 yPos, i32 yVal) { this->_SnakeTailY[yPos] = yVal; };
		//..tail size increment
		inline void tailSizeInc() { this->_TailSize++; };
	public:
		std::vector<i32> _SnakeTailX;
		std::vector<i32> _SnakeTailY;
	private:
		//..snake elements position holder
		i32 _XPos{ 0 };
		i32 _YPos{ 0 };
		//..tail data holder
		// TODO: change this to the vector
		//i32* _SnakeTailX{ new int[0] };
		//i32* _SnakeTailY{ new int[0] };
		i32 _TailSize{ 0 };
	};

}