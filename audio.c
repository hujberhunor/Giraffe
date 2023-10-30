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
#include "./inc/giraffe.h"
#include "./inc/debugmalloc.h"
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
  ma_sound sound;

int songSelect(char** array, int sizeArray){
  int selected = 0;
 
  /* Print the songs in the list */
  for(int i = 0; i < sizeArray; i++){
    printf("%d\t| %s\n",i+1, array[i]);
  }

  /* Stores the selected songs index */
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


/* RETURNS THE TIME THAT HAS ELLAPSED SINCE THE START OF THE SONG */
int songCurrSec() {
  float pCursor;
  result = ma_sound_get_cursor_in_seconds(&sound, &pCursor);
  if (MA_SUCCESS != result) return 0;
  return (int) (pCursor);
}


void restartSong(){
  ma_sound_seek_to_pcm_frame(&sound, 0);
}


/* PROGRESS "BAR" */
void progesssBar(ma_result soundResult){
  int iter = 0;
  
  while(soundResult == MA_SUCCESS){
    //printf("result = %d ", (int) cursor);
    printf("\r%i/%i | %d", iter, lenInSec(), songCurrSec());
    fflush(stdout); 
    sleep(1);
    iter++;
  }
}


/* DECODES THE .WAV FILE, SO I CAN READ INFORMATION ABOUT IT 
 * FOR EXAMPLE LENGTH IN SEC ETC.*/
int decodeSong(char* filePath){
  /* Decode */
  resultDecoder = ma_decoder_init_file(filePath, NULL, &decoder); // Decode inicial
  if (resultDecoder != MA_SUCCESS) {
    printf("Decode error\n");
    return -1;
  }
  return 0;
}


/* INITIALIZE THE RESOURCE MANAGER AND THE SOUND Engine */
int setupMA(){
  /* ResourceManager  */
  config = ma_resource_manager_config_init();

  resultRm = ma_resource_manager_init(&config, &resourceManager);
  if (resultRm != MA_SUCCESS) {
    printf("ResourceManager error");
    return -1;
  }  

  /* Sound engine  */
  resultSound = ma_engine_init(NULL, &engine);
  if (resultSound != MA_SUCCESS) { 
    printf("Engine error"); 
    return -1;
  } 
  return 0;
}

void playSong(char* songFile){
  ma_sound_init_from_file(&engine, songFile , MA_SOUND_FLAG_STREAM, NULL , NULL, &sound);
  ma_sound_start(&sound);
}

/* MiniAudio CLEANUP, BASICALLY FREES THE ALLOCATED MEMORY BY THE
 * MA ENGINE AND DECODER*/
void cleaupMA(){
  ma_decoder_uninit(&decoder);
  ma_engine_uninit(&engine);
}


/*
int main(){
  char* dir = "./songs/";
  int songArraySize;                               // size of the songList 
  char** songArray = dir_read(dir, &songArraySize); // Reading dir MEMORY ALREDY ALLOCATED
  int selected = songSelect(songArray, songArraySize);
  
  char* songPath = concat(dir, songArray[selected]); 
  char* fp = songPath; 

  decodeSong(fp);
  setupMA();

   INIT + PLAYING THE SELECTED SONG 
  ma_sound_init_from_file(&engine, fp, MA_SOUND_FLAG_STREAM, NULL , NULL, &sound);
  ma_sound_start(&sound);
  //ma_engine_play_sound(&engine, fp, NULL);


  COMMENT : ITTENI SORRAL RENDESEN MŰKÖDIK A PROGRESS BAR 
  if(resultSound == MA_SUCCESS) printf("Currently playing: %s \n", fp);
  progesssBar(resultSound);

  void cleaupMA();
}
*/
