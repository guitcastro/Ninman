/*
 * File:   Point.cpp
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 19:54
 */

#include "Point.h"

Point::Point() {
}

Point::Point(const Point& orig) {
    this->x = orig.x;
    this->y = orig.y;
}

Point::~Point() {
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

void Point::setPoint(Point p){
    this->x = p.x;
    this->y = p.y;
}