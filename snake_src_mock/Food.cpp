//
// Created by asus on 2022/7/3.
//

#include "Food.h"

Food::Food(int x, int y): x(x), y(y) {}

Food::Food(const Food &f) {
    x = f.x;
    y = f.y;
}

int Food::getX() const {
    return x;
}

int Food::getY() const {
    return y;
}
