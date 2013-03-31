/*
 * File:   NinManMap.cpp
 * Author: guilherme
 *
 * Created on 12 de Março de 2012, 21:03
 */

#include "header/NinManMap.h"

std::string * NinManMap::matrix;
unsigned int NinManMap::numberOfLines;
unsigned int NinManMap::numberOfColumns;

NinManMap::NinManMap() {
}

NinManMap::NinManMap(const NinManMap& orig) {
}

NinManMap::~NinManMap() {
}

Point * NinManMap::findPoint(char searchFor) {
    for (int a = 0; a < this->getColumnsSize(); a++)
        for (int b = 0; b < this->getLinesSize(); b++)
            if (matrix[a][b] == searchFor)
                return new Point(a, b);
}

void NinManMap::setPoint(Point point, char value) {
    this->matrix[point.x][point.y] = value;
}

void NinManMap::newFruit() {
    int x = rand() % getColumnsSize(), y = rand() % getLinesSize();
    while (matrix[x][y] != '0') {
        x = rand() % getColumnsSize();
        y = rand() % getLinesSize();
    }
    matrix[x][y] = 'x';
}

unsigned int NinManMap::getColumnsSize() {
    return NinManMap::numberOfColumns;
}

unsigned int NinManMap::getLinesSize() {
    return NinManMap::numberOfLines;
}

/**
 * load the map from a text file
 */
void NinManMap::loadLab(const char* file_name) {
    std::ifstream file(file_name, std::ifstream::in);
    std::stack <std::string>aux;
    char* line = new char [1024];
    while (file) {
        file.getline(line, 1024);
        aux.push(line);
    }
    aux.pop();
    NinManMap::numberOfLines = aux.size();
    NinManMap::matrix = new std::string [NinManMap::numberOfLines];
    for (int i = NinManMap::numberOfLines - 1; i >= 0; i--) {
        NinManMap::matrix[i] = aux.top();
        aux.pop();
    }
    NinManMap::numberOfColumns = NinManMap::matrix[0].size();
    file.close();
    delete line;
}