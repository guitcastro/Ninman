#include <iostream>

#include "header/NinmanGame.h"

/**
 * Initialize game attributes
 */

NinmanGame::NinmanGame(const char* player_name) {
    //clear screen
    clear(screen);
    //initialize game variable
    this->player_name = player_name;
    this->powertime = 0;
    this->lifes = 3;
    this->power = false;
    this->direction = esquerda;
    this->nextDirection = 0;
    this->points = 0;
    this->fruit = false;
    this->tfruit = 0;
    this->endwait = clock() + 0.01 * CLOCKS_PER_SEC;
    this->venceu = 0;
    this->sound = Sound();
    this->ninman.loadBitmaps(NinmanConfig::getNimanColor());
    this->orangeGhost.setBitmap(0, 0);
    this->blueGhost.setBitmap(24, 0);
    this->redGhost.setBitmap(48, 0);
    this->purpleGhost.setBitmap(0, 23);
    this->greenGhost.setBitmap(24, 23);
    //start game
    this->Start();
    this->Wait();
}

void NinmanGame::setNinmanPosition() {
    for (int a = 0; a < NinManMap::getLinesSize(); a++)
        for (int b = 0; b < NinManMap::getColumnsSize(); b++)
            if (NinManMap::matrix[a][b] == 'p') {
                this->ninman.x = a;
                this->ninman.y = b;
                NinManMap::matrix[a][b] = 0;
            }
}

/**
 * Init game
 */
void NinmanGame::init() {
    NinManMap::loadLab(NinmanConfig::getLab());
    this->setNinmanPosition();
    this->setGhostsPositions();
    this->DrawLab();
    NinmanGameGraph::drawInitGame();
    this->sound.play("opening");
    rest(5000);
}

double NinmanGame::ManhattanDist(Point a, Point b) {
    int x1x2, y1y2;
    x1x2 = ((a.x - b.x) > 0) ? (a.x - b.x) : (a.x - b.x) * -1;
    y1y2 = ((a.y - b.y) > 0) ? (a.y - b.y) : (a.y - b.y) * -1;
    return x1x2 + y1y2;
}

bool NinmanGame::alreadyInList(std::vector<Point> list, Point point) {
    for (int i = 0; i < list.size(); i++) {
        std::cout << "\n" << list[i].x << "-" << list[i].y;
        if (point == list[i])
            return true;
    }
    return false;
}

std::vector<Point> NinmanGame::calcPath() {
    int dist, shortest = -1;
    int x = orangeGhost.x;
    int y = orangeGhost.y;
    Point bestMove;
    std::vector <Point> ghostPath(100, Point());
    while (shortest != 0) {
        if (y < NinManMap::getColumnsSize() - 1 && NinManMap::matrix[x][y + 1] != '1') {
            if (!alreadyInList(ghostPath, Point(x, y + 1))) {
                bestMove = Point(x, y + 1);
                shortest = ManhattanDist(bestMove, this->ninman);
            }
        }
        if (x < NinManMap::getColumnsSize() - 1 && NinManMap::matrix[x + 1][y] != '1') {
            dist = ManhattanDist(Point(x + 1, y), this->ninman);
            if (dist < shortest || shortest < 0 && !alreadyInList(ghostPath, Point(x + 1, y))) {
                bestMove.x = x + 1;
                bestMove.y = y;
                shortest = dist;
            }
        }
        if (y > 0 && NinManMap::matrix[x][y - 1] != '1') {
            dist = ManhattanDist(Point(x, y - 1), this->ninman);
            if (dist < shortest || shortest < 0 && !alreadyInList(ghostPath, Point(x, y - 1))) {
                bestMove.x = x;
                bestMove.y = y - 1;
                shortest = dist;
            }
        }
        if (x > 0 && NinManMap::matrix[x - 1][y] != '1') {
            dist = ManhattanDist(Point(x - 1, y), this->ninman);
            if (dist < shortest || shortest < 0 && !alreadyInList(ghostPath, Point(x - 1, y))) {
                bestMove.x = x - 1;
                bestMove.y = y;
                shortest = dist;
            }
        }
        ghostPath.push_back(bestMove);
        x = bestMove.x;
        y = bestMove.y;
        shortest = -1;
    }
    return ghostPath;
}

bool NinmanGame::Venceu() {
    if (!power) {
        if (orangeGhost == ninman || blueGhost == ninman || redGhost == ninman
                || purpleGhost == ninman || greenGhost == ninman) {
            lifes--;
            return true;
        }
        if (lifes == 0) {
            venceu = -1;
        }
    } else {
        if (orangeGhost == ninman)
            orangeGhost.setEyesBitmap();
        if (blueGhost == ninman)
            blueGhost.setEyesBitmap();
        if (redGhost == ninman)
            redGhost.setEyesBitmap();
        if (purpleGhost == ninman)
            purpleGhost.setEyesBitmap();
        if (greenGhost == ninman)
            greenGhost.setEyesBitmap();
    }
    if (CheckWinner())
        venceu = 1;

    return false;
}

/*
Point NinmanGame::RandomMove(Point ghost) {

    int iSecret = rand() % 4;
    switch (iSecret) {
        case 0:
            iSecret = subiu;
            break;
        case 1:
            iSecret = desceu;
            break;
        case 2:
            iSecret = direita;
            break;
        case 3:
            iSecret = esquerda;
            break;
    }

    int sentido2 = iSecret;
    if (sentido2 == direita) {
        if (ghost.y + 1 < NinManMap::getColumnsSize()) {
            if (NinManMap::matrix[ghost.x][ghost.y + 1] == '1') {
                sentido2 = 0;
            }
        }
    }

    if (sentido2 == subiu) {
        if (ghost.x - 1 >= 0) {
            if (NinManMap::matrix[ghost.x - 1][ghost.y] == '1') {
                sentido2 = 0;
            }
        }
    }
    if (sentido2 == esquerda) {
        if (ghost.y - 1 >= 0) {
            if (NinManMap::matrix[ghost.x][ghost.y - 1] == '1') {
                sentido2 = 0;
            }
        }
    }
    if (sentido2 == desceu) {
        if (ghost.x < NinManMap::getLinesSize()) {
            if (NinManMap::matrix[ghost.x + 1][ghost.y] == '1') {
                sentido2 = 0;
            }
        }
    }

    if (sentido2 == 0)
        sentido2 = iSecret;

    if (sentido2 == direita) {
        if (ghost.y + 1 < NinManMap::getColumnsSize()) {
            if (NinManMap::matrix[ghost.x][ghost.y + 1] != '1') {
                NinManMap::matrix[ghost.x][ghost.y] = '0';
                ghost.y = ghost.y + 1;
                if (ghost.y == NinManMap::getColumnsSize() - 1)
                    ghost.y = 0;


            }
        }
    }

    if (sentido2 == subiu) {
        if (ghost.color - 1 >= 0) {
            if (NinManMap::matrix[ghost.color - 1][ghost.y] != '1') {
                ghost.color = ghost.color - 1;
                if (ghost.color == 0)
                    ghost.color = NinManMap::getLinesSize() - 1;

            }
        }
    }
    if (sentido2 == esquerda) {
        if (ghost.y - 1 >= 0) {
            if (NinManMap::matrix[ghost.color][ghost.y - 1] != '1') {
                ghost.y = ghost.y - 1;
                if (ghost.y == 0)
                    ghost.y = NinManMap::getColumnsSize() - 1;
            }
        }
    }
    if (sentido2 == desceu) {
        if (ghost.color < NinManMap::getLinesSize()) {
            if (NinManMap::matrix[ghost.color + 1][ghost.y] != '1') {
                ghost.color = ghost.color + 1;

                if (ghost.color == NinManMap::getLinesSize() - 1)
                    ghost.color = 0;
            }
        }
    }
    return ghost;
}
 */

bool NinmanGame::CheckWinner() {
    bool venceu = true;
    for (int a = 0; a < NinManMap::getLinesSize(); a++) {
        for (int b = 0; b < NinManMap::getColumnsSize(); b++) {
            if (NinManMap::matrix[a][b] == '2') {
                return false;
            }
        }
    }
    return venceu;
}

void NinmanGame::setGhostsPositions() {
    for (int a = 0; a < NinManMap::getLinesSize(); a++) {
        for (int b = 0; b < NinManMap::getColumnsSize(); b++) {
            if (NinManMap::matrix[a][b] == 'g') {
                orangeGhost.x = a;
                orangeGhost.y = b;
                NinManMap::matrix[a][b] = 0;
            }
            if (NinManMap::matrix[a][b] == 'h') {
                blueGhost.x = a;
                blueGhost.y = b;
                NinManMap::matrix[a][b] = 0;
            }
            if (NinManMap::matrix[a][b] == 'j') {
                redGhost.x = a;
                redGhost.y = b;
                NinManMap::matrix[a][b] = 0;
            }
            if (NinManMap::matrix[a][b] == 'k') {
                purpleGhost.x = a;
                purpleGhost.y = b;
                NinManMap::matrix[a][b] = 0;
            }
            if (NinManMap::matrix[a][b] == 'l') {

                greenGhost.x = a;
                greenGhost.y = b;
                NinManMap::matrix[a][b] = 0;
            }
        }
    }
}

int NinmanGame::getCoordinateType(int x, int y) {
    //invalid coordinate
    if (y >= NinManMap::getColumnsSize() || x >= NinManMap::getLinesSize() || x < 0 || y < 0 || NinManMap::matrix[x][y] == '1')
        return -1;
    if (NinManMap::matrix[ninman.x][ninman.y] == '0')
        return 0;
    if (NinManMap::matrix[ninman.x][ninman.y] == 'x')
        return 1;
    if (NinManMap::matrix[ninman.x][ninman.y] == '2')
        return 2;
    if (NinManMap::matrix[ninman.x][ninman.y] == '3')

        return 3;
}

int NinmanGame::move(int NextMove) {
    if (NextMove != 0) {
        int tempSentido = direction;
        if (NextMove == direita && getCoordinateType(ninman.x, ninman.y + 1) >= 0)
            direction = direita;
        else if (NextMove == subiu && getCoordinateType(ninman.x - 1, ninman.y) >= 0)
            direction = subiu;
        else if (NextMove == esquerda && getCoordinateType(ninman.x, ninman.y - 1) >= 0)
            direction = esquerda;
        else if (NextMove == desceu && getCoordinateType(ninman.x + 1, ninman.y) >= 0)
            direction = desceu;
        //sentido has changed, pre-move worked
        if (tempSentido != direction)
            NextMove = 0;
    }
    if (direction == direita && getCoordinateType(ninman.x, ninman.y + 1) >= 0)
        ninman.y += 1;
    else if (direction == subiu && getCoordinateType(ninman.x - 1, ninman.y) >= 0)
        ninman.x -= 1;
    else if (direction == esquerda && getCoordinateType(ninman.x, ninman.y - 1) >= 0)
        ninman.y -= 1;
    else if (direction == desceu && getCoordinateType(ninman.x + 1, ninman.y) >= 0)
        ninman.x += 1;

    if (ninman.y == NinManMap::getColumnsSize() - 1)
        ninman.y = 0;
    else if (ninman.x == 0)
        ninman.x = NinManMap::getLinesSize() - 1;
    else if (ninman.y == 0)
        ninman.y = NinManMap::getColumnsSize() - 1;
    else if (ninman.x == NinManMap::getLinesSize() - 1)
        ninman.x = 0;

    switch (getCoordinateType(ninman.x, ninman.y)) {
        case 0:
            break;
        case 1:
            this->nextDirection += 150;
            break;
        case 2:
        {
            this->nextDirection += 10;
            //this->sound.play("eat");
        }
            break;
        case 3:
            this->power = true;
            break;
        default:
            break;
    }
    NinManMap::matrix[ninman.x][ninman.y] = 'p';

    return NextMove;
}

/*
void NinmanGame::MoverFantasma5() {
    int iSecret = rand() % 4;
    switch (iSecret) {
        case 0:
            iSecret = subiu;
            break;
        case 1:
            iSecret = desceu;
            break;
        case 2:
            iSecret = direita;
            break;
        case 3:
            iSecret = esquerda;
            break;
    }
    if (sentido2 == 0)
        sentido2 = iSecret;
    if (sentido2 == direita) {
        if (ghost4.y + 1 < NinManMap::getColumnsSize()) {
            if (NinManMap::matrix[ghost4.color][ghost4.y + 1] == '1') {
                sentido2 = 0;
            }
        }
    }

    if (sentido2 == subiu) {
        if (ghost4.color - 1 >= 0) {
            if (NinManMap::matrix[ghost4.color - 1][ghost4.y] == '1') {
                sentido2 = 0;
            }
        }
    }
    if (sentido2 == esquerda) {
        if (ghost4.y - 1 >= 0) {
            if (NinManMap::matrix[ghost4.color][ghost4.y - 1] == '1') {
                sentido2 = 0;
            }
        }
    }
    if (sentido2 == desceu) {
        if (ghost4.color < NinManMap::getLinesSize()) {
            if (NinManMap::matrix[ghost4.color + 1][ghost4.y] == '1') {
                sentido2 = 0;
            }
        }
    }

    if (sentido2 == 0)
        sentido2 = iSecret;

    if (sentido2 == direita) {
        if (ghost4.y + 1 < NinManMap::getColumnsSize()) {
            if (NinManMap::matrix[ghost4.color][ghost4.y + 1] != '1') {
                NinManMap::matrix[ghost4.color][ghost4.y] = '0';
                ghost4.y = ghost4.y + 1;
                if (ghost4.y == NinManMap::getColumnsSize() - 1)
                    ghost4.y = 0;


            }
        }
    }

    if (sentido2 == subiu) {
        if (ghost4.color - 1 >= 0) {
            if (NinManMap::matrix[ghost4.x - 1][ghost4.y] != '1') {
                ghost4.x = ghost4.x - 1;
                if (ghost4.x == 0)
                    ghost4.x = NinManMap::getLinesSize() - 1;

            }
        }
    }
    if (sentido2 == esquerda) {
        if (ghost4.y - 1 >= 0) {
            if (NinManMap::matrix[ghost4.x][ghost4.y - 1] != '1') {
                ghost4.y = ghost4.y - 1;
                if (ghost4.y == 0)
                    ghost4.y = NinManMap::getColumnsSize() - 1;
            }
        }
    }
    if (sentido2 == desceu) {
        if (ghost4.x < NinManMap::getLinesSize()) {
            if (NinManMap::matrix[ghost4.x + 1][ghost4.y] != '1') {
                ghost4.x = ghost4.x + 1;

                if (ghost4.x == NinManMap::getLinesSize() - 1)
                    ghost4.x = 0;
            }
        }
    }
}
 */


void NinmanGame::DrawLab() {
    BITMAP *mapa = create_bitmap(NinManMap::getColumnsSize() * 26, NinManMap::getLinesSize() * 26 + 20);
    BITMAP * bloco = load_bitmap("Imagens/bloco.bmp", NULL);
    BITMAP * bola2 = load_bitmap("Imagens/bola2.bmp", NULL);
    BITMAP * bola = load_bitmap("Imagens/bola.bmp", NULL);
    BITMAP * fruit = load_bitmap("Imagens/fruit.bmp", NULL);
    clear(mapa);
    for (int a = 0; a < NinManMap::getColumnsSize(); a++) {
        for (int b = 0; b < NinManMap::getLinesSize(); b++) {
            if (NinManMap::matrix[b][a] == '1')
                draw_sprite(mapa, bloco, a * 26, b * 26);
            if (NinManMap::matrix[b][a] == '2')
                draw_sprite(mapa, bola2, a * 26, b * 26);
            if (NinManMap::matrix[b][a] == '3')
                draw_sprite(mapa, bola, a * 26, b * 26);
            if (NinManMap::matrix[b][a] == 'x')
                draw_sprite(mapa, fruit, a * 26, b * 26);
            if (b == orangeGhost.x && a == orangeGhost.y)
                draw_sprite(mapa, orangeGhost.Bit_ghost, a * 26, b * 26);
            if (b == blueGhost.x && a == blueGhost.y)
                draw_sprite(mapa, blueGhost.Bit_ghost, a * 26, b * 26);
            if (b == redGhost.x && a == redGhost.y)
                draw_sprite(mapa, redGhost.Bit_ghost, a * 26, b * 26);
            if (b == purpleGhost.x && a == purpleGhost.y)
                draw_sprite(mapa, purpleGhost.Bit_ghost, a * 26, b * 26);
            if (b == greenGhost.x && a == greenGhost.y)
                draw_sprite(mapa, greenGhost.Bit_ghost, a * 26, b * 26);
            if (b == ninman.x && a == ninman.y) {
                if (direction == direita) {
                    switch (1) {
                        case 0:
                            draw_sprite(mapa, ninman.direita1, a * 26, b * 26);
                            rest(25);
                            break;
                        case 1:
                            draw_sprite(mapa, ninman.direita2, a * 26, b * 26);
                            rest(25);
                            break;
                        case 2:
                            draw_sprite(mapa, ninman.direita3, a * 26, b * 26);
                            rest(25);
                            break;
                        case 3:
                            draw_sprite(mapa, ninman.direita4, a * 26, b * 26);
                            rest(25);
                            break;
                        case 4:
                            draw_sprite(mapa, ninman.direita5, a * 26, b * 26);
                            rest(25);
                            break;
                        case 5:
                            draw_sprite(mapa, ninman.direita6, a * 26, b * 26);
                            rest(25);
                            break;
                    }
                }
                if (direction == esquerda) {
                    switch (1) {
                        case 0:
                            draw_sprite(mapa, ninman.esquerda1, a * 26, b * 26);
                            rest(25);
                            break;
                        case 1:
                            draw_sprite(mapa, ninman.esquerda2, a * 26, b * 26);
                            rest(25);
                            break;
                        case 2:
                            draw_sprite(mapa, ninman.esquerda3, a * 26, b * 26);
                            rest(25);
                            break;
                        case 3:
                            draw_sprite(mapa, ninman.esquerda4, a * 26, b * 26);
                            rest(25);
                            break;
                        case 4:
                            draw_sprite(mapa, ninman.esquerda5, a * 26, b * 26);
                            rest(25);
                            break;
                        case 5:
                            draw_sprite(mapa, ninman.esquerda6, a * 26, b * 26);
                            rest(25);
                            break;
                    }
                }
                if (direction == subiu) {
                    switch (1) {
                        case 0:
                            draw_sprite(mapa, ninman.cima1, a * 26, b * 26);
                            rest(25);
                            break;
                        case 1:
                            draw_sprite(mapa, ninman.cima2, a * 26, b * 26);
                            rest(25);
                            break;
                        case 2:
                            draw_sprite(mapa, ninman.cima3, a * 26, b * 26);
                            rest(25);
                            break;
                        case 3:
                            draw_sprite(mapa, ninman.cima4, a * 26, b * 26);
                            rest(25);
                            break;
                        case 4:
                            draw_sprite(mapa, ninman.cima5, a * 26, b * 26);
                            rest(25);
                            break;
                        case 5:
                            draw_sprite(mapa, ninman.cima6, a * 26, b * 26);
                            rest(25);
                            break;
                    }
                }
                if (direction == desceu) {
                    switch (1) {
                        case 0:
                            draw_sprite(mapa, ninman.baixo1, a * 26, b * 26);
                            rest(25);
                            break;
                        case 1:
                            draw_sprite(mapa, ninman.baixo2, a * 26, b * 26);
                            rest(25);
                            break;
                        case 2:
                            draw_sprite(mapa, ninman.baixo3, a * 26, b * 26);
                            rest(25);
                            break;
                        case 3:
                            draw_sprite(mapa, ninman.baixo4, a * 26, b * 26);
                            rest(25);
                            break;
                        case 4:
                            draw_sprite(mapa, ninman.baixo5, a * 26, b * 26);
                            rest(25);
                            break;
                        case 5:
                            draw_sprite(mapa, ninman.baixo6, a * 26, b * 26);

                            break;
                    }
                }
            }
        }
    }
    char msg[1024];
    char temp [32];
    memset(msg, 0, 1024);
    strcpy(msg, "Pontos: ");
    memset(temp, 0, 32);
    itoa(nextDirection, temp, 10);
    strcat(msg, temp);
    memset(temp, 0, 32);
    strcat(msg, "          Vidas:");
    itoa(lifes, temp, 10);
    strcat(msg, temp);
    textout_centre_ex(mapa, font, msg, (NinManMap::getColumnsSize() * 26 / 2), NinManMap::getLinesSize() * 26 + 5, 255, -1);
    draw_sprite(screen, mapa, 400 - (NinManMap::getColumnsSize() * 26 / 2), 300 - (NinManMap::getLinesSize() * 26 / 2) - 5);
    destroy_bitmap(mapa);
    destroy_bitmap(bola);
    destroy_bitmap(bola2);
    destroy_bitmap(fruit);
    destroy_bitmap(bloco);

}

void NinmanGame::run() {
    this->init();
    //Start reading user input
    this->ninman.Start();
    std::vector<Point>::iterator pointIterator;
    while (venceu == 0) {
        DrawLab();
        if (clock() > endwait) {
            ninman.setNextMove(move(ninman.getNextMove()));
            reset = Venceu();
            if (reset) {
                //pilha1.clear();
                //pilha2.clear();
                //pilha3.clear();
                this->sound.stop("siren");
                direction = esquerda;
                if (lifes > 0) {
                    init();
                    ghost_path.clear();
                    this->sound.play("siren", true);
                }
            }
            if (!fruit)
                tfruit++;
            if (tfruit > 100 && !fruit) {
                NinManMap::newFruit();
                fruit = true;
            }
            if (fruit) {
                tfruit = tfruit - 2;
                if (tfruit <= 0) {
                }
                //DeleteFruit();
            }
            if (!power) {
                if (ghost_path.empty() || pointIterator != ghost_path.end()) {
                    ghost_path = this->calcPath();
                    pointIterator = ghost_path.begin();
                }
            }
            orangeGhost.x = pointIterator->x;
            orangeGhost.y = pointIterator->y;
            pointIterator++;
            //ghost_path.pop_front();
        } else {
            //ghost = RandomMove(ghost);
            //ghost1 = RandomMove(ghost1);
            //ghost2 = RandomMove(ghost2);
            //ghost3 = RandomMove(ghost3);
            //ghost4 = RandomMove(ghost4);
            powertime++;
            if (powertime > 25) {
                powertime = 0;
                power = false;
                this->orangeGhost.setBitmap(0, 0);
                this->blueGhost.setBitmap(24, 0);
                this->redGhost.setBitmap(48, 0);
                this->purpleGhost.setBitmap(0, 23);
                this->greenGhost.setBitmap(24, 23);
            }
        }
        endwait = clock() + 0.2 * CLOCKS_PER_SEC;
    }
    if (key[KEY_ESC]) {
        this->sound.stop("siren");
        if (NinmanGameGraph::DrawGameOptions() > 230) {

            this->venceu = -2;
        }
        this->sound.play("siren", true);
    }
}

char* itoa(int value, char* result, int base) {
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