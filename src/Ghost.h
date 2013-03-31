#ifndef GHOST_H
#define	GHOST_H

#include <allegro.h>
#include <string>
#include <list>
#include <stdio.h>

#include "Point.h"
#include "NinManMap.h"

#define TRANSPARENTE makecol (255 ,0 ,255)

class Ghost : public Point{

    private:
        NinManMap* map;

        std::list<Point> ghost_path;
        bool alreadyInList(Point p);

public:

    Ghost();
    Ghost(NinManMap * map);
    Ghost(const Ghost& orig);
    virtual ~Ghost();
    BITMAP * Bit_ghost;
    void setEyesBitmap ();
    void setWhiteBitmap ();
    void setBitmap (int x, int y);
    void move (Point ninman);
    void calcPath(Point ninman);
    int ManhattanDist(Point a,Point b);
};

#endif	/* GHOST_H */

