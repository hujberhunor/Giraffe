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


  while (getchar() != 'e') {
    printf("Currently playing: %s \n", songFile);
    playSong(songFile);
    while (true) {
       printf("\r%i/%i", songCurrSec(), lenInSec());
       fflush(stdout); 
    }
  }

/*
  while (getchar() != 'e') {
    printf("%d\n", songCurrSec());
    ma_sound_start(&sound);
  }
  /*
  int a = 0;
  while(a == 0){ 
    scanf("%d", &a);
    ma_sound_init_from_file(&engine, songFile , MA_SOUND_FLAG_STREAM, NULL , NULL, &sound);
    ma_sound_start(&sound);
    int b = songCurrSec();
    printf("songCurrSec() = %d // %d \n", b, lenInSec());
   
  }
  
 /* 
  printf("\nPress e to exit \n");
  while(getchar() != 'e'){ 
    playSong(songFile); 
    printf("songCurrSec() = %d | %d \n", i++, songCurrSec());
  }


  /* CLEANUP */
  dir_free(songArray, songArraySize);
  free(songPath);
  void cleanupMAA();
}
