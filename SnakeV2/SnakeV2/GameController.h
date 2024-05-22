#pragma once
#include "Field.h"
#include "Snake.h"
#include "Consts.h"
class GameController
{
	public:
		GameController(int, int);

		void Render();

		void Action(sg::SnakeDirection);

		bool IsGameOver();

	private:
		Field field;
		Snake snake;

		bool gameOver = false;
};

