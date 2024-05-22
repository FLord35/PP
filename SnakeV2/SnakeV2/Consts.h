#pragma once
#include <string>
#include <map>

namespace sg
{
	const int FIELD_MAX_ROWS = 10;
	const int FIELD_MAX_COLUMNS = 10;

	const int GAME_TICK_DURATION = 250; //����� ���������� �������� ����

	const int SNAKE_INITIAL_LENGTH = 3; //������� ������ � �����

	const std::string SIZE_DEFINITION_MESSAGE = "������� ���������� ����� � �������� � ������� ����. ������ � ����, ���:";
	const std::string ROWS_LENGTH_WARNING = "�������� ����� �� ������ ���� ������ ";
	const std::string COLUMNS_LENGTH_WARNING = "�������� �������� �� ������ ���� ������ ";
	const std::string WRONG_FIELD_SIZE_WARNING = "����������, ������� ������ ��������";

	const int ARROW_KEY_CODE = 224; //��������� ��� ������� �� ����������
	const int UP_ARROW_KEY_CODE = 72;
	const int DOWN_ARROW_KEY_CODE = 80;
	const int LEFT_ARROW_KEY_CODE = 75;
	const int RIGHT_ARROW_KEY_CODE = 77;

	struct Coordinates
	{
		int x = 0;
		int y = 0;

		bool operator!= (const Coordinates& coords) const //const � ����� - ������� �� ����� ������ �������� �������
		{
			return ((x != coords.x) || (y != coords.y));
		}
	};

	enum CellType
	{
		EMPTY,
		BORDER,
		SNAKE_HEAD,
		SNAKE_BODY,
		SNAKE_TAIL,
		FRUIT
	};

	struct Cell
	{
		CellType type = EMPTY;
		sg::Coordinates pos;
	};

	enum SnakeDirection
	{
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};

}

namespace
{
	std::map<sg::CellType, char> symbolRenderTable =
	{
		{sg::EMPTY, ' '},
		{sg::BORDER, '#'},
		{sg::SNAKE_HEAD, '0'},
		{sg::SNAKE_BODY, '*'},
		{sg::SNAKE_TAIL, '*'},
		{sg::FRUIT, '6'}
	};
}