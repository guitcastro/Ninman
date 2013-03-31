/*
 * File:   Ghost.cpp
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 23:46
 */

#include "header/Ghost.h"
#define TRANSPARENTE makecol (255 ,0 ,255)

Ghost::Ghost() {
}

Ghost::Ghost(const Ghost& orig) {
}

Ghost::~Ghost() {
}

void Ghost::setEyesBitmap() {
    this->Bit_ghost = load_bitmap("Imagens/eyes.bmp", NULL);
}

void Ghost::setWhiteBitmap() {
    BITMAP * fanstasmas = load_bitmap("Imagens/Fantasmas.bmp", NULL);
    this->Bit_ghost = create_bitmap(24, 23);
    blit(fanstasmas, Bit_ghost, 48, 23, 0, 0, 24, 23);
}

void Ghost::setBitmap(int x, int y) {
    BITMAP * fanstasmas = load_bitmap("Imagens/Fantasmas.bmp", NULL);
    Bit_ghost = create_bitmap(26, 26);
    clear_to_color(Bit_ghost, TRANSPARENTE);
    blit(fanstasmas, Bit_ghost, x, y, 1, 1, 24, 23);
}

