#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

const int LINE = 21; // размеры поля по y
const int COL = 50; // размеры поля по x
const int SPEED_PL = 1; // скорость каретки
const int BALL_SPEED = 10; //скорость мяча

void start_display(char screen[LINE][COL]);
void show_display(char screen[LINE][COL], int score, int time_m, int time_s, int score2);
int move_roket(char screen[LINE][COL], int x,  char key, int *pxr2);
void ball(char *pflag, char *psides, int *pmx ,int *pmy, int xr, int xr2);
void game_time(int *ptime_m, int *ptime_s);
void game_score(int *pscore, int mx, int my, int xr, int xr2, int *pscore2);


int main()
{
    char mass[LINE][COL];
    int xr = 9;         // координата каретки 1
    int xr2 = 9;
    int mx = 2, my = 4; // хранят координаты мяча
    int ball_box = 0;   // накопительная переменная скорости мяча
    char key;
    char flag = 'l';
    char sides = 'r';

    int score = 0;
    int score2 = 0;
    int time_m = 0;
    int time_s = 0;

    printf("Hellow dear User!\nIt's a Pin-Pong-Game\nInput 's' for start new game or input q for out\nUse key_left or key_right to move platform\n");
    printf("Input your choice and press enter: ");
    scanf("%c", &key);
    noecho();

    while (key != 'q')
    {
    timeout(10);
    stdscr = initscr();
    keypad(stdscr,true);

    start_display(mass);
    mass[LINE-2][xr] = '-'; mass[LINE-2][xr+1] = '-'; mass[LINE-2][xr+2] = '-'; mass[LINE-2][xr+3] = '-';
    mass[1][xr2] = '-'; mass[1][xr2+1] = '-'; mass[1][xr2+2] = '-'; mass[1][xr2+3] = '-';

    if (ball_box == BALL_SPEED) {ball(&flag, &sides, &mx, &my, xr, xr2); ball_box = 0;}
    ball_box++;
    mass[my][mx] = '*';
    game_time(&time_m, &time_s);

    game_score(&score, mx, my, xr, xr2, &score2);

    show_display(mass, score, time_m, time_s, score2);

    key = wgetch(stdscr);
    move_roket(mass, xr, key, &xr2);

    xr = move_roket(mass, xr, key, &xr2);
    clear();
    }
    endwin();
    return 0;
}
void ball(char *pflag, char *psides, int *pmx , int *pmy, int xr, int xr2)
{
    if ((*pflag) == 'h' && (*psides) == 'r')
    {
    if((*pmx)<COL-2 && (*pmy)>1){(*pmx)++; (*pmy)--;}   // полет мяча верх в рамках поля не задевая стен /
    // уход мяча в створ ворот
    else if((*pmy) == 1 && (*pmx) < COL-2 && (*pmx) != xr2 && (*pmx) != xr2+1 && (*pmx) != xr2+2 && (*pmx) != xr2+3) {(*pmx) = 25; (*pmy) = 10;}
    // мяч попал в платформу 1 2
    else if((*pmy) == 1 && (*pmx) < COL-2 && ((*pmx) == xr2 || (*pmx) == xr2+1)) {(*pflag) = 'l'; (*psides) = 'l';}
    // мяч попал в платформу 3 4
    else if((*pmy) == 1 && (*pmx) < COL-2 && ((*pmx)== xr2+2 || (*pmx)== xr2+3)) {(*pflag) = 'l'; (*psides) = 'r';}
    else {(*pflag) = 'h'; (*psides) = 'l';}
    }

    else if ((*pflag) == 'h' && (*psides) == 'l')
    {
    if((*pmx)>1 && (*pmy)>2){(*pmx)--; (*pmy)--;}  // полет мяча верх в рамках поля не задевая стен /
    // уход мяча в створ ворот
    else if((*pmy) == 0 && (*pmx) > COL-2 && (*pmx) != xr2 && (*pmx) != xr2+1 && (*pmx) != xr2+2 && (*pmx) != xr2+3) {(*pmx) = 25; (*pmy) = 10;}
    // мяч попал в платформу 1 2
    else if((*pmy) == 0 && (*pmx) < COL-2 && ((*pmx) == xr2 || (*pmx) == xr2+1)) {(*pflag) = 'l'; (*psides) = 'l';}
    // мяч попал в платформу 3 4
    else if((*pmy) == 0 && (*pmx) < (COL-2) && (*pmx)==(xr2+2) || (*pmx)==(xr2+3)) {(*pflag) = 'l'; (*psides) = 'r';}
    else {(*pflag) = 'h'; (*psides) = 'r';}
    }

    else if ((*pflag) == 'l' && (*psides) == 'r')
    // полет мяча вниз в рамках поля не задевая стен /
    {
    if((*pmx)<COL-2 && (*pmy)<LINE-2){(*pmx)++; (*pmy)++;}
    // уход мяча в створ ворот
     else if((*pmy) == LINE-2 && (*pmx) < COL-2 && (*pmx)!= xr && (*pmx)!= xr+1 && (*pmx)!= xr+2 && (*pmx)!= xr+3) {(*pmx) = 25; (*pmy = 10);}
    // мяч попал в платформу 1 2
     else if((*pmy) == LINE-2 && (*pmx) < COL-2 && (*pmx) == xr || (*pmx) == xr+1 && (*pmx)!= xr+2 && (*pmx)!= xr+3) {(*pflag) = 'h'; (*psides) = 'l';}
    // мяч попал в платформу 3 4
     else if((*pmy) == LINE-2 && (*pmx) < COL-2 && (*pmx) != xr && (*pmx) != xr+1 && (*pmx)== xr+2 || (*pmx)== xr+3) {(*pflag) = 'h'; (*psides) = 'r';}
     else {(*pflag) = 'l'; (*psides) = 'l';}
    }
    else if ((*pflag) == 'l' && (*psides) == 'l')
    // полет мяча вниз в рамках поля не задевая стен /
    {
    if((*pmx) > 1 && (*pmy) < LINE-2){(*pmx)--; (*pmy)++;}
    // уход мяча в створ ворот
     else if((*pmy) == LINE-2 && (*pmx) > 1 && (*pmx)!= xr && (*pmx)!= xr+1 && (*pmx)!= xr+2 && (*pmx)!= xr+3) {(*pmx) = 25; (*pmy = 10);}
    // мяч попал в платформу 1 2
     else if((*pmy) == LINE-2 && (*pmx) > 1 && (*pmx) == xr || (*pmx) == xr+1 && (*pmx)!= xr+2 && (*pmx)!= xr+3) {(*pflag) = 'h'; (*psides) = 'r';}
    // мяч попал в платформу 3 4
     else if((*pmy) == LINE-2 && (*pmx) > 1 && (*pmx) != xr && (*pmx) != xr+1 && (*pmx)== xr+2 || (*pmx)== xr+3) {(*pflag) = 'h'; (*psides) = 'l';}

     else if((*pmy) != LINE-2 && (*pmx) == 1) {(*pflag) = 'l'; (*psides) = 'r';}
     else {(*pflag) = 'h'; (*psides) = 'r';}
     }

}

int move_roket(char screen[LINE][COL], int x, char key, int *pxr2)
{
    if (key == 4 && x > 1) {x -= SPEED_PL; screen[LINE-2][x] = '_';}
    else if (key == 5 && x < COL-5) {x += SPEED_PL; screen[LINE-2][x] = '_';}
    else if (key == 'a' && *pxr2 > 1) {*pxr2 -= SPEED_PL; screen[1][*pxr2] = '_';}
    else if (key == 'd' && *pxr2 < COL-5) {*pxr2 += SPEED_PL; screen[1][*pxr2] = '_';}
    return x;
}

void show_display(char screen[LINE][COL], int score, int time_m, int time_s, int score2)
{
           for (int i = 0; i <= LINE-1; i++)
        {
            for (int j = 0; j <= COL-1; j++)
                printw("%c", screen[i][j]);
            printw("\n");
        }
    printw("\n");
    printw("total score: %d : %d     time: %d m %d s",score, score2, time_m, time_s);
    printw("\n");
    printw("press q for out game");
}

void start_display(char screen[LINE][COL])
{
 for (int i = 0; i <= LINE-1; i++)
        {
            for (int j = 0; j <= COL-1; j++)
                {
                    if (i == 0 || i == LINE-1) screen[i][j] = '#';
                    else if (j == 0 || j == COL-1) screen[i][j] = '#';
                    else screen[i][j] = ' ';
                }
        }

}

void game_time(int *ptime_m, int *ptime_s)
{
    int ms = clock();
    int total_sek = ms / 100000;
    (*ptime_m) = total_sek / 60;
    (*ptime_s) = total_sek % 60;
}

void game_score(int *pscore, int mx, int my, int xr, int xr2, int *pscore2)
{
    if ((mx != xr && mx != xr+1 && mx != xr+2 && mx != xr+3) && my == (LINE-2))
    (*pscore)++;
    else if ((mx != xr2 && mx != xr2+1 && mx != xr2+2 && mx != xr2+3) && my == 1) (*pscore2)++;
}
