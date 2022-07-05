//
// Created by asus on 2022/7/3.
//

#ifndef SNAKEGAME_MOCK_FOOD_H
#define SNAKEGAME_MOCK_FOOD_H

//TODO::丰富功能，然后在game的moveSnakes的checkEatFood后面里实现与蛇的交互（改变蛇的一些参数之类）
class Food {
public:
    Food(int x, int y);
    Food(const Food& f);

    int getX() const;
    int getY() const;

private:
    int x, y;

};


#endif //SNAKEGAME_MOCK_FOOD_H
