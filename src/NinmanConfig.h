#ifndef ninman_config_h
#define	ninman_config_h

#include <fstream>
#include "Score.h"

/*
 * static class, that holds and maintence game configuration and players scores
 */
class NinmanConfig {

    /*
     * Struct used to save config in a binary file
     */
    struct config {
        bool fullscreen;
        int ninman_color;
        int volume;
        int lab;
        Score scores [10];
    };

public:

    //public methods

    static void RefreshScore(int x, const char * playerName);
    static void loadConfig();

    //setters
    static void setFullScreenOption(bool value);
    static void setLab(int x);
    static void setNimanColor(int x);
    static void setVolume(int value);

    //getters

    static bool getFullScreenOption();
    static const char* getLab();
    static const char * getScore(int index);
    static int getNimanColor();
    static int getVolume();

private:

    //private properties

    static config conf;

    //private methods
    static void DefaultConfig();
    static void SaveConfig();
    static void defaultScore();
};
#endif
