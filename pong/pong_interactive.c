#include <ncurses.h>
#include <stdio.h>

// detection collision for the ball
int collision(int i, int j, int pl1, int pl2) {
    // for x walls
    if (i == 25 || i == 1) {
        return 1;
    }
    // for y walls 1pl
    else if (j == 1) {
        return 2;
    }
    // for y walls 2pl
    else if (j == 80) {
        return 3;
    }
    // for pl1  pl2
    else if (((i == pl1 - 1 || i == pl1 || i == pl1 + 1) && j == 2) ||
             ((i == pl2 - 1 || i == pl2 || i == pl2 + 1) && j == 79)) {
        return 4;
    }
    return 0;
}

// initialazing game field
int initfield(int yball, int xball, int pl1, int pl2, int sc1, int sc2) {
    for (int i = 0; i <= 26; i++) {
        for (int j = 0; j <= 81; j++) {
            // field non playable
            if ((i == 0 && j != 0 && j != 81 && j != 36 && j != 44 && j != 37 && j != 45) ||
                (i == 26 && j != 0 && j != 81)) {
                mvaddch(i, j, '-');
            }
            if (i == 0 && j == 36) {
                mvprintw(i, j, "%d-", sc1);
            }
            if (i == 0 && j == 44) {
                mvprintw(i, j, "%d-", sc2);
            }
            if (j == 0) {
                mvaddch(i, j, '|');
            } else if (j == 81) {
                mvaddch(i, j, '|');
            }
            // ball
            if (i == yball && j == xball) {
                mvaddch(i, j, 'o');
            }
            // player1
            else if ((i == pl1 + 1 || i == pl1 || i == pl1 - 1) && j == 1) {
                mvaddch(i, j, '|');
            }
            // player2
            else if ((i == pl2 + 1 || i == pl2 || i == pl2 - 1) && j == 80) {
                mvaddch(i, j, '|');
            } else if ((i != 0 && i != 26) && (j != 0 && j != 81)) {
                mvaddch(i, j, ' ');
            }
        }
    }
    refresh();
    napms(100);
    return 0;
}

// main function
int main() {
    // stock paramets
    int pl1ps = 15, pl2ps = 15;
    int plbally = 14, plballx = 40, chx = 1, chy = 1;
    int score1 = 0, score2 = 0;
    // main game cicle
    while (score1 < 21 && score2 < 21) {
        initscr();
        // game field
        initfield(plbally, plballx, pl1ps, pl2ps, score1, score2);
        // ball logic
        switch (collision(plbally, plballx, pl1ps, pl2ps)) {
            case 1:
                chy = chy * (-1);
                break;
            case 2:
                score2 += 1;
                plbally = 14;
                plballx = 40;
                pl1ps = 15;
                pl2ps = 15;
                chx = 1;
                break;
            case 3:
                score1 += 1;
                plbally = 14;
                plballx = 40;
                pl1ps = 15;
                pl2ps = 15;
                chx = (-1);
                break;
            case 4:
                chx = chx * (-1);
                break;
        }
        plbally += chy;
        plballx += chx;
        // input detection section
        timeout(100);
        char s = getch();
        if ((s == 'A' || s == 'a') && pl1ps > 2) {
            pl1ps -= 1;
        }
        if ((s == 'Z' || s == 'z') && pl1ps < 24) {
            pl1ps += 1;
        }
        if ((s == 'K' || s == 'k') && pl2ps > 2) {
            pl2ps -= 1;
        }
        if ((s == 'M' || s == 'm') && pl2ps < 24) {
            pl2ps += 1;
        }
    }
    endwin();
    // end of main loop output winner
    if (score1 == 21)
        printf("First win!\n");
    else if (score2 == 21)
        printf("Second win!\n");
    return 0;
}
