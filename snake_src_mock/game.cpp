#include <string>
#include <iostream>
#include <cmath> 

// For terminal delay
#include <chrono>
#include <thread>

#include <fstream>
#include <algorithm> 

#include "game.h"

//color considerations
#define FOOD_COLOR 0
#define SNAKE1_COLOR 1
#define SNAKE2_COLOR 2
#define SNAKE3_COLOR 3

Game::Game()
{
    // Separate the screen to three windows
    this->mWindows.resize(3);
    initscr();
    // If there wasn't any key pressed don't wait for keypress
    nodelay(stdscr, true);
    // Turn on keypad control
    keypad(stdscr, true);
    // No echo for the key pressed
    noecho();
    // No cursor show
    curs_set(0);
    // Get screen and board parameters
    getmaxyx(stdscr, this->mScreenHeight, this->mScreenWidth);
    this->mGameBoardWidth = this->mScreenWidth - this->mInstructionWidth;
    this->mGameBoardHeight = this->mScreenHeight - this->mInformationHeight;

    this->createInformationBoard();
    this->createGameBoard();
    this->createInstructionBoard();

    // Initialize the leader board to be all zeros
    this->mLeaderBoard.assign(this->mNumLeaders, 0);

    //color setting
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(FOOD_COLOR, COLOR_WHITE, COLOR_YELLOW);
    init_pair(SNAKE1_COLOR, COLOR_WHITE, COLOR_BLUE);
    init_pair(SNAKE2_COLOR, COLOR_WHITE, COLOR_GREEN);
    init_pair(SNAKE3_COLOR, COLOR_WHITE, COLOR_RED);
}

Game::~Game()
{
    //TODO::safe delete snake
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        delwin(this->mWindows[i]);
    }
    endwin();
}

void Game::createInformationBoard()
{
    int startY = 0;
    int startX = 0;
    this->mWindows[0] = newwin(this->mInformationHeight, this->mScreenWidth, startY, startX);
}

void Game::renderInformationBoard() const
{
    mvwprintw(this->mWindows[0], 1, 1, "Welcome to The Snake Game!");
    mvwprintw(this->mWindows[0], 2, 1, "This is a mock version.");
    mvwprintw(this->mWindows[0], 3, 1, "Please fill in the blanks to make it work properly!!");
    mvwprintw(this->mWindows[0], 4, 1, "Implemented using C++ and libncurses library.");
    wrefresh(this->mWindows[0]);
}

void Game::createGameBoard()
{
    int startY = this->mInformationHeight;
    int startX = 0;
    this->mWindows[1] = newwin(this->mScreenHeight - this->mInformationHeight, this->mScreenWidth - this->mInstructionWidth, startY, startX);
}

void Game::renderGameBoard() const
{
    wrefresh(this->mWindows[1]);
}

void Game::createInstructionBoard()
{
    int startY = this->mInformationHeight;
    int startX = this->mScreenWidth - this->mInstructionWidth;
    this->mWindows[2] = newwin(this->mScreenHeight - this->mInformationHeight, this->mInstructionWidth, startY, startX);
}

void Game::renderInstructionBoard() const
{
    mvwprintw(this->mWindows[2], 1, 1, "Manual");

    mvwprintw(this->mWindows[2], 3, 1, "Up: W");
    mvwprintw(this->mWindows[2], 4, 1, "Down: S");
    mvwprintw(this->mWindows[2], 5, 1, "Left: A");
    mvwprintw(this->mWindows[2], 6, 1, "Right: D");

    mvwprintw(this->mWindows[2], 8, 1, "Difficulty");
    mvwprintw(this->mWindows[2], 11, 1, "Points");

    wrefresh(this->mWindows[2]);
}


void Game::renderLeaderBoard() const
{
    // If there is not too much space, skip rendering the leader board 
    if (this->mScreenHeight - this->mInformationHeight - 14 - 2 < 3 * 2)
    {
        return;
    }
    mvwprintw(this->mWindows[2], 14, 1, "Leader Board");
    std::string pointString;
    std::string rank;
    for (int i = 0; i < std::min(this->mNumLeaders, this->mScreenHeight - this->mInformationHeight - 14 - 2); i ++)
    {
        pointString = std::to_string(this->mLeaderBoard[i]);
        rank = "#" + std::to_string(i + 1) + ":";
        mvwprintw(this->mWindows[2], 14 + (i + 1), 1, rank.c_str());
        mvwprintw(this->mWindows[2], 14 + (i + 1), 5, pointString.c_str());
    }
    wrefresh(this->mWindows[2]);
}

bool Game::renderRestartMenu() const
{
    WINDOW * menu;
    int width = this->mGameBoardWidth * 0.5;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25 + this->mInformationHeight;

    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);
    std::vector<std::string> menuItems = {"Restart", "Quit"};

    int index = 0;
    int offset = 4;
    mvwprintw(menu, 1, 1, "Your Final Score:");
    std::string pointString = std::to_string(this->mPoints[0]);
    mvwprintw(menu, 2, 1, pointString.c_str());
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 0 + offset, 1, menuItems[0].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 1 + offset, 1, menuItems[1].c_str());

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        switch(key)
        {
            case 'W':
            case 'w':
            case KEY_UP:
            {
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
            case 'S':
            case 's':
            case KEY_DOWN:
            {
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
        }
        wrefresh(menu);
        if (key == ' ' || key == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delwin(menu);

    if (index == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void Game::renderPoints() const
{
    std::string pointString = std::to_string(this->mPoints[0]);
    mvwprintw(this->mWindows[2], 12, 1, pointString.c_str());
    wrefresh(this->mWindows[2]);
}

void Game::renderDifficulty() const
{
    std::string difficultyString = std::to_string(this->mDifficulty);
    mvwprintw(this->mWindows[2], 9, 1, difficultyString.c_str());
    wrefresh(this->mWindows[2]);
}

void Game::initializeGame()
{
    // allocate memory for a new snake
    //this->mPtrSnake.reset(new Snake(this->mGameBoardWidth, this->mGameBoardHeight, this->mInitialSnakeLength));
    //TODO::implement multiple player mode
    mPoints[0] = 0; mPoints[1] = 0; mPoints[2] = 0;
    mDifficulty = 0;

    snakes.clear();
    foods.clear();

    snakes.push_back(new Snake(mGameBoardWidth, mGameBoardHeight, mInitialSnakeLength));
    foods.push_back(createRamdonFood());

}

bool Game::checkCollision(int x, int y) {
    for(Snake* snake : snakes){
        if(snake->isPartOfSnake(x, y)) return true;
    }
    return false;
}

Food Game::createRamdonFood()
{
    //generate random position
    int x = rand() % mGameBoardWidth;
    int y = rand() % mGameBoardHeight;
    while(checkCollision(x, y)){
        x = rand() % mGameBoardWidth;
        y = rand() % mGameBoardHeight;
    }
    return Food(x, y);
}

void Game::renderFood() const
{
    attron(COLOR_PAIR(FOOD_COLOR));
    for(const Food& food: foods){
        mvwaddch(this->mWindows[1], food.getY(), food.getX(), this->mFoodSymbol);
    }
    attroff(COLOR_PAIR(FOOD_COLOR));
    wrefresh(this->mWindows[1]);
}

void Game::renderSnake() const
{
    for(int s = 0; s < snakes.size(); s++){
        if(snakes[s]->state){
            int snakeLength = snakes[s]->getLength();
            std::vector<SnakeBody>& snake = snakes[s]->getSnake();
            attron(COLOR_PAIR(s + 1));
            for (int i = 0; i < snakeLength; i ++){
                mvwaddch(this->mWindows[1], snake[i].getY(), snake[i].getX(), this->mSnakeSymbol);
            }
            attroff(COLOR_PAIR(s + 1));
        }
    }
    wrefresh(this->mWindows[1]);
}

void Game::controlSnake() const
{
    int key;
    key = getch();
    switch(key)
    {
        case 'W':
        case 'w':
        case KEY_UP:
            snakes[0]->changeDirection(Direction::Up);
            break;
        case 'S':
        case 's':
        case KEY_DOWN:
            snakes[0]->changeDirection(Direction::Down);
            break;
        case 'A':
        case 'a':
        case KEY_LEFT:
            snakes[0]->changeDirection(Direction::Left);
            break;
        case 'D':
        case 'd':
        case KEY_RIGHT:
            snakes[0]->changeDirection(Direction::Right);
            break;
        default: break;
    }
}

void Game::renderBoards() const
{
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        werase(this->mWindows[i]);
    }
    this->renderInformationBoard();
    this->renderGameBoard();
    this->renderInstructionBoard();
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        box(this->mWindows[i], 0, 0);
        wrefresh(this->mWindows[i]);
    }
    this->renderLeaderBoard();
}


void Game::adjustDelay()
{
    this->mDifficulty = this->mPoints[0] / 5;
    if (mPoints[0] % 5 == 0)
    {
        this->mDelay = this->mBaseDelay * pow(0.75, this->mDifficulty);
    }
}

void Game::runGame()
{

    while (true)
    {
        /* TODO
         * this is the main control loop of the game.
         * it keeps running a while loop, and does the following things:
         * 	1. process your keyboard input
         * 	2. clear the window
         * 	3. move the current snake forward
         * 	4. check if the snake has eaten the food after movement
         * 	5. check if the snake dies after the movement
         * 	6. make corresponding steps for the ``if conditions'' in 3 and 4.
         *   7. render the position of the food and snake in the new frame of window.
         *   8. update other game states and refresh the window
         */
        this->controlSnake();
        werase(mWindows[1]);

        //TODO::get other snakes' information via server
        moveSnakes();

        this->renderSnake();
        this->renderFood();

        adjustDelay();
        renderPoints();
        renderDifficulty();

        //TODO::there's seems a problem with the delay function
        //std::this_thread::sleep_for(std::chrono::milliseconds(this->mDelay));
        _sleep(mDelay);

        refresh();

        if(snakes[0]->state == false) break;
    }
}

void Game::startGame()
{
    refresh();
    bool choice;
    while (true)
    {
        this->readLeaderBoard();
        this->renderBoards();
        this->initializeGame();
        this->runGame();
        this->updateLeaderBoard();
        this->writeLeaderBoard();
        choice = this->renderRestartMenu();
        if (choice == false)
        {
            break;
        }
    }
}

// https://en.cppreference.com/w/cpp/io/basic_fstream
bool Game::readLeaderBoard()
{
    std::fstream fhand(this->mRecordBoardFilePath, fhand.binary | fhand.in);
    if (!fhand.is_open())
    {
        return false;
    }
    int temp;
    int i = 0;
    while ((!fhand.eof()) && (i < mNumLeaders))
    {
        fhand.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        this->mLeaderBoard[i] = temp;
        i ++;
    }
    fhand.close();
    return true;
}

bool Game::updateLeaderBoard()
{
    bool updated = false;
    int newScore = this->mPoints[0];
    for (int i = 0; i < this->mNumLeaders; i ++)
    {
        if (this->mLeaderBoard[i] >= this->mPoints[0])
        {
            continue;
        }
        int oldScore = this->mLeaderBoard[i];
        this->mLeaderBoard[i] = newScore;
        newScore = oldScore;
        updated = true;
    }
    return updated;
}

bool Game::writeLeaderBoard()
{
    // trunc: clear the data file
    std::fstream fhand(this->mRecordBoardFilePath, fhand.binary | fhand.trunc | fhand.out);
    if (!fhand.is_open())
    {
        return false;
    }
    for (int i = 0; i < this->mNumLeaders; i ++)
    {
        fhand.write(reinterpret_cast<char*>(&this->mLeaderBoard[i]), sizeof(this->mLeaderBoard[i]));;
    }
    fhand.close();
    return true;
}

bool Game::checkEatFood(int x, int y) {
    for(int i = 0; i < foods.size(); i++){
        if(foods[i].getX() == x && foods[i].getY() == y){
            foods[i] = createRamdonFood();
            return true;
        }
    }
    return false;
}

bool Game::checkSnakeCollision(Snake* snake) {
    if (snake->hitWall() || snake->hitSelf()) return true;
    for(Snake* s: snakes){
        if(s->state && snake->hitOthers(s)) return true;
    }
    return false;
}

void Game::moveSnakes() {
    for(int i = 0; i < snakes.size(); i++){
        if(snakes[i]->state){ //alive
            SnakeBody head = snakes[i]->createNewHead();
            if(checkEatFood(head.getX(), head.getY())){
                mPoints[i]++;
            }else{
                snakes[i]->deleteTail();
            }
            if(checkSnakeCollision(snakes[i])) snakes[i]->state = false;
        }
    }
}








