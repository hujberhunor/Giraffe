/*                                             
      ██                      ▀███   ██           
     ▄██▄                       ██                
    ▄█▀██▄   ▀███  ▀███    ▄█▀▀███ ▀███   ▄██▀██▄ 
   ▄█  ▀██     ██    ██  ▄██    ██   ██  ██▀   ▀██
   ████████    ██    ██  ███    ██   ██  ██     ██
  █▀      ██   ██    ██  ▀██    ██   ██  ██▄   ▄██
▄███▄   ▄████▄ ▀████▀███▄ ▀████▀███▄████▄ ▀█████▀ 
*/

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_MP3
#define MA_NO_FLAC
#include "./inc/miniaudio.h"
#include "./inc/fileMan.h"
#include <stdio.h>
#include <string.h>

/* GLOBAL VARIABLES (MiniAudio) (SORRY) */
  // Decoder 
  ma_decoder decoder;
  ma_result resultDecoder;
  ma_result result;
  // Length
  ma_uint64 length;
  ma_result resultFrameSec; 
  // Resource manager
  ma_result resultRm;
  ma_resource_manager_config config;
  ma_resource_manager resourceManager;
  // Audio engine
  ma_uint64 cursor;
  ma_uint64 resultCursor;
  ma_engine engine;
  ma_result resultSound;




/*NEEDS ITS OWN HEADER FILE */
int songSelect(char** array, int sizeArray){
  int selected = 0;
 
  /* Print the songs in the list */
  for(int i = 0; i < sizeArray; i++){
    printf("%d\t| %s\n",i+1, array[i]);
  }

  printf("Select a song! ");
  scanf("%d", &selected);

  return selected-1;
}
/* RETURNS THE VALUE OF THE READ FILE LENGTH IN SEC */
int lenInSec(){
  resultFrameSec = ma_data_source_get_length_in_pcm_frames(&decoder, &length);
  if (resultFrameSec != MA_SUCCESS) {return result;} 
  return (int) length/(float)decoder.outputSampleRate;
}

/* PROGRESS "BAR" */
void progesssBar(ma_result soundResult){
  int iter = 0;
  int lengthSec = lenInSec();
  
  while(soundResult == MA_SUCCESS){
    //printf("result = %d ", (int) cursor);
    printf("\r%i/%i", iter, lenInSec());
    fflush(stdout); 
    sleep(1);
    iter++;
  }
}

/* NEEDS ITS OWN HEADER */



int main(){
  /* from fileMan */
  char* dir = "./songs/";
  int songArraySize;                               // size of the songList 
  char** songArray = dir_read(dir, &songArraySize); // Reading dir MEMORY ALREDY ALLOCATED
  
  int selected = songSelect(songArray, songArraySize);
  
  char* songPath = concat(dir, songArray[selected]); 
  char *fp = songPath;                            // dir + song name concatenated 



  /* Decode */
  resultDecoder = ma_decoder_init_file(fp, NULL, &decoder); // Decode inicial
  if (resultDecoder != MA_SUCCESS) {printf("Decode error\n");return -1;} 

  /** ResourceManager  */
  config = ma_resource_manager_config_init();
  resultRm = ma_resource_manager_init(&config, &resourceManager);
  if (resultRm != MA_SUCCESS) {printf("ResourceManager error");return -1;}  

  /* Sound engine  */
  resultSound = ma_engine_init(NULL, &engine);
  if (resultSound != MA_SUCCESS) {printf("Engine error");return -1;} 

  ma_engine_play_sound(&engine, fp, NULL);

/* IMPLEMENTÁLNI KELL A PROGRESS BAR FUNCTIONBA!!  */
  if(resultSound == MA_SUCCESS) printf("Currently playing: %s \n", fp);
  progesssBar(resultSound);

  /* MiniAudio CLEANUP */
  ma_decoder_uninit(&decoder);
  ma_engine_uninit(&engine);
}

