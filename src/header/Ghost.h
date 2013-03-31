#ifndef GHOST_H
#define	GHOST_H

#include <allegro.h>
#include "Point.h"

#define TRANSPARENTE makecol (255 ,0 ,255)

class Ghost : public Point{
    
public:

    //constructors and destroyers

    Ghost();
    Ghost(const Ghost& orig);
    virtual ~Ghost();
    BITMAP * Bit_ghost;
    void setEyesBitmap ();
    void setWhiteBitmap ();
    void setBitmap (int x, int y);

};

#endif	/* GHOST_H */

