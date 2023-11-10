/*            
▀████▄     ▄███▀         ██             
  ████    ████                          
  █ ██   ▄█ ██  ▄█▀██▄ ▀███ ▀████████▄  
  █  ██  █▀ ██ ██   ██   ██   ██    ██  
  █  ██▄█▀  ██  ▄█████   ██   ██    ██  
  █  ▀██▀   ██ ██   ██   ██   ██    ██  
▄███▄ ▀▀  ▄████▄████▀██▄████▄████  ████▄
*/


#include "./inc/giraffe.h"
#include <ncurses.h>


/* DONT FORGET
 * THE HEADER CONTAINS THE MINIAUDIO GLOBAL VARIABLES*/

int main(){
  char* dir = "./songs/";
  int songArraySize;                               
  char** songArray = dir_read(dir, &songArraySize);
  /* List the song names and asks for input
   * returns the selected index;*/
  int selected = songSelect(songArray, songArraySize);
  char* songPath = concat(dir, songArray[selected]); 
  char* songFile = songPath; 

  timeout(0); // Needed for the getch(), so it wont stop the thread flow?
  
  setupMA();
  decodeSong(songFile);


  ma_sound_init_from_file(&engine, songFile , MA_SOUND_FLAG_STREAM, NULL , NULL, &sound);


  ma_sound_start(&sound);
  
  printf("#---#---#---#---#");
  printf("\nCurrently playing: %s\n", songFile); 
 
  while (songFinished() != 1) {
    //  printf("\r%i/%i\t ", songCurrSec(), lenInSec());
    printf("\r%i/%i ", songCurrSec(), lenInSec());
    fflush(stdout);
   }


  /* CLEANUP */
  dir_free(songArray, songArraySize);
  free(songPath);
  void cleanupMAA();
}
