#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

int main(){
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    int error;
    for(;;){
        error = getch();
        if (error != ERR) printw("%d\n", error);
        refresh();
    }
}
