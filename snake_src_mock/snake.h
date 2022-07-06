#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

enum class Direction
{
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3,
};

class SnakeBody
{
public:
    SnakeBody();
    SnakeBody(int x, int y);
    SnakeBody(const SnakeBody& s);
    int getX() const;
    int getY() const;
    bool operator== (const SnakeBody& snakeBody);
private:
    int mX;
    int mY;
};

// Snake class should have no depency on the GUI library
class Snake
{
public:
    bool state = true; //true:alive; false:dead

    //Snake();
    Snake(int x, int y, int initialSnakeLength);

    bool isPartOfSnake(int x, int y);

    bool changeDirection(Direction newDirection);

    std::vector<SnakeBody>& getSnake();
    int getLength();
    inline Direction getDirection() { return mDirection; }

    SnakeBody createNewHead();
    bool deleteTail();

private:
    // Snake information
    const int mInitialSnakeLength;
    Direction mDirection;
    std::vector<SnakeBody> mSnake;

    int speed = 1;

};

#endif
