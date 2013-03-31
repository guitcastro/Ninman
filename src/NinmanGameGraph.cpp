/*
 * File:   NinmanGameGraph.cpp
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 21:15
 */

#include "NinmanGameGraph.h"

NinmanGameGraph::NinmanGameGraph() {
}

NinmanGameGraph::NinmanGameGraph(const NinmanGameGraph& orig) {
}

NinmanGameGraph::~NinmanGameGraph() {
}

int NinmanGameGraph::DrawGameOptions() {

    int y = 220;
    DrawOptions(y);
    while (true) {
        clear_keybuf();
        readkey();
        if (key[KEY_DOWN]) {
            y = y + 55;
            {
                if (y > 330)
                    y = 220;
            }
        }
        if (key[KEY_UP]) {
            y = y - 55;
            {
                if (y < 220)
                    y = 330;
            }
        }
        if (key[KEY_ENTER]) {
            return y;
        }
        DrawOptions(y);
    }
}

void NinmanGameGraph::DrawOptions(int y) {
    clear(screen);
    BITMAP * pacman;
    BITMAP * menu;
    menu = load_bitmap("Imagens/GameMenu.bmp", NULL);
    pacman = load_bitmap("Imagens/pacman.bmp", NULL);
    draw_sprite(screen, menu, 400 - 163, 350 - 153);
    draw_sprite(screen, pacman, 215, y);
    destroy_bitmap(menu);
    destroy_bitmap(pacman);
}
