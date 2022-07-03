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

Snake::Snake(int gameBoardWidth, int gameBoardHeight, int initialSnakeLength): mGameBoardWidth(gameBoardWidth), mGameBoardHeight(gameBoardHeight), mInitialSnakeLength(initialSnakeLength)
{
    this->initializeSnake();
    this->setRandomSeed();
}

void Snake::setRandomSeed()
{
    // use current time as seed for random generator
    std::srand(std::time(nullptr));
}

void Snake::initializeSnake()
{
    // Instead of using a random initialization algorithm
    // We always put the snake at the center of the game mWindows
    int centerX = this->mGameBoardWidth / 2;
    int centerY = this->mGameBoardHeight / 2;

    for (int i = 0; i < this->mInitialSnakeLength; i ++)
    {
        this->mSnake.push_back(SnakeBody(centerX, centerY + i));
    }
    this->mDirection = Direction::Up;
}

bool Snake::isPartOfSnake(int x, int y)
{
    SnakeBody temp(x, y);
    for(SnakeBody& body: mSnake){
        if(body == temp) return true;
    }
    return false;
}

/*
 * Assumption:
 * Only the head would hit wall.
 */
bool Snake::hitWall()
{
    int x = mSnake[0].getX(), y = mSnake[0].getY();
    if(x >= mGameBoardWidth || x <= 0 || y >= mGameBoardHeight || y <= 0) return true;
    return false;
}

/*
 * The snake head is overlapping with its body
 */
bool Snake::hitSelf()
{
    for(int i = 1; i < mSnake.size(); i++){
        if(mSnake[i] == mSnake[0]) return true;
    }
    return false;
}

bool Snake::hitOthers(Snake* s)
{
    if(s == this) return false;
    std::vector<SnakeBody>& snake = s->getSnake();
    for(int i = 0; i < mSnake.size(); i++){
        if(mSnake[i] == snake[0]) return true;
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

