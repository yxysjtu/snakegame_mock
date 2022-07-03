//
// Created by asus on 2022/7/3.
//

#ifndef SNAKEGAME_MOCK_FOOD_H
#define SNAKEGAME_MOCK_FOOD_H


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
