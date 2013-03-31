/*
 * File:   Fruit.h
 * Author: guilherme
 *
 * Created on 14 de Dezembro de 2011, 14:55
 */

#ifndef FRUIT_H
#define	FRUIT_H

#include "Point.h"

class Fruit : public Point{
public:
    Fruit();
    Fruit(const Fruit& orig);
    virtual ~Fruit();
private:

};

#endif	/* FRUIT_H */

