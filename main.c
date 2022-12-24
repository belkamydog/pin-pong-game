#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

const int LINE = 20; // размеры поля по y
const int COL = 50; // размеры поля по x
const int SPEED_PL = 4; // скорость каретки
const int BALL_SPEED = 20; //скорость мяча

void start_display(char screen[LINE][COL]);
void show_display(char screen[LINE][COL]);
int move_roket(char screen[LINE][COL], int x,  char key);
void ball(char *pflag, char *psides, int *pmx ,int *pmy);

int main()
{
    char mass[LINE][COL];
    int xr = 9;         // координата каретки
    int mx = 2, my = 4; // хранят координаты мяча
    int ball_box = 0;   // накопительная переменная скорости мяча
    char key = ' ';
    char flag = 'l';
    char sides = 'r';

    while (key != 'q')
    {
    timeout(5);
    noecho();
    cbreak();
    stdscr = initscr();
    keypad(stdscr,true);
    start_display(mass);
    mass[LINE-2][xr] = '-'; mass[LINE-2][xr+1] = '-'; mass[LINE-2][xr+2] = '-'; mass[LINE-2][xr+3] = '-';
    if (ball_box == BALL_SPEED) {ball(&flag, &sides, &mx, &my); ball_box = 0;}
    ball_box++;
    mass[my][mx] = '*';
    show_display(mass);
    doupdate();
    key = wgetch(stdscr);
    move_roket(mass, xr, key);
    clear();
    xr = move_roket(mass, xr, key);
    }
    endwin();
    return 0;
}
void ball(char *pflag, char *psides, int *pmx , int *pmy)
{
    if ((*pflag) == 'h' && (*psides) == 'r')
    {if((*pmx)<COL-2 && (*pmy)>1){(*pmx)++; (*pmy)--;} else if((*pmy) == 1 && (*pmx) < COL-2) {(*pflag) = 'l'; (*psides) = 'r';} else {(*pflag) = 'h'; (*psides) = 'l';}}

    else if ((*pflag) == 'h' && (*psides) == 'l')
    {if((*pmx)>1 && (*pmy)>1){(*pmx)--; (*pmy)--;} else if((*pmy) == 1 && (*pmx) > 1) {(*pflag) = 'l'; (*psides) = 'l';} else {(*pflag) = 'h'; (*psides) = 'r';}}

    else if ((*pflag) == 'l' && (*psides) == 'r')
    {if((*pmx)<COL-2 && (*pmy)<LINE-2){(*pmx)++; (*pmy)++;} else if((*pmy) == LINE-2 && (*pmx) < COL-2) {(*pflag) = 'h'; (*psides) = 'r';} else {(*pflag) = 'l'; (*psides) = 'l';}}

    else if ((*pflag) == 'l' && (*psides) == 'l')
    {if((*pmx) > 1 && (*pmy)<LINE-2){(*pmx)--; (*pmy)++;} else if((*pmy) == LINE-2 && (*pmx) > 1) {(*pflag) = 'h'; (*psides) = 'l';} else {(*pflag) = 'l'; (*psides) = 'r';}}

}

int move_roket(char screen[LINE][COL], int x, char key)
{
    if (key == 4 && x > 2) {x -= SPEED_PL; screen[LINE-2][x] = '_';}
    else if (key == 5 && x < COL-5) {x += SPEED_PL; screen[LINE-2][x] = '_';}
    return x;
}

void show_display(char screen[LINE][COL])
{
           for (int i = 0; i <= LINE-1; i++)
        {
            for (int j = 0; j <= COL-1; j++)
                printw("%c", screen[i][j]);
            printw("\n");
        }
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

