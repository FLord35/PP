#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <windows.h>
#include <queue>
#include <conio.h>

const int FIELD_MAX_ROWS = 10;
const int FIELD_MAX_COLUMNS = 10;

const int GAME_TICK_DURATION = 50; //Время обновления игрового поля

const int SNAKE_INITIAL_LENGTH = 3; //Включая голову и хвост

const std::string SIZE_DEFINITION_MESSAGE = "Введите количество строк и столбцов в игровом поле. Имейте в виду, что:";
const std::string ROWS_LENGTH_WARNING = "Значение строк не должно быть меньше ";
const std::string COLUMNS_LENGTH_WARNING = "Значение столбцов не должно быть меньше ";
const std::string WRONG_FIELD_SIZE_WARNING = "Пожалуйста, введите верные значения";

const int ARROW_KEY_CODE = 224; //Константы для стрелок на клавиатуре
const int UP_ARROW_KEY_CODE = 72;
const int DOWN_ARROW_KEY_CODE = 80;
const int LEFT_ARROW_KEY_CODE = 75;
const int RIGHT_ARROW_KEY_CODE = 77;

enum CellType
{ 
    EMPTY, 
    BORDER, 
    SNAKE_HEAD, 
    SNAKE_BODY, 
    SNAKE_TAIL, 
    FRUIT 
};

enum SnakeDirection
{
    UP    = 0,
    DOWN  = 1,
    LEFT  = 2,
    RIGHT = 3
};

struct Coordinates
{
    int x = 0;
    int y = 0;
};

struct Cell
{
    CellType type = EMPTY;
    Coordinates pos;
};

std::vector<std::vector<Cell>> PlaceFruit(std::vector<std::vector<Cell>> &field)
{
    srand(time(0));

    Coordinates pos = { rand() % (field[0].size() - 2) + 1, rand() % (field.size() - 2) + 1 };

    while (field[pos.y][pos.x].type != EMPTY)
    {
        if (pos.x < field[0].size())
            pos.x++;
        else if (pos.y < field.size())
            pos = { 1, pos.y++ }; 
        else
            pos = { 1, 1 };
    }
    field[pos.y][pos.x].type = FRUIT;

    return field;
}

bool IsFieldSizeValid(int &rows, int &columns)
{
    std::cin >> rows >> columns;

    if (rows < FIELD_MAX_ROWS || columns < FIELD_MAX_COLUMNS)
        return false;
    return true;
}

std::vector<std::vector<Cell>> FieldSetup(std::vector<std::vector<Cell>> &field, std::queue<Coordinates> &Snake)
{//TODO: Разбить функцию
    std::vector<std::vector<Cell>>::iterator rowIterator = field.begin();

    Coordinates pos;

    while (rowIterator != field.end())
    {
        std::vector<Cell> currentRow = *rowIterator;
        std::vector<Cell>::iterator columnIterator = currentRow.begin();

        pos.x = 0;

        while (columnIterator != currentRow.end())
        {
            if ((rowIterator == field.begin()) || (rowIterator == --field.end())) //Верхняя и нижняя границы поля
                columnIterator->type = BORDER;
            else if ((columnIterator == currentRow.begin()) || (columnIterator == --currentRow.end())) //Правая и левая границы поля
                columnIterator->type = BORDER;
            else
                columnIterator->type = EMPTY;

            columnIterator->pos.x = pos.x;
            columnIterator->pos.y = pos.y;
            pos.x++;
            ++columnIterator;
        }
        *rowIterator = currentRow;

        pos.y++;
        ++rowIterator;
    }

    pos = {static_cast <int> (field[0].size() / 2), static_cast <int> (field.size() - 2)};

    std::queue<Coordinates> snake;

    Snake.push(pos);
    field[pos.y][pos.x].type = SNAKE_TAIL;

    for (int i = 1; i < SNAKE_INITIAL_LENGTH - 1; i++)
    {
        Snake.push({ pos.x, pos.y - i });
        field[pos.y - i][pos.x].type = SNAKE_BODY;
    }

    Snake.push({ pos.x, pos.y - SNAKE_INITIAL_LENGTH + 1 });
    field[pos.y - SNAKE_INITIAL_LENGTH + 1][pos.x].type = SNAKE_HEAD;

    field = PlaceFruit(field);

    return field;
}

char GetCellSymbol(CellType type, std::map<CellType, char> table) //TODO: вынести таблицу в константу
{
    for (auto &it : table) //TODO: убрать for, итератор не нужен, обращение идёт по ключу
    {
        if (type == it.first)
            return it.second;
    }
    return 'E'; //Значение в случае ошибки
}

void FieldRendering(std::vector<std::vector<Cell>> &field)
{
    int xRenderPos;
    int yRenderPos;

    static std::map<CellType, char> symbolRenderTable = 
    {
        {EMPTY, ' '},
        {BORDER, '#'},
        {SNAKE_HEAD, '0'},
        {SNAKE_BODY, '*'},
        {SNAKE_TAIL, '*'},
        {FRUIT, '6'}
    };

    for (yRenderPos = 0; yRenderPos < field.size(); yRenderPos++)
    {
        for (xRenderPos = 0; xRenderPos < field[0].size(); xRenderPos++) //TODO: возможно использовать copy
            std::cout << ' ' << GetCellSymbol(field[yRenderPos][xRenderPos].type, symbolRenderTable);

        std::cout << std::endl;
    }
}

SnakeDirection DefineNewDirection()
{
    int command = _getch();
    if (command == ARROW_KEY_CODE)
    {
        command = _getch();
    }
    switch (command)
    {
    case LEFT_ARROW_KEY_CODE:
        return LEFT;
    case RIGHT_ARROW_KEY_CODE:
        return RIGHT;
    case UP_ARROW_KEY_CODE:
        return UP;
    case DOWN_ARROW_KEY_CODE:
        return DOWN;
    default:
        return UP;
    }
}

bool Action(std::vector<std::vector<Cell>> &field, SnakeDirection dir, std::queue<Coordinates> &snake)
{ 
    //Вычисление последствий одного действия
    //TODO: переименовать функцию для соответствия типу bool, разбить функцию
    Coordinates snakeHeadPosition = snake.back();
    bool isFruit = false;

    switch (dir)
    {
        case UP:
            snakeHeadPosition = { snakeHeadPosition.x, snakeHeadPosition.y - 1 };
            break;
        case DOWN:
            snakeHeadPosition = { snakeHeadPosition.x, snakeHeadPosition.y + 1 };
            break;
        case LEFT:
            snakeHeadPosition = { snakeHeadPosition.x - 1, snakeHeadPosition.y };
            break;
        case RIGHT:
            snakeHeadPosition = { snakeHeadPosition.x + 1, snakeHeadPosition.y };
            break;
    }

    switch (field[snakeHeadPosition.y][snakeHeadPosition.x].type)
    {
        case EMPTY:
            break;
        case BORDER:
            return true;
        case SNAKE_BODY:
            return true;
        case SNAKE_TAIL:
            return true;
        case FRUIT:
            isFruit = true;
    }

    field[snake.back().y][snake.back().x].type = SNAKE_BODY;
    field[snakeHeadPosition.y][snakeHeadPosition.x].type = SNAKE_HEAD;
    snake.push(snakeHeadPosition);

    if (!isFruit)
    {
        field[snake.front().y][snake.front().x].type = EMPTY;
        snake.pop();
    }
    else
        field = PlaceFruit(field);

    return false;
}

void GameLoop(std::vector<std::vector<Cell>> &field, std::queue<Coordinates> &snake) 
{
    SnakeDirection direction = UP;
    bool gameOver = false;

    system("cls");

    while (!gameOver)
    {
        COORD position = { 0, 0 };
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //TODO: вынести в отдельную функцию
        SetConsoleCursorPosition(hConsole, position);

        FieldRendering(field);
        Sleep(GAME_TICK_DURATION);
        if (_kbhit()) //TODO: Перенести в DefineNewDirection()
        {
            SnakeDirection newDir = DefineNewDirection();
            if (!(direction + newDir == 1 || direction + newDir == 5)) //Проверка на противоположные направления
                direction = newDir; //TODO: организовать читабельность if-а
        }
        gameOver = Action(field, direction, snake);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //TODO: переименование переменных
    int fieldRowQuantity;
    int fieldColumnQuantity;
    //TODO: вынести в отдельную функцию запрос размера поля
    std::cout << SIZE_DEFINITION_MESSAGE << std::endl
        << ROWS_LENGTH_WARNING << FIELD_MAX_ROWS << std::endl
        << COLUMNS_LENGTH_WARNING << FIELD_MAX_COLUMNS << std::endl;

    while (!IsFieldSizeValid(fieldRowQuantity, fieldColumnQuantity))
        std::cout << WRONG_FIELD_SIZE_WARNING << std::endl;

    std::vector<std::vector<Cell>> field(fieldRowQuantity, std::vector<Cell>(fieldColumnQuantity));
    std::queue<Coordinates> snake;

    field = FieldSetup(field, snake);

    GameLoop(field, snake);

    return 0;
}