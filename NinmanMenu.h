/*
 * File:   NinmanMenu.h
 * Author: guilherme
 *
 * Created on April 27, 2011, 10:18 AM
 */

#ifndef NINMANMENU_H
#define	NINMANMENU_H

#include "NinmanGame.h"

class NinmanMenu {
public:
    NinmanMenu();

private:
    void Score();
    void DrawStartGame(int y, std::string nome);
    std::string TextBox();
    void DrawLoadGame(int y);
    int LoadGame();
    bool CreatPlayer(const char * nome);
    int MainMenu();
    void About();
    void OptionMenu();
    const char* GetVolumeString();
    void DrawOptionMenu(int y);
    void DrawMenu(int y);

};

#endif	/* NINMANMENU_H */

