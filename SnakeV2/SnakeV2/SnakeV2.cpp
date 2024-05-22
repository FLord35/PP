#include <iostream>
#include <windows.h>
#include <conio.h>
#include "GameController.h"
#include "Consts.h"

//TODO: методы выше main убрать/перенести?

bool IsFieldSizeValid(int& rows, int& columns)
{
    std::cin >> rows >> columns;

    if (rows < sg::FIELD_MAX_ROWS || columns < sg::FIELD_MAX_COLUMNS)
        return false;
    return true;
}

bool AreOppositeDirections(sg::SnakeDirection dir1, sg::SnakeDirection dir2)
{
    //UP + DOWN = 1
    //LEFT + RIGHT = 5
    return ((dir1 + dir2 == 1) || (dir1 + dir2 == 5));
}

sg::SnakeDirection DefineNewDirection(sg::SnakeDirection &direction)
{
    if (_kbhit())
    {
        sg::SnakeDirection newDir;

        int command = _getch();
        if (command == sg::ARROW_KEY_CODE)
        {
            command = _getch();
        }
        switch (command)
        {
            case sg::LEFT_ARROW_KEY_CODE:
                newDir = sg::LEFT;
                break;
            case sg::RIGHT_ARROW_KEY_CODE:
                newDir = sg::RIGHT;
                break;
            case sg::UP_ARROW_KEY_CODE:
                newDir = sg::UP;
                break;
            case sg::DOWN_ARROW_KEY_CODE:
                newDir = sg::DOWN;
                break;
            default:
                newDir = sg::UP;
                break;
        }

        if (!AreOppositeDirections(direction, newDir))//Проверка на противоположные направления 
            direction = newDir;
    }

    return direction;
}

void GetFieldSize(int &fieldRowQuantity, int &fieldColumnQuantity)
{
    std::cout << sg::SIZE_DEFINITION_MESSAGE << std::endl
        << sg::ROWS_LENGTH_WARNING << sg::FIELD_MAX_ROWS << std::endl
        << sg::COLUMNS_LENGTH_WARNING << sg::FIELD_MAX_COLUMNS << std::endl;

    while (!IsFieldSizeValid(fieldRowQuantity, fieldColumnQuantity))
        std::cout << sg::WRONG_FIELD_SIZE_WARNING << std::endl;
}

void ResetCursorPosition()
{
    COORD position = { 0, 0 };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, position);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int fieldRowQuantity;
    int fieldColumnQuantity;
    
    GetFieldSize(fieldRowQuantity, fieldColumnQuantity);

    GameController gameController(fieldRowQuantity, fieldColumnQuantity);
    sg::SnakeDirection direction = sg::UP;
    system("cls");

    while (gameController.IsGameOver() != true)
    {
        ResetCursorPosition();

        gameController.Render();

        Sleep(sg::GAME_TICK_DURATION);

        direction = DefineNewDirection(direction); //TODO: вынести в GameController

        gameController.Action(direction);
    }

    return 0;
}
