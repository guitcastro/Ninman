/*
 * File:   Score.cpp
 * Author: guilherme
 *
 * Created on April 27, 2011, 9:34 PM
 */

#include "header/Score.h"

//constructors and destructors

Score::Score() {
    memset (this->playerName,0,32);
    this->playerPoints = 0;
}

Score::Score(const char * name, int points) {
    memset (this->playerName,0,32);
    memcpy(this->playerName,name,strlen(name)+1);
    this->playerPoints = points;
}

Score::Score(const Score& orig){
    memcpy(this->playerName,orig.playerName,strlen(orig.playerName)+1);
    this->playerPoints = orig.playerPoints;
}

Score::~Score(){
    delete this->playerName;
}

//setters

void Score::setPlayerPoints (int playerPoints){
    this->playerPoints = playerPoints;
}

void Score::setPlayerName(const char * playerName){
    strcpy (this->playerName,playerName);
}

//getters

int Score::getPlayerPoints (){
    return this->playerPoints;
}

const char *  Score::getPlayerName (){
    return this->playerName;
}

const char * Score::getScoreToString() {
    std::string separator = " - ";
    std::string s = this->playerName;
    s+= separator;
    s+= this->playerPoints;
    return s.c_str();
}
/*
char * Score::getScoreToString() {
    char * retorno = this->playerName;
    retorno += playerPoints;
    return retorno;
}*/
