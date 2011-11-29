#ifndef ninman_config_h
#define	ninman_config_h

#include <fstream>
#include <allegro.h>
#include <list>
#include "Score.h"

class NinmanConfig {
public:
    NinmanConfig();
    void RefreshScore(int x, const char * jogador);
    void DefaultConfig();
    bool GetFullScreenOption();
    void SaveConfig();
    void SetFullScreenOption(bool value);
    int GetVolume();
    void SetLab(int x);
    const char* GetLab();
    void SetVolume(int value);
    const char * GetScore(int x);
    void SetNimanColor(int x);
    int GetNimanColor();
    static char* itoa(int value, char* result, int base);
    void setDefaultScore();

private:
    Score scores [10];
    int labs;
    int Volume;
    int Ninman_color;
    bool fullscreen;

};
#endif
