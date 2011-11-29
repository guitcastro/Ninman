/*
 * File:   Ninman.h
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 23:12
 */

#ifndef NINMAN_H
#define	NINMAN_H

#include <allegro.h>
#include "Point.h"
#include "Thread.h"

#define TRANSPARENTE makecol (255 ,0 ,255)
#define subiu 1
#define desceu -1
#define direita 2
#define esquerda -2

class Ninman : public Point, public Thread {
public:
    Ninman();
    Ninman(const Ninman& orig);
    virtual ~Ninman();
    void loadBitmaps(int color);
    void setNextMove (int x);
    int getNextMove ();
    BITMAP* direita1;
    BITMAP* direita2;
    BITMAP* direita3;
    BITMAP* direita4;
    BITMAP* direita5;
    BITMAP* direita6;
    BITMAP* esquerda1;
    BITMAP* esquerda2;
    BITMAP* esquerda3;
    BITMAP* esquerda4;
    BITMAP* esquerda5;
    BITMAP* esquerda6;
    BITMAP* cima1;
    BITMAP* cima2;
    BITMAP* cima3;
    BITMAP* cima4;
    BITMAP* cima5;
    BITMAP* cima6;
    BITMAP* baixo1;
    BITMAP* baixo2;
    BITMAP* baixo3;
    BITMAP* baixo4;
    BITMAP* baixo5;
    BITMAP* baixo6;


private:
    void LerMovimento();
    int NextMove;
    void run();
};

#endif	/* NINMAN_H */

