#pragma once
#include <queue>
#include "Consts.h"

class Snake
{
	public:
        Snake(int, int);
        
        sg::SnakeDirection snakeDirection = sg::UP;

        void Move(sg::SnakeDirection);

        void Decay(); 

        const std::deque<sg::Coordinates> &GetQueue() const;

        const sg::Coordinates& GetHeadPos() const;
        const sg::Coordinates& GetTailPos() const;

	private:
        std::deque<sg::Coordinates> snake;

};

