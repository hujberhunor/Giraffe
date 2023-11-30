/*
███▀▀██▀▀███            ██  
█▀   ██   ▀                
     ██      ███  ▀███ ▀███  
     ██      ██    ██   ██  
     ██      ██    ██   ██  
     ██      ██    ██   ██  
   ▄████▄    ▀████▀███▄████▄
*/

#include <ncurses.h>
#include "./inc/giraffe.h"

/* GLOBAL VARIABLES */
  WINDOW *song;
  WINDOW *hint;
  WINDOW *bar; 


/* READS THE DIR PARAMETER AND THEN LISTS THE FILES INSIDE OF
* THAT DIRECRORY TO THE SONG WINDOW*/
void printSongs(char* dir){
  int size;
  char** songArray = dir_read(dir , &size);
  if(songArray == NULL){return;}

  box(song, 0, 0);
  mvwprintw(song, 0, 1, "Songs");
  for(int i = 0; i < size; i++){
    mvwprintw(song, i+1, 2, "[ ]");
    mvwprintw(song, i+1, 6, songArray[i]);
  }

  dir_free(songArray, size);
}  


/* PRINTS THE HINT WINDOW WITH TEXT INSIDE OF IT. */
void printHint(int toDisplay){
  box(hint, 0, 0);
  mvwprintw(hint, 0, 1, "Hint");

  mvwprintw(hint, 1, 2, "Press e to EXIT");
  mvwprintw(hint, 2, 2, "Press space to PAUSE");
  mvwprintw(hint, 3, 2, "Press s to (re)START");
  mvwprintw(hint, 4, 2, "Press r to RESTART from 0");
  mvwprintw(hint, 5, 2, "Press j,k to move UP/DOWN");
  mvwprintw(hint, 6, 2, "Press l to SELECT");
  mvwprintw(hint, 6, 2, "Press c to CREATE OUT FILE");
  mvwprintw(hint, 8, 2, "This song played %d times", toDisplay);
}

char* songStat(ma_uint64 paused){
  if(paused) return "Paused";
  else if(isPlaying()) return "Playing";
}


/* PRINTS THE STATUS BARS WINDOWS */
void printBar(char* song, int len){

  box(bar, 0, 0);
  char* charStatus;
  if(songFinished()){
    charStatus = "Not playing";
  }
  else charStatus = "Playing";

  mvwprintw(bar, 0, 2, "Playing");
  mvwprintw(bar, 1, 2,"%s", song);
  mvwprintw(bar, 1, 82, "%s", charStatus);
  mvwprintw(bar, 2, 2, "%i / %i  ", songCurrSec(), len%1000);
}


/* TAKES USER INPUT AND THEN "RETUNRS" WITH A INDEX 
 * WITH THAT INDEX YOU CAN PLAY THE SELECTED SONG*/
void selectSong(WINDOW *song, int *selected, int size){
  int cursX = 5; int cursY = 3;
  int index = 0;
  char ch;
  int exit = 0;
  move(cursY, cursX); // Curson in place

  while((exit == 0)){
    ch = getch();
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
          *selected = index;
          wrefresh(bar);
          exit = 1;
          break;
      
      case 'c':
        createFileOut("played.txt");
        break;


      case 'e':
           exit = 1;
    }
    move(cursY,cursX);
    if(cursY < 3){cursY++; index += 1;}
    else if (cursY > size+2){cursY--; index -= 1;}
    wrefresh(song);
  }
}

/* iNITIALIZES NCURSES AND THE WINDOWS THAT IM USING */
void initCurses(){
  initscr();  
  noecho();
  timeout(0); // Needed cause getch() blocks the thread
  keypad(stdscr, TRUE);

  song = newwin(15, 60, 2, 2);
  hint = newwin(15, 30, 2, 63);
  bar = newwin(4, 91, 17, 2);

  refresh();
}

/*
int main(){
  initCurses(); 
  
   // Print the text inside the windows. 
  printSongs("./songs/");
  printHint();
  printBar();
  // Refreshing the window 
  wrefresh(song);
  wrefresh(hint);
  wrefresh(bar);

  int selectedSongIndex;
  selectSong(song, selectedSongIndex);

  endwin();
}

*/

