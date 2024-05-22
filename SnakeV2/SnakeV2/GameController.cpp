#include "GameController.h"

GameController::GameController(int rowQuantity, int columnQuantity) :
	field(rowQuantity, columnQuantity),
	snake(rowQuantity, columnQuantity)
{
	field.PlaceFruit();
}

void GameController::Render()
{
	field.Render(snake);
}

void GameController::Action(sg::SnakeDirection dir)
{
	snake.Move(dir);

	if (field.IsCollisionPresent(snake.GetHeadPos()))
		gameOver = true;

	if (!field.IsFruitPresent(snake.GetHeadPos()))
	{
		field.DeleteOldTail(snake.GetTailPos());
		snake.Decay();
	}
	else
		field.PlaceFruit();
}

bool GameController::IsGameOver()
{
	return gameOver;
}
