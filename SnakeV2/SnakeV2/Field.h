#pragma once
#include <vector>
#include "Snake.h"
#include "Consts.h"

class Field
{
	public:

		Field(int, int); //TODO: добавить деструктор, посмотреть, очищает ли динамические структуры
		void Render(const Snake&);

		bool IsCollisionPresent(const sg::Coordinates&);
		bool IsFruitPresent(const sg::Coordinates&);

		void PlaceFruit();
		void DeleteOldTail(const sg::Coordinates&);

	private:

		void SetSize(int, int);
		std::vector<std::vector<sg::Cell>> field;

		void RewriteSnakePositions(const Snake&);

};

