#include "GD_GameData.h"

#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <thread>

#pragma comment(lib, "winmm.lib")

namespace GD
{
	GameData::GameData()
	{
		//..seed for the game
		std::srand(static_cast<u32>(std::time(0)));
		//..cmd window size
		std::string colsSize = std::to_string(this->_BoardWidth + 2);
		std::string rowsSize = std::to_string(this->_BoardHeight + 5);
		std::string completeCommand = "MODE con:cols=" + colsSize + " lines=" + rowsSize;
		system(completeCommand.c_str());

		// TODO: make separate class for the main loop;
		//..main game loop
		while (this->_GS != GameState::GAMEOVER)
		{
			if (this->_GS == GameState::MAINMENU) this->_MainMenu();
			//..game inititalization
			if (this->_Dir == Direction::UP || this->_Dir == Direction::DOWN)
			{
				// TODO: add game speed via this value;
				Sleep(25);
			}
			Sleep(this->_GameSpeed);
			//..input holder
			this->_KeyLogic();
			this->_GameInit();
			this->_GameLogic();
		}
		PlaySound(0, 0, 0);
		system("cls");
		std::cout << "\n\n\n\t\t\tGAME OVER\n"
			<< "\n\n\n\t\t\tScore:\t" << this->getScore() << "\n\n";
	}
	void GameData::_KeyLogic()
	{
		//..change snake direction depends on inputed key
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				if (this->_Dir != Direction::DOWN)
					this->_Dir = Direction::UP;
				break;
			case 's':
				if (this->_Dir != Direction::UP)
					this->_Dir = Direction::DOWN;
				break;
			case 'a':
				if (this->_Dir != Direction::RIGHT)
					this->_Dir = Direction::LEFT;
				break;
			case 'd':
				if (this->_Dir != Direction::LEFT)
					this->_Dir = Direction::RIGHT;
				break;
			case 27:
				this->_GS = GameState::MAINMENU;
				break;
			default:
				break;
			}
		}
	}
	void GameData::_MainMenu()
	{
		//..this one is awesome main menu screen
		// TODO: make text gui for the main menu
		system("cls");
		this->playTrack("bgm1.wav", GameState::MAINMENU);
		std::cout << "\n\n\t\tWelcome to the awesome snake game.\n\n\n"
			<< "\t\t\t1. New Game\n"
			<< "\t\t\t0. Exit\n";
		i32 userInput = 0;
		std::cin >> userInput;
		switch (userInput)
		{
		case 1:
			system("cls");
			this->_GS = GameState::START;
			break;
		case 0:
			system("cls");
			this->_GS = GameState::QUIT;
			break;
		default:
			system("cls");
			this->_GS = GameState::MAINMENU;
			break;
		}
	}
	void GameData::_GameInit()
	{
		//.. clear screen
		this->_ClearScreen();
		this->playTrack("bgm2.wav", GameState::START);
		//..draw top border
		this->_VertBorder("+", "-");
		//..draw game board
		for (i32 rows = 0; rows < this->_BoardHeight; ++rows)
		{
			for (i32 cols = 0; cols < this->_BoardWidth; ++cols)
			{
				//..print board data
				//..left border
				if (cols == 0)						std::cout << '|';
				//..inner space
				//..snake head
				if (rows == this->_snake.getYPos() && cols == this->_snake.getXPos())
					std::cout << '@';
				//..target
				else if (rows == this->_target.getYPos() && cols == this->_target.getXPos())
					std::cout << '#';
				//..snake tail
				else
				{
					bool isTail = false;
					for (i32 k = 0; k < this->_snake.getTailSize(); ++k)
					{
						//if (this->_snake.getSnakeTailX(k) == cols && this->_snake.getSnakeTailY(k) == rows)
						if (this->_snake._SnakeTailX[k] == cols && this->_snake._SnakeTailY[k] == rows)
						{
							std::cout << '@';
							isTail = true;
						}
					}
					if (!isTail) std::cout << ' ';
				}
				//..right border
				if (cols == this->_BoardWidth - 1)	std::cout << "|\n";
			}
		}
		this->_VertBorder("+", "-");
		//print the score
		std::cout << "\tScore:\t" << this->getScore() << std::endl;
	}
	void GameData::_GameLogic()
	{
		//..each itteration game keeps previous snake head position in tmp holders
		//..after this, change first elem of the snake to the new position (damn vectors)
		this->_snake._SnakeTailX.insert(this->_snake._SnakeTailX.begin(), this->_snake.getXPos());
		this->_snake._SnakeTailY.insert(this->_snake._SnakeTailY.begin(), this->_snake.getYPos());

		//..change snake head coordinates depending on input
		switch (this->_Dir)
		{
		case Direction::UP:
			this->_snake.setYPos(this->_snake.getYPos() - 1);
			break;
		case Direction::DOWN:
			this->_snake.setYPos(this->_snake.getYPos() + 1);
			break;
		case Direction::LEFT:
			this->_snake.setXPos(this->_snake.getXPos() - 1);
			break;
		case Direction::RIGHT:
			this->_snake.setXPos(this->_snake.getXPos() + 1);
			break;
		default:
			break;
		}

		//..detecte collisions
		this->isBody();
		this->isWall();
		this->isTarget();
	}
	void GameData::_ClearScreen() const
	{
		//..clear the screen and put cursor to 0,0
		COORD cursorPos{ 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
	}
	void GameData::_VertBorder(std::string outter, std::string inner) const
	{
		//..draw vertical border with given params
		i32 size = this->_BoardWidth + 2;
		for (i32 i = 0; i < size; ++i)
		{
			std::cout << ((i == 0 || i == size - 1) ? ((i == size - 1) ? outter + "\n" : outter) : inner);
		}
	}
	void GameData::_VertBorderWithText(std::string inner, std::string text, std::string outter) const
	{
		// TODO: finish
		i32 size = this->_BoardWidth + 2;
		for (i32 i = 0; i < size; ++i)
		{
			if (i == 0) std::cout << '|';
			if (i == 1) std::cout << ' ';
			std::cout << text;
			i32 textGap = 2 + static_cast<i32>(text.size());
			if (i > textGap && i < size - 2) std::cout << ' ';
			if (i == size - 1) std::cout << "|\n";
		}
	}
	void GameData::isWall()
	{
		//..check if wall hitted
		if (this->_snake.getXPos() == -1 || this->_snake.getXPos() == this->_BoardWidth) this->_GS = GameState::GAMEOVER;
		if (this->_snake.getYPos() == -1 || this->_snake.getYPos() == this->_BoardHeight) this->_GS = GameState::GAMEOVER;
	}
	void GameData::isBody()
	{
		//..check if head hit self body
		if (this->_snake.getTailSize() > 4)
		{
			for (i32 i = 0; i < this->_snake.getTailSize(); ++i)
			{
				if (this->_snake._SnakeTailX[i] == this->_snake.getXPos() && this->_snake._SnakeTailY[i] == this->_snake.getYPos())
					this->_GS = GameState::GAMEOVER;
			}
		}
	}
	void GameData::isTarget()
	{
		//..check if snake reach target and increase snake size
		if (this->_snake.getXPos() == this->_target.getXPos() && this->_snake.getYPos() == this->_target.getYPos())
		{
			this->setScore();
			//..generate new target
			this->_target.setXPos(rand() % this->_BoardWidth);
			this->_target.setYPos(rand() % this->_BoardHeight);
			//..check if target overlay snake
			for (i32 i = 0; i < this->_snake.getTailSize();)
			{
				bool isSnake = false;
				if (this->_snake._SnakeTailX[i] == this->_target.getXPos() && this->_snake._SnakeTailY[i] == this->_target.getYPos())
				{
					isSnake = true;
					this->_target.setXPos(rand() % this->_BoardWidth);
					this->_target.setYPos(rand() % this->_BoardHeight);
					break;
				}
				if (!isSnake) i++;
			}
			this->_snake.tailSizeInc();
			//..change game speed;
			if (this->_GameSpeed > 20) this->_GameSpeed -= 5;
		}
	}
	void GameData::playTrack(std::string soundName, GameState givenState)
	{
		//..play bgm sound
		std::string trackName = "bgm\\" + soundName;
		if (prev != givenState)
		{
			this->prev = givenState;
			PlaySound(TEXT(trackName.c_str()), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}
}