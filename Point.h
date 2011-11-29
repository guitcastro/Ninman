/*
 * File:   Point.h
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 19:54
 */

#ifndef POINT_H
#define	POINT_H

class Point {
public:
    Point();
    Point(const Point& orig);
    Point(int x, int y);
    virtual ~Point();
    int x;
    int y;
};

#endif	/* POINT_H */

