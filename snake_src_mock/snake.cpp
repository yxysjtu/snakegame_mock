#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "snake.h"


SnakeBody::SnakeBody()
{
}


SnakeBody::SnakeBody(int x, int y): mX(x), mY(y)
{
}

SnakeBody::SnakeBody(const SnakeBody& s){
    mX = s.getX();
    mY = s.getY();
}

int SnakeBody::getX() const
{
    return mX;
}

int SnakeBody::getY() const
{
    return mY;
}

bool SnakeBody::operator== (const SnakeBody& snakeBody)
{
	return mX == snakeBody.mX && mY == snakeBody.mY;
}

Snake::Snake(int x, int y, int initialSnakeLength): mInitialSnakeLength(initialSnakeLength)
{
    for (int i = 0; i < this->mInitialSnakeLength; i ++)
    {
        this->mSnake.push_back(SnakeBody(x, y + i));
    }
    this->mDirection = Direction::Up;
    // use current time as seed for random generator
    std::srand(std::time(nullptr));
}


bool Snake::isPartOfSnake(int x, int y)
{
    SnakeBody temp(x, y);
    for(SnakeBody& body: mSnake){
        if(body == temp) return true;
    }
    return false;
}

std::vector<SnakeBody>& Snake::getSnake()
{
    return this->mSnake;
}

bool Snake::changeDirection(Direction newDirection)
{
    if((mDirection == Direction::Up && newDirection == Direction::Down) || (mDirection == Direction::Down && newDirection == Direction::Up)
    || (mDirection == Direction::Left && newDirection == Direction::Right) || (mDirection == Direction::Right && newDirection == Direction::Left)){
        return false;
    }
    mDirection = newDirection;
    return true;
}


SnakeBody Snake::createNewHead()
{
    const SnakeBody& oriHead = mSnake[0];
    int x = oriHead.getX(), y = oriHead.getY();
    int moveDist = 1;
    switch (mDirection) {
        case Direction::Up: y -= moveDist; break;
        case Direction::Down: y += moveDist; break;
        case Direction::Left: x -= moveDist; break;
        case Direction::Right: x += moveDist; break;
        default: break;
    }
    SnakeBody newHead(x, y);
    mSnake.insert(mSnake.begin(), newHead);
    return newHead;
}

bool Snake::deleteTail(){
    if(mSnake.size() <= 1) return false;
    mSnake.pop_back();
    return true;
}


int Snake::getLength()
{
    return this->mSnake.size();
}

