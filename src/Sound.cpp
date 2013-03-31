/*
 * File:   Sound.cpp
 * Author: guilherme
 *
 * Created on 29 de Novembro de 2011, 01:49
 */

#include "header/Sound.h"

Sound::Sound() {
    this->siren = load_sample("Sound/siren.wav");
    this->opening = load_sample("Sound/opening_song.wav");
    this->eat = load_sample("Sound/eating.short.wav");
}

Sound::Sound(const Sound& orig) {
}

Sound::~Sound() {
}

void Sound::play(const char* sound,bool repeat ) {
    play_sample(selectSound(sound), 255, 0, 1000, repeat);
}

void Sound::stop(const char* sound) {
    stop_sample(selectSound(sound));
}

SAMPLE * Sound::selectSound(const char* sound) {
    if (strcmp(sound, "siren") == 0)
        return siren;
    else if (strcmp(sound, "opening") == 0)
        return opening;
}

