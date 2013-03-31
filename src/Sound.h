/*
 * File:   Sound.h
 * Author: guilherme
 *
 * Created on 29 de Novembro de 2011, 01:49
 */

#ifndef SOUND_H
#define	SOUND_H

#include "allegro.h"

class Sound {
public:
    Sound();
    Sound(const Sound& orig);
    void play (const char * sound,bool repeat = false);
    void stop (const char * sound);
    virtual ~Sound();
private:
    SAMPLE * siren;
    SAMPLE * opening;
    SAMPLE * eat;
    SAMPLE * selectSound (const char * sound);

};

#endif	/* SOUND_H */

