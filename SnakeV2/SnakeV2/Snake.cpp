#include "Snake.h"

Snake::Snake(int rowQuantity, int columnQuantity)
{
    sg::Coordinates pos = { static_cast <int> (rowQuantity / 2), static_cast <int> (columnQuantity - 2) };

    snake.push_front(pos);

    for (int i = 1; i < sg::SNAKE_INITIAL_LENGTH - 1; i++)
    {
        snake.push_back({ pos.x, pos.y - i });
    }

    snake.push_back({ pos.x, pos.y - sg::SNAKE_INITIAL_LENGTH + 1 });
}

void Snake::Move(sg::SnakeDirection dir)
{
    sg::Coordinates snakeHeadPosition = snake.back();

    switch (dir)
    {
        case sg::UP:
            snakeHeadPosition = { snakeHeadPosition.x, snakeHeadPosition.y - 1 };
            break;
        case sg::DOWN:
            snakeHeadPosition = { snakeHeadPosition.x, snakeHeadPosition.y + 1 };
            break;
        case sg::LEFT:
            snakeHeadPosition = { snakeHeadPosition.x - 1, snakeHeadPosition.y };
            break;
        case sg::RIGHT:
            snakeHeadPosition = { snakeHeadPosition.x + 1, snakeHeadPosition.y };
            break;
    }

    snake.push_back(snakeHeadPosition);
}

void Snake::Decay()
{
    snake.pop_front();
}

const std::deque<sg::Coordinates>& Snake::GetQueue() const
{
    return snake;
}

const sg::Coordinates& Snake::GetHeadPos() const
{
    return snake.back();
}

const sg::Coordinates& Snake::GetTailPos() const
{
    return snake.front();
}
