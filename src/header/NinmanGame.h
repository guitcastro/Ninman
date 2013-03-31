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
#include "NinManMap.h"

#include <vector>
#include <stack>
#include <math.h>
#include <time.h>
#include <pthread.h>
#define subiu 1
#define desceu -1
#define direita 2
#define esquerda -2


class NinmanGame :  public Thread {
public:

    NinmanGame(const char * player_name);

private:

    const char * player_name;
    Sound sound;
    int venceu, lifes, powertime, direction, points, nextDirection, tfruit;
    Ghost orangeGhost, blueGhost, redGhost, purpleGhost, greenGhost;
    Ninman ninman;
    bool power, reset, fruit;
    std::vector <Point> ghost_path;
    clock_t endwait;

    void run();
    void DeleteFruit();
    void init();
    void NewFruit();
    std::vector<Point> calcPath();
    void DestroyerPlayer();
    bool Venceu();
    Point RandomMove(Point Ghost);
    void EatGhost(int x);
    void LoadPlayer();
    bool CheckWinner();
    void setGhostsPositions();
    void setNinmanPosition();
    bool alreadyInList(std::vector<Point>,Point);
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

