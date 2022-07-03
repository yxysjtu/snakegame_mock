#ifndef GAME_H
#define GAME_H

#include <curses.h>
#include <string>
#include <vector>
#include <memory>

#include "snake.h"
#include "food.h"


class Game
{
public:
    Game();
    ~Game();
    
    void createInformationBoard();
    void renderInformationBoard() const;

    void createGameBoard();
    void renderGameBoard() const;
    
    void createInstructionBoard();
    void renderInstructionBoard() const;
		
    void loadLeadBoard();
    void updateLeadBoard();
    bool readLeaderBoard();
    bool updateLeaderBoard();
    bool writeLeaderBoard();
    void renderLeaderBoard() const;
    
    void renderBoards() const;

    void initializeGame();
    void runGame();
    void renderPoints() const;
    void renderDifficulty() const;
    
    Food createRamdonFood();
    void renderFood() const;
    void renderSnake() const;
    void controlSnake() const;
    
    void startGame();
    bool renderRestartMenu() const;
    void adjustDelay();

private:
    // We need to have two windows
    // One is for game introduction
    // One is for game mWindows
    int mScreenWidth;
    int mScreenHeight;
    int mGameBoardWidth;
    int mGameBoardHeight;
    const int mInformationHeight = 6;
    const int mInstructionWidth = 18;
    std::vector<WINDOW *> mWindows;

    // Snake information
    const int mInitialSnakeLength = 2;
    std::vector<Snake*> snakes;
    const char mSnakeSymbol = '@';
    // Food information
    std::vector<Food> foods; //can add more food and different food for future implementation
    const char mFoodSymbol = '#';

    //game info
    int mPoints[3] = {0};
    int mDifficulty = 0;
    int mBaseDelay = 100;
    int mDelay = 100;
    const std::string mRecordBoardFilePath = "record.dat";
    std::vector<int> mLeaderBoard;
    const int mNumLeaders = 3;

    bool checkCollision(int x, int y);//for generate food
    bool checkEatFood(int x, int y); //input:snake head
    bool checkSnakeCollision(Snake* s);

    void moveSnakes();

};

#endif
