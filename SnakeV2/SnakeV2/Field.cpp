#include <iostream>
#include <map>
#include <queue>
#include <ctime>
#include "Field.h"
#include "Consts.h"

Field::Field(int rowQuantity, int columnQuantity)
{
    SetSize(rowQuantity, columnQuantity);

    std::vector<std::vector<sg::Cell>>::iterator rowIterator = field.begin();

    sg::Coordinates pos;

    while (rowIterator != field.end())
    {
        std::vector<sg::Cell> currentRow = *rowIterator;
        std::vector<sg::Cell>::iterator  columnIterator = currentRow.begin();

        pos.x = 0;

        while (columnIterator != currentRow.end())
        {
            if ((rowIterator == field.begin()) || (rowIterator == --field.end())) //Верхняя и нижняя границы поля
                columnIterator->type = sg::BORDER;
            else if ((columnIterator == currentRow.begin()) || (columnIterator == --currentRow.end())) //Правая и левая границы поля
                columnIterator->type = sg::BORDER;
            else
                columnIterator->type = sg::EMPTY;

            columnIterator->pos.x = pos.x;
            columnIterator->pos.y = pos.y;
            pos.x++;
            ++columnIterator;
        }
        *rowIterator = currentRow;

        pos.y++;
        ++rowIterator;
    }
}

void Field::SetSize(int rowQuantity, int columnQuantity)
{
    field.resize(rowQuantity, std::vector<sg::Cell>(columnQuantity));
}

void Field::RewriteSnakePositions(const Snake& snake)
{
    std::deque<sg::Coordinates> snakeQueue = snake.GetQueue();

    field[snakeQueue.back().y][snakeQueue.back().x].type = sg::SNAKE_HEAD;
    field[snakeQueue.front().y][snakeQueue.front().x].type = sg::SNAKE_TAIL;

    for (auto& it: snakeQueue)
    {
        if ((it != snakeQueue.front()) && (it != snakeQueue.back()))
            field[it.y][it.x].type = sg::SNAKE_BODY;
    }
}

void Field::Render(const Snake& snake)
{
    RewriteSnakePositions(snake);

    for (int yRenderPos = 0; yRenderPos < field.size(); yRenderPos++)
    {
        for (int xRenderPos = 0; xRenderPos < field[0].size(); xRenderPos++)
            std::cout << ' ' << symbolRenderTable[field[yRenderPos][xRenderPos].type];

        std::cout << std::endl;
    }
}

bool Field::IsCollisionPresent(const sg::Coordinates& headPos)
{
    switch (field[headPos.y][headPos.x].type)
    {
    case sg::EMPTY:
        return false;
    case sg::BORDER:
        return true;
    case sg::SNAKE_BODY:
        return true;
    case sg::SNAKE_TAIL:
        return true;
    case sg::FRUIT:
        return false;
    default:
        return false;
    }
}

bool Field::IsFruitPresent(const sg::Coordinates& headPos)
{
    return field[headPos.y][headPos.x].type == sg::FRUIT;
}

void Field::PlaceFruit()
{
    srand(time(0));

    sg::Coordinates pos;
    pos.x = (rand() % (field[0].size() - 2)) + 1;
    pos.y = (rand() % (field.size() - 2)) + 1;

    while (field[pos.y][pos.x].type != sg::EMPTY)
    {
        if (pos.x < field[0].size())
            pos.x++;
        else if (pos.y < field.size())
            pos = { 1, pos.y++ };
        else
            pos = { 1, 1 };
    }
    field[pos.y][pos.x].type = sg::FRUIT;
}

void Field::DeleteOldTail(const sg::Coordinates& tailPos)
{
    field[tailPos.y][tailPos.x].type = sg::EMPTY;
}
