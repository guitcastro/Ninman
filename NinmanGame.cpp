#include "NinmanGame.h"

NinmanGame::NinmanGame() {
    clear(screen);
    this->powertime = 0;
    this->sound = Sound();
    this->power = false;
    this->vida = 3;
    this->sentido = esquerda;
    this->pontos = 0;
    this->sentido2 = 0;
    this->fruit = false;
    this->tfruit = 0;
    this->endwait = clock() + 0.01 * CLOCKS_PER_SEC;
    this->venceu = 0;
    this->LoadPlayer();
    this->Inicio();
    this->Start();
    this->Wait();
}

void NinmanGame::DeleteFruit() {
    for (int a = 0; a < linhas; a++)
        for (int b = 0; b < colunas; b++)
            if (matriz[a][b] == 'x')
                matriz[a][b] = '0';
}

void NinmanGame::setNinmanPosition() {
    for (int a = 0; a < linhas; a++)
        for (int b = 0; b < colunas; b++)
            if (matriz[a][b] == 'p') {
                this->ninman.x = a;
                this->ninman.y = b;
                matriz[a][b] = 0;
            }
}

void NinmanGame::Inicio() {
    this->LoadLab(GetLab(player));
    this->setNinmanPosition();
    this->setGhostsPositions();
    this->ninman.loadBitmaps(player.Ninman_color);
    this->ghost.setBitmap(0, 0);
    this->ghost1.setBitmap(24, 0);
    this->ghost2.setBitmap(48, 0);
    this->ghost3.setBitmap(0, 23);
    this->ghost4.setBitmap(24, 23);
    this->DrawLab();
    BITMAP * temp = load_bitmap("Imagens/GetReady.bmp", NULL);
    draw_sprite(screen, temp, 200, 300 - 43);
    destroy_bitmap(temp);
    this->sound.play("opening");
    rest(3000);
}

void NinmanGame::NewFruit() {
    int x = rand() % linhas, y = rand() % colunas;
    while (matriz[x][y] != '0') {
        x = rand() % linhas;
        y = rand() % colunas;
    }
    matriz[x][y] = 'x';
}

double NinmanGame::ManhattanDist(Point a, Point b) {
    int x1x2, y1y2;
    x1x2 = ((a.x - b.x) > 0) ? (a.x - b.x) : (a.x - b.x) * -1;
    y1y2 = ((a.y - b.y) > 0) ? (a.y - b.y) : (a.y - b.y) * -1;
    return x1x2 + y1y2;
}

bool NinmanGame::alreadyInList(std::list<Point>) {
}

std::list<Point> NinmanGame::calcPath() {
    int dist, shortest = -1;
    Point bestMove;
    int x = ghost.x;
    int y = ghost.y;
    std::list<Point> ghost_path;
    while (shortest != 0 && ghost_path.size() < 100) {
        if (y < colunas - 1 && matriz[x][y + 1] != '1') {
            bestMove.x = x;
            bestMove.y = y + 1;
            shortest = ManhattanDist(bestMove, this->ninman);
        }
        if (x < linhas - 1 && matriz[x + 1][y] != '1') {
            dist = ManhattanDist(Point(x + 1, y), this->ninman);
            if (dist < shortest || shortest < 0) {
                bestMove.x = x + 1;
                bestMove.y = y;
                shortest = dist;
            }
        }
        if (y > 0 && matriz[x][y - 1] != '1') {
            dist = ManhattanDist(Point(x, y - 1), this->ninman);
            if (dist < shortest || shortest < 0) {
                bestMove.x = x;
                bestMove.y = y - 1;
                shortest = dist;
            }
        }
        if (x > 0 && matriz[x - 1][y] != '1') {
            dist = ManhattanDist(Point(x - 1, y), this->ninman);
            if (dist < shortest || shortest < 0) {
                bestMove.x = x - 1;
                bestMove.y = y;
                shortest = dist;
            }
        }
        ghost_path.push_back(bestMove);
        x = bestMove.x;
        y = bestMove.y;
        shortest = -1;
    }
    return ghost_path;
}

void NinmanGame::DestroyerPlayer() {

    std::ofstream y;
    y.open("Player.dat", std::ios::binary);
    player.points = 0;
    y.write((char*) & player, sizeof (player));
    y.close();
}

bool NinmanGame::Venceu() {
    if (!power) {
        if (ghost.x == ninman.x && ghost.y == ninman.y) {
            vida--;
            return true;
        }
        if (ghost1.x == ninman.x && ghost1.y == ninman.y) {
            vida--;
            return true;
        }
        if (ghost2.x == ninman.x && ghost2.y == ninman.y) {
            vida--;
            return true;
        }
        if (ghost3.x == ninman.x && ghost3.y == ninman.y) {
            vida--;
            return true;
        }
        if (ghost4.x == ninman.x && ghost4.y == ninman.y) {
            vida--;
            return true;
        }
        if (vida == 0) {
            venceu = -1;
        }
    } else {
        if (ghost.x == ninman.x && ghost.y == ninman.y)
            ghost.setEyesBitmap();
        if (ghost1.x == ninman.x && ghost1.y == ninman.y)
            ghost1.setEyesBitmap();
        if (ghost2.x == ninman.x && ghost2.y == ninman.y)
            ghost2.setEyesBitmap();
        if (ghost3.x == ninman.x && ghost3.y == ninman.y)
            ghost3.setEyesBitmap();
        if (ghost4.x == ninman.x && ghost4.y == ninman.y)
            ghost4.setEyesBitmap();
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

void NinmanGame::LoadPlayer() {
    std::ifstream x;
    x.open("Player.dat", std::ios::binary);
    if (x.is_open()) {
        x.read((char*) & player, sizeof (player));
    }
    x.close();
}

const char* NinmanGame::GetLab(PLAYER player) {
    std::string temp;
    temp = "Labirintos/";
    temp += player.lab;
    temp += ".txt";
    return temp.c_str();
}

bool NinmanGame::CheckWinner() {
    bool venceu = true;
    for (int a = 0; a < linhas; a++) {
        for (int b = 0; b < colunas; b++) {
            if (matriz[a][b] == '2') {
                return false;
            }
        }
    }
    return venceu;
}

void NinmanGame::setGhostsPositions() {
    for (int a = 0; a < linhas; a++) {
        for (int b = 0; b < colunas; b++) {
            if (matriz[a][b] == 'g') {
                ghost.x = a;
                ghost.y = b;
                matriz[a][b] = 0;
            }
            if (matriz[a][b] == 'h') {
                ghost1.x = a;
                ghost1.y = b;
                matriz[a][b] = 0;
            }
            if (matriz[a][b] == 'j') {
                ghost2.x = a;
                ghost2.y = b;
                matriz[a][b] = 0;
            }
            if (matriz[a][b] == 'k') {
                ghost3.x = a;
                ghost3.y = b;
                matriz[a][b] = 0;
            }
            if (matriz[a][b] == 'l') {
                ghost4.x = a;
                ghost4.y = b;
                matriz[a][b] = 0;
            }
        }
    }
}

int NinmanGame::getCoordinateType(int x, int y) {
    //invalid coordinate
    if (y >= colunas || x >= linhas || x < 0 || y < 0 || matriz[x][y] == '1')
        return -1;
    if (matriz[ninman.x][ninman.y] == '0')
        return 0;
    if (matriz[ninman.x][ninman.y] == 'x')
        return 1;
    if (matriz[ninman.x][ninman.y] == '2')
        return 2;
    if (matriz[ninman.x][ninman.y] == '3')
        return 3;
}

int NinmanGame::move(int NextMove) {
    if (NextMove != 0) {
        int tempSentido = sentido;
        if (NextMove == direita && getCoordinateType(ninman.x, ninman.y + 1) >= 0)
            sentido = direita;
        else if (NextMove == subiu && getCoordinateType(ninman.x - 1, ninman.y) >= 0)
            sentido = subiu;
        else if (NextMove == esquerda && getCoordinateType(ninman.x, ninman.y - 1) >= 0)
            sentido = esquerda;
        else if (NextMove == desceu && getCoordinateType(ninman.x + 1, ninman.y) >= 0)
            sentido = desceu;
        //sentido has changed, pre-move worked
        if (tempSentido != sentido)
            NextMove = 0;
    }
    if (sentido == direita && getCoordinateType(ninman.x, ninman.y + 1) >= 0)
        ninman.y += 1;
    else if (sentido == subiu && getCoordinateType(ninman.x - 1, ninman.y) >= 0)
        ninman.x -= 1;
    else if (sentido == esquerda && getCoordinateType(ninman.x, ninman.y - 1) >= 0)
        ninman.y -= 1;
    else if (sentido == desceu && getCoordinateType(ninman.x + 1, ninman.y) >= 0)
        ninman.x += 1;

    if (ninman.y == colunas - 1)
        ninman.y = 0;
    else if (ninman.x == 0)
        ninman.x = linhas - 1;
    else if (ninman.y == 0)
        ninman.y = colunas - 1;
    else if (ninman.x == linhas - 1)
        ninman.x = 0;

    switch (getCoordinateType(ninman.x, ninman.y)) {
        case 0:
            break;
        case 1:
            this->pontos += 150;
            break;
        case 2:
        {
            this->pontos += 10;
            //this->sound.play("eat");
        }
            break;
        case 3:
            this->power = true;
            break;
        default:
            break;
    }
    matriz[ninman.x][ninman.y] = 'p';
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
void NinmanGame::LoadLab(const char* file_name) {
    std::ifstream arquivo;
    arquivo.open(file_name);
    std::stack <std::string>aux;
    char* linha = new char [1024];
    while (arquivo) {
        arquivo.getline(linha, 1024);
        aux.push(linha);
    }
    aux.pop();
    linhas = aux.size();
    matriz = new std::string [linhas];
    for (int i = linhas - 1; i >= 0; i--) {
        matriz[i] = aux.top();
        aux.pop();
    }
    colunas = matriz[0].size();
    delete linha;
}

void NinmanGame::DrawLab() {
    BITMAP *mapa = create_bitmap(colunas * 26, linhas * 26 + 20);
    BITMAP * bloco = load_bitmap("Imagens/bloco.bmp", NULL);
    BITMAP * bola2 = load_bitmap("Imagens/bola2.bmp", NULL);
    BITMAP * bola = load_bitmap("Imagens/bola.bmp", NULL);
    BITMAP * fruit = load_bitmap("Imagens/fruit.bmp", NULL);
    clear(mapa);
    for (int a = 0; a < colunas; a++) {
        for (int b = 0; b < linhas; b++) {
            if (matriz[b][a] == '1')
                draw_sprite(mapa, bloco, a * 26, b * 26);
            if (matriz[b][a] == '2')
                draw_sprite(mapa, bola2, a * 26, b * 26);
            if (matriz[b][a] == '3')
                draw_sprite(mapa, bola, a * 26, b * 26);
            if (matriz[b][a] == 'x')
                draw_sprite(mapa, fruit, a * 26, b * 26);
            if (b == ghost.x && a == ghost.y)
                draw_sprite(mapa, ghost.Bit_ghost, a * 26, b * 26);
            if (b == ghost1.x && a == ghost1.y)
                draw_sprite(mapa, ghost1.Bit_ghost, a * 26, b * 26);
            if (b == ghost2.x && a == ghost2.y)
                draw_sprite(mapa, ghost2.Bit_ghost, a * 26, b * 26);
            if (b == ghost3.x && a == ghost3.y)
                draw_sprite(mapa, ghost3.Bit_ghost, a * 26, b * 26);
            if (b == ghost4.x && a == ghost4.y)
                draw_sprite(mapa, ghost4.Bit_ghost, a * 26, b * 26);
            if (b == ninman.x && a == ninman.y) {
                if (sentido == direita) {
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
                if (sentido == esquerda) {
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
                if (sentido == subiu) {
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
                if (sentido == desceu) {
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
    NinmanConfig::itoa(pontos, temp, 10);
    strcat(msg, temp);
    memset(temp, 0, 32);
    strcat(msg, "          Vidas:");
    NinmanConfig::itoa(vida, temp, 10);
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
    //Start reading user input
    this->ninman.Start();
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
                sentido = esquerda;
                if (vida > 0) {
                    Inicio();
                    ghost_path.clear();
                    this->sound.play("siren", true);
                }
            }
            if (!fruit)
                tfruit++;
            if (tfruit > 100 && !fruit) {
                NewFruit();
                fruit = true;
            }
            if (fruit) {
                tfruit = tfruit - 2;
                if (tfruit <= 0)
                    DeleteFruit();
            }
            if (!power) {
                //if (ghost_path.empty())
                //ghost_path = this->calcPath();
                //ghost = ghost_path.front();
                //ghost_path.pop_front();
                //pilha1 = moveFantasma1(pilha1);
                //pilha2 = MoverFantasma2(pilha2);
                //pilha3 = MoverFantasma3(pilha3);
                //MoverFantasma5();
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
                    this->ghost.setBitmap(0, 0);
                    this->ghost1.setBitmap(24, 0);
                    this->ghost2.setBitmap(48, 0);
                    this->ghost3.setBitmap(0, 23);
                    this->ghost4.setBitmap(24, 23);
                }
            }
            endwait = clock() + 0.2 * CLOCKS_PER_SEC;
        }
        if (key[KEY_ESC]) {
            this->sound.stop("siren");
            if (NinmanGameGraph::DrawGameOptions() > 230) {
                this->venceu = -2;
                DestroyerPlayer();
            }
            this->sound.play("siren", true);
        }
    }
}