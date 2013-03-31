/*
 * File:   Ninman.cpp
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 23:12
 */

#include "header/Ninman.h"

Ninman::Ninman() {
}

Ninman::Ninman(const Ninman& orig) {
}

Ninman::~Ninman() {
}

void Ninman::loadBitmaps(int color) {
    BITMAP * sprite = load_bitmap("Imagens/Ninman.bmp", NULL);
    int y = -25;
    direita1 = create_bitmap(26, 26);
    clear_to_color(direita1, TRANSPARENTE);
    blit(sprite, direita1, color, y = y + 25, 3, 3, 21, 21);
    direita2 = create_bitmap(26, 26);
    clear_to_color(direita2, TRANSPARENTE);
    blit(sprite, direita2, color, y = y + 25, 3, 3, 21, 21);
    direita3 = create_bitmap(26, 26);
    clear_to_color(direita3, TRANSPARENTE);
    blit(sprite, direita3, color, y = y + 25, 3, 3, 21, 21);
    direita4 = create_bitmap(26, 26);
    clear_to_color(direita4, TRANSPARENTE);
    blit(sprite, direita4, color, y = y + 25, 3, 3, 21, 21);
    direita5 = create_bitmap(26, 26);
    clear_to_color(direita5, TRANSPARENTE);
    blit(sprite, direita5, color, y = y + 25, 3, 3, 21, 21);
    direita6 = create_bitmap(26, 26);
    clear_to_color(direita6, TRANSPARENTE);
    blit(sprite, direita6, color, y = y + 25, 3, 3, 21, 21);

    baixo1 = create_bitmap(26, 26);
    clear_to_color(baixo1, TRANSPARENTE);
    blit(sprite, baixo1, color, y = y + 25, 3, 3, 21, 21);
    baixo2 = create_bitmap(26, 26);
    clear_to_color(baixo2, TRANSPARENTE);
    blit(sprite, baixo2, color, y = y + 25, 3, 3, 21, 21);
    baixo3 = create_bitmap(26, 26);
    clear_to_color(baixo3, TRANSPARENTE);
    blit(sprite, baixo3, color, y = y + 25, 3, 3, 21, 21);
    baixo4 = create_bitmap(26, 26);
    clear_to_color(baixo4, TRANSPARENTE);
    blit(sprite, baixo4, color, y = y + 25, 3, 3, 21, 21);
    baixo5 = create_bitmap(26, 26);
    clear_to_color(baixo5, TRANSPARENTE);
    blit(sprite, baixo5, color, y = y + 25, 3, 3, 21, 21);
    baixo6 = create_bitmap(26, 26);
    clear_to_color(baixo6, TRANSPARENTE);
    blit(sprite, baixo6, color, y = y + 25, 3, 3, 21, 21);

    esquerda1 = create_bitmap(26, 26);
    clear_to_color(esquerda1, TRANSPARENTE);
    blit(sprite, esquerda1, color, y = y + 25, 3, 3, 21, 21);
    esquerda2 = create_bitmap(26, 26);
    clear_to_color(esquerda2, TRANSPARENTE);
    blit(sprite, esquerda2, color, y = y + 25, 3, 3, 21, 21);
    esquerda3 = create_bitmap(26, 26);
    clear_to_color(esquerda3, TRANSPARENTE);
    blit(sprite, esquerda3, color, y = y + 25, 3, 3, 21, 21);
    esquerda4 = create_bitmap(26, 26);
    clear_to_color(esquerda4, TRANSPARENTE);
    blit(sprite, esquerda4, color, y = y + 25, 3, 3, 21, 21);
    esquerda5 = create_bitmap(26, 26);
    clear_to_color(esquerda5, TRANSPARENTE);
    blit(sprite, esquerda5, color, y = y + 25, 3, 3, 21, 21);
    esquerda6 = create_bitmap(26, 26);
    clear_to_color(esquerda6, TRANSPARENTE);
    blit(sprite, esquerda6, color, y = y + 25, 3, 3, 21, 21);

    cima1 = create_bitmap(26, 26);
    clear_to_color(cima1, TRANSPARENTE);
    blit(sprite, cima1, color, y = y + 25, 3, 3, 21, 21);
    cima2 = create_bitmap(26, 26);
    clear_to_color(cima2, TRANSPARENTE);
    blit(sprite, cima2, color, y = y + 25, 3, 3, 21, 21);
    cima3 = create_bitmap(26, 26);
    clear_to_color(cima3, TRANSPARENTE);
    blit(sprite, cima3, color, y = y + 25, 3, 3, 21, 21);
    cima4 = create_bitmap(26, 26);
    clear_to_color(cima4, TRANSPARENTE);
    blit(sprite, cima4, color, y = y + 25, 3, 3, 21, 21);
    cima5 = create_bitmap(26, 26);
    clear_to_color(cima5, TRANSPARENTE);
    blit(sprite, cima5, color, y = y + 25, 3, 3, 21, 21);
    cima6 = create_bitmap(26, 26);
    clear_to_color(cima6, TRANSPARENTE);
    blit(sprite, cima6, color, y = y + 25, 3, 3, 21, 21);

    destroy_bitmap(sprite);
}

void Ninman::run() {
    LerMovimento();
}

void Ninman::LerMovimento() {
    while (true) {
        if (key[KEY_DOWN])
            this->NextMove = desceu;
        if (key[KEY_UP])
            this->NextMove = subiu;
        if (key[KEY_LEFT])
            this->NextMove = esquerda;
        if (key[KEY_RIGHT])
            this->NextMove = direita;
    }
}

void Ninman::setNextMove(int x) {
    this->NextMove = x;
}

int Ninman::getNextMove() {
    return this->NextMove;
}

void Ninman::setNinmanPosition (Point position){
    this->x = position.x;
    this->y = position.y;
}