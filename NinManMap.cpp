/*
 * File:   NinManMap.cpp
 * Author: guilherme
 *
 * Created on 30 de Março de 2013, 11:43
 */

#include "NinManMap.h"

NinManMap::NinManMap(const char* file_name) {
    std::ifstream file;
    file.open(file_name);
    std::stack <std::string>aux;
    char* linha = new char [1024];
    while (file) {
        file.getline(linha, 1024);
        aux.push(linha);
    }
    file.close();
    aux.pop();
    this->numberOfLines = aux.size();
    this->matrix = new std::string [numberOfLines];
    for (int i = numberOfLines - 1; i >= 0; i--) {
        matrix[i] = aux.top();
        for (int j=0;j<matrix[i].size();j++){
            if (matrix[i][j] == '2'){
                this->numberOfDots++;
            }
            if (matrix[i][j] == 'p'){
                this->ninmanInitialPosition = Point (j,i);
                matrix[i][j] = '0';
            }
            if (matrix[i][j] == 'g') {
                this->orangeGhostInitialPosition = Point (j,i);
                matrix[i][j] = '0';
            }
            if (matrix[i][j] == 'h') {
                this->blueGhostInitialPosition = Point (j,i);
                matrix[i][j] = '0';
            }
            if (matrix[i][j] == 'j') {
                this->pinkGhostInitialPosition = Point (j,i);
                matrix[i][j] = '0';
            }
            if (matrix[i][j] == 'k') {
                this->redGhostInitialPosition = Point (j,i);
                matrix[i][j] = '0';
            }
            if (matrix[i][j] == 'l') {
                this->greenGhostInitialPosition = Point (j,i);
                matrix[i][j] = '0';
            }
        }
        aux.pop();
    }
    //colunas = matrix[0].size();
    delete linha;
}

NinManMap::NinManMap(const NinManMap& orig) {
}

NinManMap::~NinManMap() {
    delete [] matrix;
}

bool NinManMap::isValidCoordinate(int x,int y){
   if (y >= this->getNumberOfLines() || y < 0){
       return false;
   }
   if (x >= this->getNumberOfColumns() || x < 0){
       return false;
   }
   return this->getPointValue(x,y) != '1'; // return true if is a not wall block
}

bool NinManMap::replacePointValue(char oldValue,char newValue){
    int nColumns = this->getNumberOfColumns();
    for (int i=0;i <this->getNumberOfLines();i++){
        for (int j=0;j<nColumns;j++){
            if (this->matrix[i][j] == oldValue){
                this->matrix[i][j] = newValue;
                return true; //value changed
            }
        }
    }
    return false; //value not changed
}

void NinManMap::showFruit(){
    int nColumns = this->getNumberOfColumns();
    int x = rand() % nColumns,y = this->getNumberOfLines();
    while (this->getPointValue(x,y) != '0') {
        x = rand() % this->getNumberOfLines();
        y = rand() % nColumns;
    }
    matrix[y][x] = 'x';
}

void  NinManMap::setPointValue(int x,int y,char value){
    this->matrix[y][x] = value;
}

// getters

char NinManMap::getPointValue(int x, int y){
    // matrix coordenates are reverso from cardinal
    return this->matrix[y][x];
}

Point NinManMap::getNinmanInitialPosition(){
    return this->ninmanInitialPosition;
}

Point NinManMap::getOrangeGhostInitialPosition(){
    return this->orangeGhostInitialPosition;
}

Point NinManMap::getBlueGhostInitialPosition(){
    return this->blueGhostInitialPosition;
}

Point NinManMap::getPinkGhostInitialPosition(){
    return this->pinkGhostInitialPosition;
}

Point NinManMap::getRedGhostInitialPosition(){
    return this->redGhostInitialPosition;
}

Point NinManMap::getGreenGhostInitialPosition(){
    return this->greenGhostInitialPosition;
}

size_t NinManMap::getNumberOfLines(){
    return this->numberOfLines;
}
size_t NinManMap::getNumberOfColumns(){
    return this->matrix[0].size();
}

size_t NinManMap::getNumberOfDots(){
    return this->numberOfDots;
}