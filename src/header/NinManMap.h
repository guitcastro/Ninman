/*
 * File:   NinManMap.h
 * Author: guilherme
 *
 * Created on 12 de Março de 2012, 21:03
 */


#ifndef NINMANMAP_H
#define	NINMANMAP_H
//C
#include <stdlib.h>
//C++
#include <string>
#include <fstream>
#include <stack>
//local
#include "Point.h"

class NinManMap {
public:
    NinManMap();
    NinManMap(const NinManMap& orig);
    virtual ~NinManMap();
    Point * findPoint(char searchFor);
    void setPoint(Point point, char value);
    static void newFruit();

    /**
     * load the map from a text file
     */
    static void loadLab(const char* file_name);
    
    static unsigned int getColumnsSize();
    static unsigned int getLinesSize();
    static std::string * matrix;
private:
    static unsigned int numberOfLines;
    static unsigned int numberOfColumns;
};

#endif	/* NINMANMAP_H */

