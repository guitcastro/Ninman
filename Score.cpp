/*
 * File:   Score.cpp
 * Author: guilherme
 *
 * Created on April 27, 2011, 9:34 PM
 */

#include "Score.h"

char* itoa(int value) {

    char* result = new char [32];
    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= 10;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * 10)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

Score::Score() {
    memset (this->playerName,0,32);
    this->playerPoints = 0;
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

Score::Score(const char * name, int points) {
    memset (this->playerName,0,32);
    memcpy(this->playerName,name,strlen(name)+1);
    this->playerPoints = points;
}
