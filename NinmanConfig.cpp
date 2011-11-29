
#include "NinmanConfig.h"
#include <iostream>
#include <list>

NinmanConfig::NinmanConfig() {
    std::ifstream configure("config.dat", std::ios::binary);
    if (configure.is_open()) {
        configure.read((char*) this, sizeof (*this));
    } else {
        DefaultConfig();
    }
    configure.close();

}

void NinmanConfig::RefreshScore(int playerPoints, const char * playerName) {
    //precisa ser implementado
    SaveConfig();
}

void NinmanConfig::setDefaultScore() {
    this->scores[0] = (Score("Nin", 1000));
    this->scores[1] = (Score("Voix", 900));
    this->scores[2] = (Score("Max", 800));
    this->scores[3] = (Score("Jhony", 700));
    this->scores[4] = (Score("Jack", 600));
    this->scores[5] = (Score("Dagao", 500));
    this->scores[6] = (Score("Tux", 400));
    this->scores[7] = (Score("James", 300));
    this->scores[8] = (Score("Jessie", 200));
    this->scores[9] = (Score("Janie", 100));
}

void NinmanConfig::DefaultConfig() {
    std::ofstream configure;
    configure.open("config.dat", std::ios::binary);
    this->setDefaultScore();
    this->fullscreen = false;
    this->Ninman_color = 0;
    this->Volume = 250;
    this->labs = 0;
    configure.write((char*) this, sizeof (*this));
    configure.close();
}

bool NinmanConfig::GetFullScreenOption() {
    return this->fullscreen;
}

void NinmanConfig::SaveConfig() {
    std::ofstream configure;
    configure.open("config.dat", std::ios::binary);
    configure.write((char*) this, sizeof (*this));
    configure.close();
}

void NinmanConfig::SetFullScreenOption(bool value) {
    this->fullscreen = value;
    SaveConfig();
}

int NinmanConfig::GetVolume() {
    return this->Volume;
}

void NinmanConfig::SetLab(int x) {
    this->labs = this->labs + x;
    if (this->labs > 3)
        this->labs = 0;
    if (this->labs < 0)
        this->labs = 3;
    SaveConfig();

}

const char* NinmanConfig::GetLab() {
    switch (this->labs) {
        case 0:return "Classic";
        case 1:return "Small";
        case 2:return "Medium";
        case 3:return "Larger";
    }
    return "Classic";
}

void NinmanConfig::SetVolume(int value) {
    if (value <= 250 && value >= 0) {
        this->Volume = value;
        SaveConfig();
    }
}

const char* NinmanConfig::GetScore(int x) {
    return this->scores[x].getScoreToString();
}

void NinmanConfig::SetNimanColor(int x) {
    if (x < 0)
        x = 75;
    if (x > 75)
        x = 0;
    this->Ninman_color = x;
    SaveConfig();
}

int NinmanConfig::GetNimanColor() {
    return this->Ninman_color;
}

char* NinmanConfig::itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
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


