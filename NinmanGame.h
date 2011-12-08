/*
 * File:   NinmanGame.h
 * Author: guilherme
 *
 * Created on April 27, 2011, 11:07 AM
 */


#ifndef NINMANGAME_H
#define	NINMANGAME_H

#include "NinmanConfig.h"
#include "NinmanGameGraph.h"
#include "Ninman.h"
#include "Ghost.h"
#include "Thread.h"
#include "Sound.h"
#include <list>
#include <stack>
#include <math.h>
#include <time.h>
#include <pthread.h>
#define subiu 1
#define desceu -1
#define direita 2
#define esquerda -2
#define WHITE makecol(0, 0, 0)
#define TRANSPARENTE makecol (255 ,0 ,255)

class NinmanGame : public Thread {
public:

    NinmanGame(const char * player_name);

private:
    std::string* matriz;
    const char * player_name;
    Sound sound;
    int venceu, vida, powertime, linhas, colunas, sentido, pontos, sentido2, tfruit;
    Ghost ghost, ghost1, ghost2, ghost3, ghost4;
    Ninman ninman;
    bool power, reset, fruit;
    std::list <Point> ghost_path; //, pilha1, pilha2, pilha3;;
    clock_t endwait;

    void run();
    void DeleteFruit();
    void init();
    void LoadMatriz();
    void NewFruit();
    std::list<Point> calcPath();
    void DestroyerPlayer();
    bool Venceu();
    Point RandomMove(Point Ghost);
    void EatGhost(int x);
    void LoadPlayer();
    bool CheckWinner();
    void setGhostsPositions();
    void setNinmanPosition();
    bool alreadyInList(std::list<Point>);
    int move(int NextMove);
    void PowerOn();
    void MoverFantasma5();
    void LoadLab(const char* file_name);
    void DrawLab();
    double ManhattanDist(Point a, Point b);
    int getCoordinateType(int x, int y);
};

char* itoa(int value, char* result, int base);

#endif	/* NINMANGAME_H */

