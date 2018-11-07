#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <string.h>

int start_x;
int start_y;
int width_global;
int height_global;
WINDOW *w;

#define BASE_WIDTH 90
#define BASE_HEIGHT 15

#define MAX_WIDTH 110
#define MAX_HEIGHT 16

void setcolor(WINDOW *w) {
    if (has_colors()) {

        start_color();
        init_pair(1, COLOR_BLACK, COLOR_WHITE);
        attron(COLOR_PAIR(1));
        wbkgd(w, A_NORMAL | COLOR_PAIR(1) | ' ');
        assume_default_colors(COLOR_RED, COLOR_BLUE);

        attron(COLOR_PAIR(3));
        int i;

        for (i = (start_x + 2); i < (start_x + width_global + 1); i++) {
            move((start_y + height_global), i);
            addch(' ');
        }

        for (i = (start_y + 1); i < (start_y + height_global + 1); i++) {
            move(i, (start_x + width_global));
            addch(' ');
            move(i, (start_x + width_global + 1));
            addch(' ');
        }
        attroff(COLOR_PAIR(3));

        refresh();
    }
}

WINDOW *startWindow(int height, int width) {
    WINDOW *w;

    height_global = height;
    width_global = width;
    start_y = (LINES - height) / 2;
    start_x = (COLS - width) / 2;

    if (start_y < 1 || start_x < 1 || (start_y + MAX_HEIGHT + 2) > LINES || (start_x + MAX_WIDTH + 2) > COLS) {
        return NULL;
    }

    w = newwin(height, width, start_y, start_x);
    setcolor(w);
    box(w, ' ', ' ');

    wrefresh(w);
    return w;
}

void setupWindow() {
    wrefresh(w);
    noecho();
    keypad(w, TRUE);
    curs_set(0);
}

int second_window(int height, int width) {
    int selected = 0, i = 0, ch;
    MEVENT event;
    char list[6][512] = {"A. PGM1 rulez!", "B. M'agrada programar webs en Java.",
                         "C. SELECT * FROM torrades WHERE nom = \"Aaron\";",
                         "D. Jo hagues fet aquest programa amb NCurses!",
                         "E. sudo apt-get install life",
                         "F. Most of the BST operations (e.g., search, max, min, insert, delete.. etc) take O(h) time where h is the height of the BST. The cost of these operations may become O(n) for a skewed Binary tree. If we make sure that height of the tree remains O(Logn) after every insertion and deletion, then we can guarantee an upper bound of O(Logn) for all these operations. The height of a Red Black tree is always O(Logn) where n is the number of nodes in the tree."};

    w = startWindow(height, width);
    if (w == NULL) {
        if (start_y < 0 && start_x < 0) {
            w = startWindow(BASE_HEIGHT, BASE_WIDTH);
        } else if (start_y < 0) {
            w = startWindow(BASE_HEIGHT, 100);
        } else if (start_x < 0) {
            w = startWindow(18, BASE_WIDTH);
        }
        if (w == NULL) {
            endwin();
            return 1;
        }
    }

    mvwprintw(w, 2, 5, "Amb quina de les seguent frases et sents mes comode?");

    for (i = 0; i < 6; i++) {
        if (i == 3)
            wattron(w, A_STANDOUT);
        else
            wattroff(w, A_STANDOUT);
        mvwprintw(w, 4 + i, 8, "%s", list[i]);
    }
    i = 3;

    setupWindow();

    while ((ch = wgetch(w)) != 'q' && ch != 10) {
        mvwprintw(w, 3 + i + 1, 8, "%s", list[i]);

        switch (ch) {
            case KEY_UP:
                i--;
                i = (i < 0) ? 5 : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i > 5) ? 0 : i;
                break;
            case KEY_MOUSE:
                if (has_mouse() && getmouse(&event) == OK) {
                    if (event.bstate & BUTTON1_CLICKED) {
                        if (((event.y - start_y) > 3) && ((event.y - start_y) < 14)
                            && ((event.x - start_x) > 7) && ((event.x - start_x) < 100)) {
                            i = (event.y - start_y) - 4;
                            if (i > 5) {
                                i = 5;
                            }
                            refresh();
                        }
                    }
                }
                break;
            default:
                break;
        }
        wattron(w, A_STANDOUT);

        selected = i;
        mvwprintw(w, 3 + i + 1, 8, "%s", list[i]);
        wattroff(w, A_STANDOUT);
    }

    if (ch == 'q') {
        endwin();
        exit(0);
    }

    refresh();
    clear();

    return selected;
}

void first_window(int height, int width) {

    w = startWindow(height, width);
    if (w == NULL) {
        return;
    }

    wattroff(w, A_STANDOUT);
    mvwprintw(w, 0, 20, "*** Convocatoria al sopar semestral del GDI ***");
    mvwprintw(w, 2, 5, "Lloc: Tasca i Vins, Carrer Industria 118, Barcelona");
    mvwprintw(w, 3, 5, "Dia: Dijous 15 de novembre");
    mvwprintw(w, 4, 5, "Hora: 22:00");
    mvwprintw(w, 5, 5, "Dress code: Business informal (tingueu en compte que vindra el vice-dega!)");
    mvwprintw(w, 7, 5, "Assistiras al sopar? ");
    wattron(w, A_STANDOUT);
    mvwprintw(w, 9, 5, "%s", "Si");
    wattroff(w, A_STANDOUT);
    mvwprintw(w, 10, 5, "%s", "No");

    if (has_colors() && has_mouse()) {
        mvwprintw(w, 12, 5, "Utilitza les fletxes i/o mouse per seleccionar, enter per continuar.");
    } else if (has_colors()) {
        mvwprintw(w, 12, 5, "Utilitza les fletxes per seleccionar, enter per continuar.");
    } else {
        mvwprintw(w, 12, 5,
                  "Utilitza les fletxes per seleccionar, enter per continuar (Ah i ja de pas, un terminal amb colors :)).");
    }

    setupWindow();

    int selected = 0, ch = 0;
    MEVENT event;

    while (selected != 1) {
        selected = 1;
        while ((ch = wgetch(w)) != 'q' && ch != 10) {
            switch (ch) {
                case KEY_UP:
                    wattron(w, A_STANDOUT);
                    mvwprintw(w, 9, 5, "%s", "Si");
                    wattroff(w, A_STANDOUT);
                    mvwprintw(w, 10, 5, "%s", "No");
                    selected = 1;
                    break;
                case KEY_DOWN:
                    wattron(w, A_STANDOUT);
                    mvwprintw(w, 10, 5, "%s", "Si");
                    wattroff(w, A_STANDOUT);
                    mvwprintw(w, 9, 5, "%s", "No");
                    break;
                case KEY_MOUSE:
                    if (has_mouse() && getmouse(&event) == OK) {
                        if (event.bstate & BUTTON1_CLICKED) {

                            if (((event.y - start_y) > 8) && ((event.y - start_y) < 11)
                                && ((event.x - start_x) > 4) && ((event.x - start_x) < 8)) {

                                if (event.y - start_y > 9) {
                                    wattron(w, A_STANDOUT);
                                    mvwprintw(w, 10, 5, "%s", "Si");
                                    wattroff(w, A_STANDOUT);
                                    mvwprintw(w, 9, 5, "%s", "No");
                                } else {
                                    wattron(w, A_STANDOUT);
                                    mvwprintw(w, 9, 5, "%s", "Si");
                                    wattroff(w, A_STANDOUT);
                                    mvwprintw(w, 10, 5, "%s", "No");
                                }
                                refresh();
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        if (ch == 'q') {
            delwin(w);
            endwin();
            exit(0);
        }
    }

}

void third_window(int height, int width, int selected) {

    w = startWindow(height, width);
    if (w == NULL) {
        if (start_y < 0 && start_x < 0) {
            w = startWindow(BASE_HEIGHT, BASE_WIDTH);
        } else if (start_x < 0) {
            w = startWindow(12, BASE_WIDTH);
        }
        if (w == NULL) {
            endwin();
            return;
        }
    }

    switch (selected) {
        case 0:
            mvwprintw(w, 2, 5, "Yay");
            break;
        case 1:
            mvwprintw(w, 2, 5, "Veig que ets un home/dona amb cultura i vas venir al sopar del curs passat.");
            break;
        case 2:

            mvwprintw(w, 2, 5, "No ho dubtava pas, qualsevol altra torrada no mereix el nostre respecte.");
            break;
        case 3:
            mvwprintw(w, 2, 5,
                      "Valent! Honro la teva decisio, també pots intentar-ho amb Brainfuck (llenguatge esoteric).");
            break;
        case 4:
            mvwprintw(w, 2, 5, "Sorry, you don't sudoer permission to install life.");
            break;
        case 5:
            mvwprintw(w, 2, 5, "Pernia, ves a menjar sushi i deixa estar els AVL!");
            break;
        case 6:
            mvwprintw(w, 2, 5, "No s'ha pogut mostrar la finestra grafica per falta d'espai.");
            break;

        default:
            break;
    }

    if (selected != 6)
        mvwprintw(w, 4, 5,
                  "Per confirmar la teva assistencia, respon al correu que has rebut (reply all) amb el seguent missatge:\n");

    switch (selected) {
        case 0:
            mvwprintw(w, 7, 5, "\"Soc un PGM1 fan boy.\"");
            break;
        case 1:
            mvwprintw(w, 7, 5, "\"Soc un vetera programador web.\"");
            break;
        case 2:
            mvwprintw(w, 7, 5, "\"Donam una BBDD i conquistare el mon!\"");
            break;
        case 3:
            mvwprintw(w, 7, 5, "\"Thunderbird es per nenazas, jo prefereixo Pine.\"");
            break;
        case 4:
            mvwprintw(w, 7, 5, "\"echo \"No bash no party\".\"");
            break;
        case 5:
            mvwprintw(w, 7, 5, "\"Em dic Pernia i estic malalt del cap.\"");
            mvwprintw(w, 8, 5, "Si no ets en Pernia, pots enviar: \"Estic malalt del cap com en Pernia.\"");
            break;
        default:
            break;
    }

    if (selected != 6) mvwprintw(w, 10, 5, "Prem 'q' per sortir.");

    setupWindow();

    while (wgetch(w) != 'q') {}
}

int main() {

    char error[] = {"No s'ha pogut mostrar la finestra grafica per falta d'espai.\n"};
    setlocale(LC_ALL, "");

    initscr();
    mousemask(ALL_MOUSE_EVENTS, NULL);

    first_window(BASE_HEIGHT, BASE_WIDTH);
    if (w == NULL) {
        printf("%s", error);
        endwin();
        return 1;
    }

    delwin(w);

    int selected = second_window(16, 100);
    if (w == NULL) {
        printf("%s", error);
        endwin();
        return 1;
    }

    delwin(w);

    third_window(12, 110, selected);
    if (w == NULL) {
        printf("%s", error);
        endwin();
        return 1;
    }

    delwin(w);
    endwin();

    return 0;
}
