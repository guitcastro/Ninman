#include "header/NinmanConfig.h"

/*
 * Hold the game data configuration
 */
NinmanConfig::config NinmanConfig::conf;

/*
 * Save the game configuration to a binary file
 */
void NinmanConfig::SaveConfig() {
    std::ofstream configure;
    configure.open("config.dat", std::ios::binary);
    configure.write((char*) &conf, sizeof (conf));
    configure.close();
}

/*
 * Set a default game score
 */
void NinmanConfig::defaultScore() {
    conf.scores[0] = (Score("Nin", 1000));
    conf.scores[1] = (Score("Voix", 900));
    conf.scores[2] = (Score("Max", 800));
    conf.scores[3] = (Score("Jhony", 700));
    conf.scores[4] = (Score("Jack", 600));
    conf.scores[5] = (Score("Dagao", 500));
    conf.scores[6] = (Score("Tux", 400));
    conf.scores[7] = (Score("James", 300));
    conf.scores[8] = (Score("Jessie", 200));
    conf.scores[9] = (Score("Janie", 100));
}

/*
 * Set default game configuration
 */
void NinmanConfig::DefaultConfig() {
    defaultScore();
    conf.fullscreen = false;
    conf.ninman_color = 0;
    conf.volume = 250;
    conf.lab = 0;
    SaveConfig();
}

/*
 * Try to load a previous game configuration, if failed set the game
 * to the default configuration and save it in a binary file
 */
void NinmanConfig::loadConfig() {
    std::ifstream configure("config.dat", std::ios::binary);
    if (configure.is_open()) {
        configure.read((char*) &conf, sizeof (conf));
    } else {
        DefaultConfig();
    }
    configure.close();
}

/*
 * Refresh player score
 */
void NinmanConfig::RefreshScore(int playerPoints, const char * playerName) {
    Score temp(playerName, playerPoints);
    for (int i = 0; i < 10; i++) {
        if (conf.scores[i].getPlayerPoints() < playerPoints) {
            Score temp2 = conf.scores[i];
            conf.scores[i].setPlayerName(temp.getPlayerName());
            conf.scores[i].setPlayerPoints(temp.getPlayerPoints());
            temp = temp2;
        }
    }
    SaveConfig();
}

//getters

bool NinmanConfig::getFullScreenOption() {
    return conf.fullscreen;
}

const char* NinmanConfig::getLab() {
    switch (conf.lab) {

        case 0:return "Labirintos/Classic.txt";
        case 1:return "Labirintos/Small.txt";
        case 2:return "Labirintos/Medium.txt";
        case 3:return "Labirintos/Larger.txt";
    }
    return "Classic";
}

int NinmanConfig::getNimanColor() {
    return conf.ninman_color;
}

const char* NinmanConfig::getScore(int index) {
    return conf.scores[index].getScoreToString();
}

int NinmanConfig::getVolume() {
    return conf.volume;
}

//setters

void NinmanConfig::setFullScreenOption(bool value) {

    conf.fullscreen = value;
    SaveConfig();
}

void NinmanConfig::setLab(int x) {
    conf.lab = conf.lab + x;
    if (conf.lab > 3)
        conf.lab = 0;
    if (conf.lab < 0)
        conf.lab = 3;
    SaveConfig();
}

void NinmanConfig::setNimanColor(int value) {
    conf.ninman_color += value;
    if (conf.ninman_color < 0)
        conf.ninman_color = 75;
    if (conf.ninman_color > 75)
        conf.ninman_color = 0;
    SaveConfig();
}

void NinmanConfig::setVolume(int value) {
    if (value <= 250 && value >= 0) {
        conf.volume = value;
        SaveConfig();
    }
}