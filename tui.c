/*
███▀▀██▀▀███            ██  
█▀   ██   ▀                
     ██    ███  ▀███ ▀███  
     ██      ██    ██   ██  
     ██      ██    ██   ██  
     ██      ██    ██   ██  
   ▄████▄    ▀████▀███▄████▄
*/

#include <ncurses.h>
#include "./inc/giraffe.h"

int main(int argc, char **argv)
{
    initscr();

    // creating a window;
    // with height = 15 and width = 10
    // also with start x axis 10 and start y axis = 20

  int wsize = strlen("Random eloado - random szam");
    WINDOW *win = newwin(15, wsize, 0, 0);
    refresh();

    // making box border with default border styles
    box(win, 0, 0);
  mvwprintw(win, 0, 3, "Songs");

    // move and print in window

    // refreshing the window
    wrefresh(win);
    getch();
    endwin();
    return 0;
}
