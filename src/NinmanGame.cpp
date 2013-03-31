#include "NinmanGame.h"

NinmanGame::~NinmanGame(){
    delete this->orangeGhost;
    delete this->blueGhost;
    delete this->redGhost;
    delete this->pinkGhost;
    delete this->greenGhost;
}

NinmanGame::NinmanGame(const char* player_name) {
    //clear screen
    clear(screen);
    //initialize game variable
    this->player_name = player_name;
    this->powertime = 0;
    this->vida = 3;
    this->power = false;
    this->sentido = esquerda;
    this->pontos = 0;
    this->sentido2 = 0;
    this->fruit = false;
    this->tfruit = 0;
    this->endwait = clock() + 0.01 * CLOCKS_PER_SEC;
    this->venceu = 0;
    this->sound = Sound();
    //start game
    this->Start();
    this->Wait();
}

void NinmanGame::init() {

    this->map = new NinManMap (NinmanConfig::getLab());
    this->remainingDots = map->getNumberOfDots();

    this->linhas = map->getNumberOfLines();
    this->colunas = map->getNumberOfColumns();

    this->orangeGhost = new Ghost (map);
    this->blueGhost = new Ghost (map);
    this->redGhost = new Ghost (map);
    this->pinkGhost = new Ghost (map);
    this->greenGhost = new Ghost (map);

    this->setNinmanPosition();
    this->setGhostsPositions();
    this->ninman.loadBitmaps(NinmanConfig::getNimanColor());
    this->orangeGhost->setBitmap(0, 0);
    this->blueGhost->setBitmap(24, 0);
    this->redGhost->setBitmap(48, 0);
    this->pinkGhost->setBitmap(0, 23);
    this->greenGhost->setBitmap(24, 23);
    this->DrawLab();
    BITMAP * temp = load_bitmap("Imagens/GetReady.bmp", NULL);
    draw_sprite(screen, temp, 200, 300 - 43);
    destroy_bitmap(temp);
    this->sound.play("opening");
    rest(3000);
}

void inline NinmanGame::DeleteFruit() {
    this->map->replacePointValue('x','0');
}

void NinmanGame::setNinmanPosition() {
    this->ninman.setPoint(this->map->getNinmanInitialPosition());
}

bool NinmanGame::Venceu() {
    if (!power) {
        if (orangeGhost->x == ninman.x && orangeGhost->y == ninman.y) {
            vida--;
            return true;
        }
        if (blueGhost->x == ninman.x && blueGhost->y == ninman.y) {
            vida--;
            return true;
        }
        if (redGhost->x == ninman.x && redGhost->y == ninman.y) {
            vida--;
            return true;
        }
        if (pinkGhost->x == ninman.x && pinkGhost->y == ninman.y) {
            vida--;
            return true;
        }
        if (greenGhost->x == ninman.x && greenGhost->y == ninman.y) {
            vida--;
            return true;
        }
        if (vida == 0) {
            venceu = -1;
        }
    } else {
        if (orangeGhost->x == ninman.x && orangeGhost->y == ninman.y)
           orangeGhost->setEyesBitmap();
        if (blueGhost->x == ninman.x && blueGhost->y == ninman.y)
            blueGhost->setEyesBitmap();
        if (redGhost->x == ninman.x && redGhost->y == ninman.y)
            redGhost->setEyesBitmap();
        if (pinkGhost->x == ninman.x && pinkGhost->y == ninman.y)
            pinkGhost->setEyesBitmap();
        if (greenGhost->x == ninman.x && greenGhost->y == ninman.y)
            greenGhost->setEyesBitmap();
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
        if (ghost.y + 1 < colunas) {
            if (matriz[ghost.x][ghost.y + 1] == '1') {
                sentido2 = 0;
            }
        }
    }

    if (sentido2 == subiu) {
        if (ghost.x - 1 >= 0) {
            if (matriz[ghost.x - 1][ghost.y] == '1') {
                sentido2 = 0;
            }
        }
    }
    if (sentido2 == esquerda) {
        if (ghost.y - 1 >= 0) {
            if (matriz[ghost.x][ghost.y - 1] == '1') {
                sentido2 = 0;
            }
        }
    }
    if (sentido2 == desceu) {
        if (ghost.x < linhas) {
            if (matriz[ghost.x + 1][ghost.y] == '1') {
                sentido2 = 0;
            }
        }
    }

    if (sentido2 == 0)
        sentido2 = iSecret;

    if (sentido2 == direita) {
        if (ghost.y + 1 < colunas) {
            if (matriz[ghost.x][ghost.y + 1] != '1') {
                matriz[ghost.x][ghost.y] = '0';
                ghost.y = ghost.y + 1;
                if (ghost.y == colunas - 1)
                    ghost.y = 0;


            }
        }
    }

    if (sentido2 == subiu) {
        if (ghost.color - 1 >= 0) {
            if (matriz[ghost.color - 1][ghost.y] != '1') {
                ghost.color = ghost.color - 1;
                if (ghost.color == 0)
                    ghost.color = linhas - 1;

            }
        }
    }
    if (sentido2 == esquerda) {
        if (ghost.y - 1 >= 0) {
            if (matriz[ghost.color][ghost.y - 1] != '1') {
                ghost.y = ghost.y - 1;
                if (ghost.y == 0)
                    ghost.y = colunas - 1;
            }
        }
    }
    if (sentido2 == desceu) {
        if (ghost.color < linhas) {
            if (matriz[ghost.color + 1][ghost.y] != '1') {
                ghost.color = ghost.color + 1;

                if (ghost.color == linhas - 1)
                    ghost.color = 0;
            }
        }
    }
    return ghost;
}
 */

inline bool NinmanGame::CheckWinner() {
    return this->remainingDots == 0;
}

void NinmanGame::setGhostsPositions() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            orangeGhost->setPoint(this->map->getOrangeGhostInitialPosition());
            blueGhost->setPoint(this->map->getBlueGhostInitialPosition());
            redGhost->setPoint(this->map->getRedGhostInitialPosition());
            pinkGhost->setPoint(this->map->getPinkGhostInitialPosition());
            greenGhost->setPoint(this->map->getGreenGhostInitialPosition());
        }
    }
}

int NinmanGame::getCoordinateType(int x, int y) {
    //invalid coordinate
    if (!map->isValidCoordinate(x,y))
        return -1;
    if (map->getPointValue(x,y) == '0')
        return 0;
    else if (map->getPointValue(x,y) == 'x')
        return 1;
    else if (map->getPointValue(x,y) == '2')
        return 2;
    else if (map->getPointValue(x,y) == '3')
        return 3;
}

int NinmanGame::move(int NextMove) {
    if (NextMove != 0) {
        int tempSentido = sentido;
        if (NextMove == direita && map->isValidCoordinate(ninman.x +1,ninman.y))
            sentido = direita;
        else if (NextMove == subiu && map->isValidCoordinate(ninman.x,ninman.y-1))
            sentido = subiu;
        else if (NextMove == esquerda && map->isValidCoordinate(ninman.x - 1,ninman.y))
            sentido = esquerda;
        else if (NextMove == desceu && map->isValidCoordinate(ninman.x,ninman.y +1 ))
            sentido = desceu;
        //sentido has changed, pre-move worked
        if (tempSentido != sentido)
            NextMove = 0;
    }
    if (sentido == direita && map->isValidCoordinate(ninman.x +1,ninman.y))
        ninman.x += 1;
    else if (sentido == subiu && map->isValidCoordinate(ninman.x,ninman.y -1))
        ninman.y -= 1;
    else if (sentido == esquerda && map->isValidCoordinate(ninman.x -1,ninman.y))
        ninman.x -= 1;
    else if (sentido == desceu && map->isValidCoordinate(ninman.x,ninman.y +1))
        ninman.y += 1;

    if (ninman.y == linhas - 1)
        ninman.y = 0;
    else if (ninman.x == 0)
        ninman.x = colunas - 1;
    else if (ninman.y == 0)
        ninman.y = linhas - 1;
    else if (ninman.x == colunas - 1)
        ninman.x = 0;

    switch (getCoordinateType(ninman.x,ninman.y)) {
        case 0:
            break;
        case 1:
            this->pontos += 150;
            break;
        case 2:
        {
            this->pontos += 10;
            this->remainingDots--;
        }
            break;
        case 3:
            this->power = true;
            break;
        default:
            break;
    }
    this->map->setPointValue(ninman.x,ninman.y,'0');
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
        if (ghost4.y + 1 < colunas) {
            if (matriz[ghost4.color][ghost4.y + 1] == '1') {
                sentido2 = 0;
            }
        }
    }

    if (sentido2 == subiu) {
        if (ghost4.color - 1 >= 0) {
            if (matriz[ghost4.color - 1][ghost4.y] == '1') {
                sentido2 = 0;
            }
        }
    }
    if (sentido2 == esquerda) {
        if (ghost4.y - 1 >= 0) {
            if (matriz[ghost4.color][ghost4.y - 1] == '1') {
                sentido2 = 0;
            }
        }
    }
    if (sentido2 == desceu) {
        if (ghost4.color < linhas) {
            if (matriz[ghost4.color + 1][ghost4.y] == '1') {
                sentido2 = 0;
            }
        }
    }

    if (sentido2 == 0)
        sentido2 = iSecret;

    if (sentido2 == direita) {
        if (ghost4.y + 1 < colunas) {
            if (matriz[ghost4.color][ghost4.y + 1] != '1') {
                matriz[ghost4.color][ghost4.y] = '0';
                ghost4.y = ghost4.y + 1;
                if (ghost4.y == colunas - 1)
                    ghost4.y = 0;


            }
        }
    }

    if (sentido2 == subiu) {
        if (ghost4.color - 1 >= 0) {
            if (matriz[ghost4.x - 1][ghost4.y] != '1') {
                ghost4.x = ghost4.x - 1;
                if (ghost4.x == 0)
                    ghost4.x = linhas - 1;

            }
        }
    }
    if (sentido2 == esquerda) {
        if (ghost4.y - 1 >= 0) {
            if (matriz[ghost4.x][ghost4.y - 1] != '1') {
                ghost4.y = ghost4.y - 1;
                if (ghost4.y == 0)
                    ghost4.y = colunas - 1;
            }
        }
    }
    if (sentido2 == desceu) {
        if (ghost4.x < linhas) {
            if (matriz[ghost4.x + 1][ghost4.y] != '1') {
                ghost4.x = ghost4.x + 1;

                if (ghost4.x == linhas - 1)
                    ghost4.x = 0;
            }
        }
    }
}
 */

void NinmanGame::DrawLab() {
    BITMAP *mapa = create_bitmap(colunas * 26, linhas * 26 + 20);
    BITMAP * bloco = load_bitmap("Imagens/bloco.bmp", NULL);
    BITMAP * bola2 = load_bitmap("Imagens/bola2.bmp", NULL);
    BITMAP * bola = load_bitmap("Imagens/bola.bmp", NULL);
    BITMAP * fruit = load_bitmap("Imagens/fruit.bmp", NULL);
    clear(mapa);
    for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
            if (this->map->getPointValue(j,i) == '1')
                draw_sprite(mapa, bloco, j * 26, i * 26);
            if (this->map->getPointValue(j,i) == '2')
                draw_sprite(mapa, bola2, j * 26, i * 26);
            if (this->map->getPointValue(j,i) == '3')
                draw_sprite(mapa, bola, j * 26, i * 26);
            if (this->map->getPointValue(j,i) == 'x')
                draw_sprite(mapa, fruit, j * 26, i * 26);
            if (j == orangeGhost->x && i == orangeGhost->y)
                draw_sprite(mapa, orangeGhost->Bit_ghost, j * 26, i * 26);
            if (j == blueGhost->x && i == blueGhost->y)
                draw_sprite(mapa, blueGhost->Bit_ghost, j * 26, i * 26);
            if (j == redGhost->x && i == redGhost->y)
                draw_sprite(mapa, redGhost->Bit_ghost, j * 26, i * 26);
            if (j == pinkGhost->x && i == pinkGhost->y)
                draw_sprite(mapa, pinkGhost->Bit_ghost, j * 26, i * 26);
            if (j == greenGhost->x && i == greenGhost->y)
                draw_sprite(mapa, greenGhost->Bit_ghost, j * 26, i * 26);
            if (j == ninman.x && i == ninman.y) {
                 if (sentido == direita) {
                    switch (1) {
                        case 0:
                            draw_sprite(mapa, ninman.direita1, j * 26, i * 26);
                            rest(25);
                            break;
                        case 1:
                            draw_sprite(mapa, ninman.direita2, j * 26, i * 26);
                            rest(25);
                            break;
                        case 2:
                            draw_sprite(mapa, ninman.direita3, j * 26, i * 26);
                            rest(25);
                            break;
                        case 3:
                            draw_sprite(mapa, ninman.direita4, j * 26, i * 26);
                            rest(25);
                            break;
                        case 4:
                            draw_sprite(mapa, ninman.direita5, j * 26, i * 26);
                            rest(25);
                            break;
                        case 5:
                            draw_sprite(mapa, ninman.direita6, j * 26, i * 26);
                            rest(25);
                            break;
                    }
                }
                if (sentido == esquerda) {
                    switch (1) {
                        case 0:
                            draw_sprite(mapa, ninman.esquerda1, j * 26, i * 26);
                            rest(25);
                            break;
                        case 1:
                            draw_sprite(mapa, ninman.esquerda2, j * 26, i * 26);
                            rest(25);
                            break;
                        case 2:
                            draw_sprite(mapa, ninman.esquerda3, j * 26, i * 26);
                            rest(25);
                            break;
                        case 3:
                            draw_sprite(mapa, ninman.esquerda4, j * 26, i * 26);
                            rest(25);
                            break;
                        case 4:
                            draw_sprite(mapa, ninman.esquerda5, j * 26, i * 26);
                            rest(25);
                            break;
                        case 5:
                            draw_sprite(mapa, ninman.esquerda6, j * 26, i * 26);
                            rest(25);
                            break;
                    }
                }
                if (sentido == subiu) {
                    switch (1) {
                        case 0:
                            draw_sprite(mapa, ninman.cima1, j * 26, i * 26);
                            rest(25);
                            break;
                        case 1:
                            draw_sprite(mapa, ninman.cima2, j * 26, i * 26);
                            rest(25);
                            break;
                        case 2:
                            draw_sprite(mapa, ninman.cima3, j * 26, i * 26);
                            rest(25);
                            break;
                        case 3:
                            draw_sprite(mapa, ninman.cima4, j * 26, i * 26);
                            rest(25);
                            break;
                        case 4:
                            draw_sprite(mapa, ninman.cima5, j * 26, i * 26);
                            rest(25);
                            break;
                        case 5:
                            draw_sprite(mapa, ninman.cima6, j * 26, i * 26);
                            rest(25);
                            break;
                    }
                }
                if (sentido == desceu) {
                    switch (1) {
                        case 0:
                            draw_sprite(mapa, ninman.baixo1, j * 26, i * 26);
                            rest(25);
                            break;
                        case 1:
                            draw_sprite(mapa, ninman.baixo2, j * 26, i * 26);
                            rest(25);
                            break;
                        case 2:
                            draw_sprite(mapa, ninman.baixo3, j * 26, i * 26);
                            rest(25);
                            break;
                        case 3:
                            draw_sprite(mapa, ninman.baixo4, j * 26, i * 26);
                            rest(25);
                            break;
                        case 4:
                            draw_sprite(mapa, ninman.baixo5, j * 26, i * 26);
                            rest(25);
                            break;
                        case 5:
                            draw_sprite(mapa, ninman.baixo6, j * 26, i * 26);
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
    itoa(pontos, temp, 10);
    strcat(msg, temp);
    memset(temp, 0, 32);
    strcat(msg, "          Vidas:");
    itoa(vida, temp, 10);
    strcat(msg, temp);
    textout_centre_ex(mapa, font, msg, (colunas * 26 / 2), linhas * 26 + 5, 255, -1);
    draw_sprite(screen, mapa, 400 - (colunas * 26 / 2), 300 - (linhas * 26 / 2) - 5);
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
    while (venceu == 0) {
        DrawLab();
        if (clock() > endwait) {
            ninman.setNextMove(move(ninman.getNextMove()));
            reset = Venceu();
            if (reset) {
                this->sound.stop("siren");
                sentido = esquerda;
                if (vida > 0) {
                    init();
                    this->sound.play("siren", true);
                }
            }
            if (!fruit)
                tfruit++;
            if (tfruit > 100 && !fruit) {
                //this->map->showFruit();
                //fruit = true;
            }
            if (fruit) {
                tfruit = tfruit - 2;
                if (tfruit <= 0)
                    DeleteFruit();
            }
            if (!power) {
                orangeGhost->move(this->ninman);
                blueGhost->move(this->ninman);
                redGhost->move(this->ninman);
                greenGhost->move(this->ninman);
                pinkGhost->move(this->ninman);

            } else {
                //ghost = RandomMove(ghost);
                powertime++;
                if (powertime > 25) {
                    powertime = 0;
                    power = false;
                    orangeGhost->setBitmap(0, 0);
                    this->blueGhost->setBitmap(24, 0);
                    this->redGhost->setBitmap(48, 0);
                    this->pinkGhost->setBitmap(0, 23);
                    this->greenGhost->setBitmap(24, 23);
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