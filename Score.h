/*
 * File:   Score.h
 * Author: guilherme
 *
 * Created on April 27, 2011, 9:34 PM
 */

#ifndef SCORE_H
#define	SCORE_H

#include <string.h>
#include <string>

class Score {
public:
    Score();
    Score(const char *, int);
    const char * getScoreToString();

private:
    char  playerName [32] ;
    int playerPoints;
};

#endif	/* SCORE_H */

