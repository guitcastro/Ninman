#include "header/NinmanMenu.h"

/*
 * Start Allegro and draw the game Menu
 */
NinmanMenu::NinmanMenu() {
    NinmanConfig::loadConfig();
    install_keyboard();
    install_mouse();
    install_timer();
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) < 0)
        install_sound(DIGI_OSS, MIDI_NONE, NULL);
    set_color_depth(32);
    if (NinmanConfig::getFullScreenOption())
        set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0);
    else
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    set_volume(NinmanConfig::getVolume(), 0);
    DrawMenu(220);
    MainMenu();
}

/*
 * Show players Scores
 */
void NinmanMenu::Score() {
    BITMAP * fundo;
    BITMAP * menu;
    BITMAP * pacman;
    do {
        menu = load_bitmap("Imagens/Score.bmp", NULL);
        fundo = load_bitmap("Imagens/fundo.bmp", NULL);
        pacman = load_bitmap("Imagens/pacman.bmp", NULL);
        textout_centre_ex(menu, font, NinmanConfig::getScore(0), 163, 30, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(1), 163, 50, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(2), 163, 70, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(3), 163, 90, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(4), 163, 110, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(5), 163, 130, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(6), 163, 150, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(7), 163, 170, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(8), 163, 190, WHITE, -1);
        textout_centre_ex(menu, font, NinmanConfig::getScore(9), 163, 210, WHITE, -1);
        draw_sprite(fundo, menu, 400 - 164, 350 - 153);
        draw_sprite(fundo, pacman, 215, 440);
        draw_sprite(screen, fundo, 0, 0);
        destroy_bitmap(fundo);
        destroy_bitmap(menu);
        destroy_bitmap(pacman);
        readkey();
    } while (!key[KEY_ESC] && !key[KEY_ENTER]);
}

/*
 * Draw player Enter name Scren
 */
void NinmanMenu::DrawStartGame(int y, std::string nome) {
    BITMAP * fundo;
    BITMAP * menu;
    BITMAP * pacman;
    menu = load_bitmap("Imagens/StartGame.bmp", NULL);
    fundo = load_bitmap("Imagens/fundo.bmp", NULL);
    pacman = load_bitmap("Imagens/pacman.bmp", NULL);
    textout_centre_ex(menu, font, "Enter your name:", 163, 30, WHITE, -1);
    textout_centre_ex(menu, font, nome.c_str(), 163, 42, WHITE, -1);
    vline(menu, nome.size() * 4 + 163, 40, 50, WHITE);
    draw_sprite(fundo, menu, 400 - 164, 350 - 153);
    draw_sprite(fundo, pacman, 215, y);
    draw_sprite(screen, fundo, 0, 0);
    destroy_bitmap(fundo);
    destroy_bitmap(menu);
    destroy_bitmap(pacman);
}

/*
 * Read user inputs
 */
std::string NinmanMenu::TextBox() {
    int y = 220 + 55;
    std::string edittext; // an empty string for editting
    std::string::iterator iter = edittext.begin(); // string iterator
    DrawStartGame(y, edittext);
    int caret = 0; // tracks the text caret
    do {
        while (keypressed()) {
            int newkey = readkey();
            char ASCII = newkey & 0xff;

            // a character key was pressed; add it to the string
            if (ASCII >= 32 && ASCII <= 126) {
                // add the new char, inserting or replacing as need be
                if (iter == edittext.end())
                    if (caret < 31) {
                        iter = edittext.insert(iter, ASCII);
                        caret++;
                        iter++;
                    }
            }// some other, "special" key was pressed; handle it here
            if (key[KEY_ESC])
                return "-1";
            if (key[KEY_ENTER]) {
                if (y == 220 + 55)
                    return edittext;
                else
                    return "-1";
            }
            if (key[KEY_DOWN])
                y = y + 55;
            if (key[KEY_UP])
                y = y - 55;
            if (key[KEY_BACKSPACE]) {
                if (iter != edittext.begin()) {
                    caret--;
                    iter--;
                    iter = edittext.erase(iter);
                }
            }
            if (y > 220 + 55 + 55)
                y = 220 + 55;
            if (y < 220 + 55)
                y = 220 + 55 + 55;
            DrawStartGame(y, edittext);
        }
    } while (true); // end of game loop
}

int NinmanMenu::MainMenu() {
    int y = 220;
    while (true) {
        readkey();
        if (key[KEY_ESC])
            return 0;
        if (key[KEY_DOWN]) {
            y = y + 55;
            if (y > 440)
                y = 220;
        }
        if (key[KEY_UP]) {
            y = y - 55;
            if (y < 220)
                y = 440;
        }
        if (key[KEY_ENTER]) {
            if (y == 220) {
                std::string player;
                while (player == "")
                    player = TextBox();
                if (player != "-1")
                    NinmanGame(player.c_str());
            }
            if (y == 275) {
                Score();
                y = 220;
            }
            if (y == 330) {
                OptionMenu();
                y = 220;
            }
            if (y == 385) {
                About();
                y = 220;
            }

            if (y == 440)
                break;
            clear_keybuf();
        }
        DrawMenu(y);
    }
    return 0;
}

void NinmanMenu::About() {
    BITMAP * fundo;
    BITMAP * menu;
    BITMAP * pacman;
    fundo = load_bitmap("Imagens/fundo.bmp", NULL);
    menu = load_bitmap("Imagens/about.bmp", NULL);
    pacman = load_bitmap("Imagens/pacman.bmp", NULL);
    draw_sprite(fundo, menu, 400 - 163, 350 - 153);
    draw_sprite(fundo, pacman, 215, 440);
    draw_sprite(screen, fundo, 0, 0);
    readkey();
    while (!key[KEY_ENTER] && !key[KEY_ESC]);
    destroy_bitmap(fundo);
    destroy_bitmap(menu);
    destroy_bitmap(pacman);
}

void NinmanMenu::OptionMenu() {
    int y = 220;
    DrawOptionMenu(y);
    while (true) {
        readkey();
        if (key[KEY_DOWN]) {
            y = y + 55;
            if (y > 440)
                y = 220;
        }
        if (key[KEY_UP]) {
            y = y - 55;
            if (y < 220)
                y = 440;
        }
        if (key[KEY_LEFT] || key[KEY_RIGHT]) {
            if (y == 220) {
                if (NinmanConfig::getFullScreenOption())
                    NinmanConfig::setFullScreenOption(false);
                else
                    NinmanConfig::setFullScreenOption(true);
                if (NinmanConfig::getFullScreenOption())
                    set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0);
                else
                    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
            }
            if (y == 275) {

                if (key[KEY_LEFT]) {
                    NinmanConfig::setVolume(NinmanConfig::getVolume() - 25);
                }
                if (key[KEY_RIGHT]) {

                    NinmanConfig::setVolume(NinmanConfig::getVolume() + 25);
                    set_volume(NinmanConfig::getVolume(), 0);
                }
                set_volume(NinmanConfig::getVolume(), 0);
            }
            if (y == 330) {
                if (key[KEY_LEFT])
                    NinmanConfig::setNimanColor(-25);
                if (key[KEY_RIGHT])
                    NinmanConfig::setNimanColor(25);

            }
            if (y == 385) {
                if (key[KEY_LEFT])
                    NinmanConfig::setLab(-1);
                if (key[KEY_RIGHT])
                    NinmanConfig::setLab(1);
            }

        }
        if (key[KEY_ENTER]) {
            if (y == 440)
                break;
        }
        if (key[KEY_ESC])
            break;
        DrawOptionMenu(y);
    }
}

const char* NinmanMenu::GetVolumeString() {
    switch (NinmanConfig::getVolume()) {

        case 0:
            return "Imagens/volume_00.bmp";
        case 25:
            return "Imagens/volume_01.bmp";
        case 50:
            return "Imagens/volume_02.bmp";
        case 75:
            return "Imagens/volume_03.bmp";
        case 100:
            return "Imagens/volume_04.bmp";
        case 125:
            return "Imagens/volume_05.bmp";
        case 150:
            return "Imagens/volume_06.bmp";
        case 175:
            return "Imagens/volume_07.bmp";
        case 200:
            return "Imagens/volume_08.bmp";
        case 225:
            return "Imagens/volume_09.bmp";
        case 250:
            return "Imagens/volume_10.bmp";
    }
    return "";
}

void NinmanMenu::DrawOptionMenu(int y) {
    BITMAP * fundo;
    BITMAP * menu;
    BITMAP * pacman;
    BITMAP * sprite = load_bitmap("Imagens/Ninman.bmp", NULL);
    BITMAP * FS = load_bitmap("Imagens/ONOFF.bmp", NULL);
    BITMAP* temp = create_bitmap(100, 26);
    clear_to_color(temp, TRANSPARENTE);
    blit(sprite, temp, 0, 0, 3, 3, 100, 26);
    BITMAP * som;
    fundo = load_bitmap("Imagens/fundo.bmp", NULL);
    som = load_bitmap(GetVolumeString(), NULL);
    menu = load_bitmap("Imagens/OptionMenu.bmp", NULL);
    if (NinmanConfig::getFullScreenOption())
        rect(menu, 199, 30, 200 + 29, 30 + 25, WHITE);

    else
        rect(menu, 199 + 31, 30, 200 + 29 + 30, 30 + 25, WHITE);
    pacman = load_bitmap("Imagens/pacman.bmp", NULL);
    textout_centre_ex(menu, font, "Use Left and Right arrow", 163, 285, 255, -1);
    textout_centre_ex(menu, font, "to change settings.", 163, 295, 255, -1);
    textout_centre_ex(menu, font, NinmanConfig::getLab(), 175, 205, WHITE, -1);
    draw_sprite(menu, FS, 200, 30);
    draw_sprite(menu, som, 120, 76);
    draw_sprite(menu, temp, 180, 73 + 65);
    rect(menu, 180 + NinmanConfig::getNimanColor(), 138, 181 + 25 + NinmanConfig::getNimanColor(), 138 + 25, WHITE);
    draw_sprite(fundo, menu, 400 - 163, 350 - 153);
    draw_sprite(fundo, pacman, 215, y);
    draw_sprite(screen, fundo, 0, 0);
    destroy_bitmap(fundo);
    destroy_bitmap(temp);
    destroy_bitmap(sprite);
    destroy_bitmap(menu);
    destroy_bitmap(pacman);
    destroy_bitmap(som);
}

void NinmanMenu::DrawMenu(int y) {
    BITMAP * fundo;
    BITMAP * menu;
    BITMAP * pacman;
    fundo = load_bitmap("Imagens/fundo.bmp", NULL);
    menu = load_bitmap("Imagens/menu.bmp", NULL);
    pacman = load_bitmap("Imagens/pacman.bmp", NULL);
    draw_sprite(fundo, menu, 400 - 163, 350 - 153);
    draw_sprite(fundo, pacman, 215, y);
    draw_sprite(screen, fundo, 0, 0);
    destroy_bitmap(fundo);
    destroy_bitmap(menu);
    destroy_bitmap(pacman);
}
