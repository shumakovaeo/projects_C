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
    printf("                                    %d  --  %d\n", sc1, sc2);
    for (int i = 0; i <= 26; i++) {
        for (int j = 0; j <= 81; j++) {
            // field non playable
            if ((i == 0 && j != 0 && j != 81) || (i == 26 && j != 0 && j != 81)) {
                printf("-");
            }
            if (j == 0) {
                printf("|");
            } else if (j == 81) {
                printf("|\n");
            }
            // ball
            if (i == yball && j == xball) {
                printf("o");
            }
            // player1
            else if ((i == pl1 + 1 || i == pl1 || i == pl1 - 1) && j == 1) {
                printf("|");
            }
            // player2
            else if ((i == pl2 + 1 || i == pl2 || i == pl2 - 1) && j == 80) {
                printf("|");
            } else if ((i != 0 && i != 26) && (j != 0 && j != 81)) {
                printf(" ");
            }
        }
    }
    return 0;
}

// main function
int main() {
    // stock paramets
    int pl1ps = 15, pl2ps = 15;
    int plbally = 14, plballx = 40, chx = 1, chy = 1;
    int score1 = 0, score2 = 0;
    // the game rules
    printf(
        "Lets game! print only A/Z and K/M - to move the rackets, Space Bar - "
        "to skip\n");
    // main game cicle
    while (score1 < 21 && score2 < 21) {
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
        char s = getchar();
        char n = getchar();
        if (n == '\n') {
            switch (s) {
                case 'A':
                    if (pl1ps > 2 && chx == -1) pl1ps -= 1;
                    break;
                case 'a':
                    if (pl1ps > 2 && chx == -1) pl1ps -= 1;
                    break;
                case 'Z':
                    if (pl1ps < 24 && chx == -1) pl1ps += 1;
                    break;
                case 'z':
                    if (pl1ps < 24 && chx == -1) pl1ps += 1;
                    break;
                case 'K':
                    if (pl2ps > 2 && chx == 1) pl2ps -= 1;
                    break;
                case 'k':
                    if (pl2ps > 2 && chx == 1) pl2ps -= 1;
                    break;
                case 'M':
                    if (pl2ps < 24 && chx == 1) pl2ps += 1;
                    break;
                case 'm':
                    if (pl2ps < 24 && chx == 1) pl2ps += 1;
                    break;
            }
        }
        while (n != '\n') {
            n = getchar();
        }
    }
    // end of main loop output winner
    if (score1 == 21)
        printf("First win!\n");
    else if (score2 == 21)
        printf("Second win!\n");
    return 0;
}
