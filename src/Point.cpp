/*
 * File:   Point.cpp
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 19:54
 */

#include "header/Point.h"

Point::Point() {
    this->x=0;
    this->y=0;
}

Point::Point(const Point& orig) {
}

Point::~Point() {
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Point::operator==(Point &point) {
    return (this->x == point.x && this->y == point.y);
}
