/*
 * File:   NinManMap.h
 * Author: guilherme
 *
 * Created on 30 de Março de 2013, 11:43
 */

#ifndef NINMANMAP_H
#define	NINMANMAP_H

#include <string>
#include <fstream>
#include <stack>
#include <stdlib.h>
#include "Point.h"

class NinManMap {
public:

    // constructors and destructors

    NinManMap(const char* file_name);
    NinManMap(const NinManMap& orig);
    virtual ~NinManMap();

    // methods

    bool isValidCoordinate(int x,int y);
    bool replacePointValue(char oldValue,char newValue);

    void showFruit();
    void  setPointValue(int x,int y,char value);

    // getters

    Point getNinmanInitialPosition();

    Point getOrangeGhostInitialPosition();
    Point getBlueGhostInitialPosition();
    Point getPinkGhostInitialPosition();
    Point getRedGhostInitialPosition();
    Point getGreenGhostInitialPosition();

    char getPointValue(int x, int y);
    size_t getNumberOfLines();
    size_t getNumberOfColumns();
    size_t getNumberOfDots();

private:
    std::string* matrix;

    Point ninmanInitialPosition;

    Point orangeGhostInitialPosition;
    Point blueGhostInitialPosition;
    Point pinkGhostInitialPosition;
    Point redGhostInitialPosition;
    Point greenGhostInitialPosition;

    size_t numberOfLines;
    size_t numberOfDots;
};

#endif	/* NINMANMAP_H */

