#include "NinmanGame.h"

NinmanGame::NinmanGame() {
    this->powertime = 0;
    this->power = false;
    this->vida = 3;
    this->sentido = esquerda;
    this->pontos = 0;
    this->sentido2 = 0;
    LoadPlayer();
    clear(screen);
    venceu = 0;
    Inicio();
    this->run();
    //conf.RefreshScore(pontos, player.nome);
}

void NinmanGame::DeleteFruit() {
    for (int a = 0; a < linhas; a++) {
        for (int b = 0; b < colunas; b++) {
            if (matriz[a][b] == 'x') {
                matriz[a][b] = '0';
            }
        }
    }
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
    LoadLab(GetLab(player));
    setNinmanPosition();
    setGhostsPositions();
    this->ninman.loadBitmaps(player.Ninman_color);
    this->ghost.setBitmap(0, 0);
    this->ghost1.setBitmap(24, 0);
    this->ghost2.setBitmap(48, 0);
    this->ghost3.setBitmap(0, 23);
    this->ghost4.setBitmap(24, 23);
    DrawLab();
    BITMAP * temp = load_bitmap("Imagens/GetReady.bmp", NULL);
    draw_sprite(screen, temp, 200, 300 - 43);
    destroy_bitmap(temp);
    SAMPLE * abertura = load_sample("Sound/opening_song.wav");
    play_sample(abertura, 255, 0, 1000, 0);
    rest(4000);
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

void NinmanGame::GameOptions() {

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
            if (y == 275) {
                //SaveGame();
                venceu = -2;
            }
            if (y == 330) {

                DestroyerPlayer();
                venceu = -2;
            }
            break;
        }
        DrawOptions(y);
    }
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

void NinmanGame::DrawOptions(int y) {

    DrawLab();
    BITMAP * pacman;
    BITMAP * menu;
    menu = load_bitmap("Imagens/GameMenu.bmp", NULL);
    pacman = load_bitmap("Imagens/pacman.bmp", NULL);
    draw_sprite(screen, menu, 400 - 163, 350 - 153);
    draw_sprite(screen, pacman, 215, y);
    destroy_bitmap(menu);
    destroy_bitmap(pacman);
}

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

int NinmanGame::Mover(int NextMove) {
    SAMPLE * cumeu = load_sample("Sound/eating.short.wav");
    if (NextMove == direita) {
        if (ninman.y + 1 < colunas) {
            if (matriz[ninman.x][ninman.y + 1] != '1') {
                sentido = direita;
                NextMove = 0;
            }
        }
    }

    if (NextMove == subiu) {
        if (ninman.x - 1 >= 0) {
            if (matriz[ninman.x - 1][ninman.y] != '1') {
                sentido = subiu;
                NextMove = 0;
            }
        }
    }
    if (NextMove == esquerda) {
        if (ninman.y - 1 >= 0) {
            if (matriz[ninman.x][ninman.y - 1] != '1') {
                sentido = esquerda;
                NextMove = 0;
            }
        }
    }
    if (NextMove == desceu) {
        if (ninman.x < linhas) {
            if (matriz[ninman.x + 1][ninman.y] != '1') {
                sentido = desceu;
                NextMove = 0;
            }
        }
    }


    if (sentido == direita) {
        if (ninman.y + 1 < colunas) {
            if (matriz[ninman.x][ninman.y + 1] != '1') {
                matriz[ninman.x][ninman.y] = '0';
                ninman.y = ninman.y + 1;
                if (matriz[ninman.x][ninman.y] == '3')
                    this->power = true;
                if (matriz[ninman.x][ninman.y] == 'x')
                    pontos = pontos + 150;
                if (matriz[ninman.x][ninman.y] == '2') {
                    pontos = pontos + 10;
                    play_sample(cumeu, 255, 0, 1000, 0);
                }
                if (ninman.y == colunas - 1)
                    ninman.y = 0;
                matriz[ninman.x][ninman.y] = 'p';

            }
        }
    }

    if (sentido == subiu) {
        if (ninman.x - 1 >= 0) {
            if (matriz[ninman.x - 1][ninman.y] != '1') {
                matriz[ninman.x][ninman.y] = '0';
                ninman.x = ninman.x - 1;
                if (matriz[ninman.x][ninman.y] == '2') {
                    pontos = pontos + 10;
                    play_sample(cumeu, 255, 0, 1000, 0);
                }
                if (matriz[ninman.x][ninman.y] == '3')
                    this->power = true;
                if (matriz[ninman.x][ninman.y] == 'x')
                    pontos = pontos + 150;
                if (ninman.x == 0)
                    ninman.x = linhas - 1;
                matriz[ninman.x][ninman.y] = 'p';
            }
        }
    }
    if (sentido == esquerda) {
        if (ninman.y - 1 >= 0) {
            if (matriz[ninman.x][ninman.y - 1] != '1') {
                matriz[ninman.x][ninman.y] = '0';
                ninman.y = ninman.y - 1;
                if (matriz[ninman.x][ninman.y] == '2') {
                    play_sample(cumeu, 255, 0, 1000, 0);
                }
            }
            pontos = pontos + 10;
            if (matriz[ninman.x][ninman.y] == '3')
                this->power = true;
            if (matriz[ninman.x][ninman.y] == 'x')
                pontos = pontos + 150;
            if (ninman.y == 0)
                ninman.y = colunas - 1;
            matriz[ninman.x][ninman.y] = 'p';
        }
    }

    if (sentido == desceu) {
        if (ninman.x < linhas) {
            if (matriz[ninman.x + 1][ninman.y] != '1') {
                matriz[ninman.x][ninman.y] = '0';

                ninman.x = ninman.x + 1;
                if (matriz[ninman.x][ninman.y] == '2') {
                    pontos = pontos + 10;
                    play_sample(cumeu, 255, 0, 1000, 0);
                }
                if (matriz[ninman.x][ninman.y] == '3')
                    this->power = true;
                if (matriz[ninman.x][ninman.y] == 'x')
                    pontos = pontos + 150;

                if (ninman.x == linhas - 1)
                    ninman.x = 0;
                matriz[ninman.x][ninman.y] = 'p';
            }
        }
    }

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

int NinmanGame::LerMovimento(int NextMove) {
    if (key[KEY_DOWN])
        NextMove = desceu;
    if (key[KEY_UP])
        NextMove = subiu;
    if (key[KEY_LEFT])
        NextMove = esquerda;
    if (key[KEY_RIGHT])
        NextMove = direita;

    return NextMove;
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
    char * temp = new char [32];
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

    int Nextmove = 0, tfruit = 0;
    SAMPLE * siren = load_sample("Sound/siren.wav");
    std::list <Point> ghost_path; //, pilha1, pilha2, pilha3;
    bool reset;
    bool fruit = false;
    clock_t endwait = clock() + 0.01 * CLOCKS_PER_SEC;
    while (venceu == 0) {
        DrawLab();
        Nextmove = LerMovimento(Nextmove);
        if (clock() > endwait) {
            Nextmove = Mover(Nextmove);
            reset = Venceu();
            if (reset) {
                //pilha1.clear();
                //pilha2.clear();
                //pilha3.clear();
                stop_sample(siren);
                sentido = esquerda;
                if (vida > 0) {
                    Inicio();
                    ghost_path.clear();
                    play_sample(siren, 255, 0, 1000, true);
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
                //pilha1 = MoverFantasma1(pilha1);
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
            endwait = clock() + 0.01 * CLOCKS_PER_SEC;
        }
        if (key[KEY_ESC]) {
            stop_sample(siren);
            GameOptions();
            play_sample(siren, 255, 0, 1000, true);
        }
    }
}