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



int printSongs(WINDOW *song, char* dir){
  int size;
  char** songArray = dir_read(dir , &size);

  mvwprintw(song, 0, 1, "Songs");
  for(int i = 0; i < size; i++){
    mvwprintw(song, i+1, 2, "[ ]");
    mvwprintw(song, i+1, 6, songArray[i]);
  }
  return size;
}  

void printHint(WINDOW *hint){
  mvwprintw(hint, 0, 1, "Hint");

  mvwprintw(hint, 1, 2, "Press e to exit");
  mvwprintw(hint, 2, 2, "Press space to pause");
  mvwprintw(hint, 3, 2, "Press s to start");
  mvwprintw(hint, 4, 2, "Press r to restart");
  mvwprintw(hint, 6, 2, "This song played x times");
}

void printBar(WINDOW *bar){
  mvwprintw(bar, 0, 2, "Playing");

  mvwprintw(bar, 1, 2, "Song");
  mvwprintw(bar, 1, 82, "Status");
  mvwprintw(bar, 2, 2, "Full/Curr");
}

void initWindows(WINDOW **song, WINDOW **hint, WINDOW **bar){
 /* IDE JÖNNE AZ INICIALIZÁLÁS ÁS A WINDOW DEKLARÁLÁS */ 
}

int main(){
  initscr();  
  noecho();
  keypad(stdscr, TRUE);

  WINDOW *song = newwin(15, 60, 2, 2);
  WINDOW *hint = newwin(15, 30, 2, 63);
  WINDOW *bar = newwin(4, 91, 17, 2);
  int arraySize;

  refresh();

  box(song, 0, 0);
  box(hint, 0, 0);
  box(bar, 0, 0);
  
   /* Print the text inside the windows. */
  arraySize = printSongs(song, "./songs/");
  printHint(hint);
  printBar(bar);
 
  // refreshing the window
  wrefresh(song);
  wrefresh(hint);
  wrefresh(bar);

  int cursX = 5; int cursY = 3;
  int index = 0;
  char ch;
  move(cursY, cursX); // Curson in place

  while(ch = getch()){
    switch (ch) {
      case 'j':     // MOVE DOWN
          cursY++;
          index++;
          break;
      case 'k':     // MOVE UP
          cursY--;
          index--;
          break;
      case 'l':     // SELECT
          mvwprintw(song, index+1, 2, "[x]");
          break;
      case 'h':
          mvwprintw(song, index+1, 2, "[ ]");
          break;
    }
    move(cursY,cursX);
    wrefresh(song);
  } 
  printf("VÉGE\n");

  endwin();
}
