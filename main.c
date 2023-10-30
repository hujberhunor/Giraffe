#include "./inc/giraffe.h"

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

  setupMA();
  decodeSong(songFile);
  
  printf("\nPress e to exit ");
  while(getchar() != 'e'){ 
    playSong(songFile); 
  }

  /* CLEANUP */
  dir_free(songArray, songArraySize);
  free(songPath);
  void cleanupMAA();
}
