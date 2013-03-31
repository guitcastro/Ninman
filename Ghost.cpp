/*
 * File:   Ghost.cpp
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 23:46
 */

#include "Ghost.h"
#define TRANSPARENTE makecol (255 ,0 ,255)

Ghost::Ghost() {

}

Ghost::Ghost(NinManMap * map) {
    this->map = map;
}

Ghost::Ghost(const Ghost& orig) {
}

Ghost::~Ghost() {
}

void Ghost::setEyesBitmap() {
    this->Bit_ghost = load_bitmap("Imagens/eyes.bmp", NULL);
}

void Ghost::setWhiteBitmap() {
    BITMAP * fanstasmas = load_bitmap("Imagens/Fantasmas.bmp", NULL);
    this->Bit_ghost = create_bitmap(24, 23);
    blit(fanstasmas, Bit_ghost, 48, 23, 0, 0, 24, 23);
}

void Ghost::setBitmap(int x, int y) {
    BITMAP * fanstasmas = load_bitmap("Imagens/Fantasmas.bmp", NULL);
    Bit_ghost = create_bitmap(26, 26);
    clear_to_color(Bit_ghost, TRANSPARENTE);
    blit(fanstasmas, Bit_ghost, x, y, 1, 1, 24, 23);
}

bool Ghost::alreadyInList(Point p) {
    std::list<Point>::iterator it = ghost_path.begin();
    it++;
    while (it != ghost_path.end()){
        if ((*it).x== p.x && (*it).y == p.y){
            return true;
        }
        it++;
    }
    return false;
}

int Ghost::ManhattanDist(Point a,Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void Ghost::move(Point ninman){
    if (ghost_path.empty()){
        this->calcPath(ninman);
    }
    Point p = ghost_path.front();
    this->x = p.x;
    this->y = p.y;
    ghost_path.pop_front();
}

void Ghost::calcPath(Point ninman) {
    int dist, shortest = -1;
    int x = this->x;
    int y = this->y;
    Point bestMove;
    while (shortest != 0 && shortest != INT_MAX) {
        shortest = INT_MAX;
        if (map->isValidCoordinate(x,y+1)) {
            bestMove.x = x;
            bestMove.y = y + 1;
            if (!this->alreadyInList(Point(x, y + 1))){
                shortest = ManhattanDist(Point(x, y + 1),ninman);
            }
        }
        if (map->isValidCoordinate(x+1,y)) {
            dist = ManhattanDist(Point(x + 1, y),ninman);
            if (dist < shortest && !this->alreadyInList(Point(x + 1, y))) {
                bestMove.x = x + 1;
                bestMove.y = y;
                shortest = dist;
            }
        }
        if (map->isValidCoordinate(x,y-1)) {
            dist = ManhattanDist(Point(x, y - 1),ninman);
            if (dist < shortest && !this->alreadyInList(Point(x, y-1))) {
                bestMove.x = x;
                bestMove.y = y - 1;
                shortest = dist;
            }
        }
        if (map->isValidCoordinate(x-1,y)) {
            dist = ManhattanDist(Point(x - 1, y),ninman);
            if (dist < shortest && !this->alreadyInList(Point(x -1, y))) {
                bestMove.x = x - 1;
                bestMove.y = y;
                shortest = dist;
            }
        }
        ghost_path.push_back(bestMove);
        x = bestMove.x;
        y = bestMove.y;
        printf("%d %d %d\n",x,y,dist);
    }
}
