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

int main(){
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
  ma_result resultCursor;
  ma_engine engine;
  ma_result resultSound;
  
  /* from fileMan */
  char* dir = "./songs/";
  int songListSize;                               // size of the songList 
  char** songList = dir_read(dir, &songListSize); // Reading dir MEMORY ALREDY ALLOCATED
  char* songPath = concat(dir, songList[2]); 
  char *fp = songPath;                            // dir + song name concatenated 

  /* ############### */


  /* Decode */
  resultDecoder = ma_decoder_init_file(fp, NULL, &decoder); // Decode inicial
  if (resultDecoder != MA_SUCCESS) {printf("Decode error\n");return -1;} 

  /** ResourceManager  */
  config = ma_resource_manager_config_init();
  resultRm = ma_resource_manager_init(&config, &resourceManager);
  if (resultRm != MA_SUCCESS) {printf("ResourceManager error");return -1;}  

  /* Song duration in sec */
  resultFrameSec = ma_data_source_get_length_in_pcm_frames(&decoder, &length);
  if (resultFrameSec != MA_SUCCESS) {return result;} 
  int lenInSec = (int) length/(float)decoder.outputSampleRate;

  /* Sound engine  */
  resultSound = ma_engine_init(NULL, &engine);
  if (resultSound != MA_SUCCESS) {printf("Engine error");return -1;} 

  ma_engine_play_sound(&engine, fp, NULL);
  
  /* Progress bar */
  resultCursor = ma_data_source_get_cursor_in_pcm_frames(&decoder, &cursor);
  if (resultCursor != MA_SUCCESS) return result;
  
  if(resultSound == MA_SUCCESS) printf("Currently playing: %s \n", fp);

  int iter = 0;
  while(resultSound == MA_SUCCESS){
    //printf("result = %d ", (int) cursor);
    printf("\r%i/%i",  iter, lenInSec);
    fflush(stdout);
    sleep(1);
    iter++;
  }

  ma_decoder_uninit(&decoder);
  ma_engine_uninit(&engine);
}

