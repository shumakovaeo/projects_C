#include <stdio.h>

#define X 81 // not use??????????????????????????????
#define Y 26

int collision(int i, int j, int pl1, int pl2) {
    //for x walls
    if (i == 25 || i == 1) {
        return 1;
    }
    //for y walls 1pl
    else if (j == 1) {
    	return 2;
    }
    //for y walls 2pl
    else if (j == 80) {
        return 3;
    }
    //for pl1  pl2
    else if  (((i == pl1 - 1 || i == pl1 || i == pl1 + 1) && j == 2) || ((i  == pl2 - 1 || i  == pl2 || i == pl2 + 1) && j == 79)) {
        return 4;
    }    //for     else if  {	return 5;    } !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return 0;
}

int initfield(int yball, int xball, int pl1, int pl2, int sc1, int sc2) {
    int goal;
    printf("                                    %d  --  %d\n", sc1, sc2);
    for (int i = 0; i <= Y; i++) {
        for (int j =0; j <= X; j++) {
	    //field non playable
	    if ((i == 0 && j != 0 && j != 81) || (i == 26 && j != 0 && j != 81)) {
                printf("-");
            }
	    if (j == 0) {
	    	printf("|");
	    }
	    else if (j == 81) {
	    	printf("|\n");
	    }
	    //ball
            if (i == yball && j == xball) {
                printf("o");
	    }
	    //player1
	    else if ((i == pl1 + 1 || i == pl1 || i == pl1 - 1) && j == 1) {
		printf("|");
	    }
	    //player2
	    else if ((i == pl2 + 1 || i == pl2 || i == pl2 - 1) && j == 80) {
                printf("|");
            }
	    else if ((i != 0 && i != 26) && (j != 0 && j != 81)) {
	        printf(" ");
	    }
	     goal= collision(yball, xball, pl1, pl2);//?????????????????    
	}
    }
    return goal;
}

int main () {
    int pl1ps=15, pl2ps=15;
    int plbally = 14, plballx = 40, chx = 1, chy = 1;
    int score1 = 0, score2 = 0;
    printf("Lets game! print only A/Z and K/M - to move the rackets, Space Bar - to skip\n");
    while (score1 < 21 && score2 < 21) { // !not (score1 < 21 || score2 < 21) !!!!!!!!!!!!!!!!!!!!!!!
	char s;
	char n;
        switch (initfield(plbally, plballx, pl1ps, pl2ps, score1, score2)){
		//case 0: 			break; // not need !!!!!!!!!!!!!!!!!!!!!!!!!!!!
		case 1:
		        chy = chy * (-1);
		       break;
	    case 2:
		       score2 +=1;
		       plbally = 14; 
		       plballx = 40;
		       pl1ps= 15; 
		       pl2ps=15;
		       chx = 1;
		       break;
		case 3:
		       score1 +=1;
                plbally = 14;
                plballx = 40;
                pl1ps= 15;
                pl2ps=15;
			chx = (-1);
			break;
		case 4:
			chx = chx * (-1);
			break; 		//case 5: 			chx = chx * (-1);			break; // like case 4!!!!!!!!!!!!!!!!!!!
	}
        plbally += chy;
        plballx += chx;
	if (scanf("%c%c", &s, &n) == 2 && n == '\n' && (s == 'a' || s == 'A' || s == 'z' || s == 'A' || s == 'm' || s == 'M' || s == 'k' || s == 'K' || s == ' '))
	    {
            switch (s){
                case 'A':
                        if (pl1ps>2) pl1ps -=1;
                        break;
                case 'a':
                        if (pl1ps>2) pl1ps -=1;
                        break;
                case 'Z':
                        if (pl1ps<24) pl1ps +=1;
                        break;
                case 'z':
                        if (pl1ps<24) pl1ps +=1;
                        break;
                case 'K':
                        if (pl2ps>2) pl2ps -=1;
                        break;
                case 'k':
                        if (pl2ps>2) pl2ps -=1;
                        break;
                case 'M':
                        if (pl2ps<24) pl2ps +=1;
                        break;
                case 'm':
                        if (pl2ps<24) pl2ps +=1;
                        break;                        // if space bar pl1ps and pl2ps not change
        }
    }
	else
        {printf("Enter wrong!");
            break;
   }
}
if (score1 == 1) 
printf("First win!");
else 
if (score2 == 1) 
printf("Second win!");
return 0;
}