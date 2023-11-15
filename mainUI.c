#include "./inc/giraffe.h"


int main(){
  char* dir = "./songs/";
  int songArraySize;
  char** songArray = dir_read(dir, &songArraySize);
  int selectedSongIndex;
  
  initCurses();
  // Print the text inside the windows. 
  printSongs(dir);
  printHint();
  // Refreshing the window 
  wrefresh(song);
  wrefresh(hint);

  /* USER SELECTS A SONG IN UI, THEN CONCAT THE DIR + THE SELECTED 
   * INDEXES SONG NAME */
  selectSong(song, &selectedSongIndex);
  char* songPath = concat(dir, songArray[selectedSongIndex]);
  printBar(songPath, songCurrSec(), lenInSec());


  setupMA();
  decodeSong(songPath);
  ma_sound_init_from_file(&engine, songPath, MA_SOUND_FLAG_STREAM, NULL, NULL, &sound);
  ma_sound_start(&sound);

  ma_uint64 currentTime;
  int exit = 0;
 

  while (!(songFinished()) && !(exit)) {
    int ch = getch();
    int a = songFinished();

  printBar(songPath, songCurrSec(), lenInSec()); 
    wrefresh(bar);
    
    switch (ch) {
      case 'e':
        ma_sound_stop(&sound);
        exit = 1;
        break;
      case 'r':
        restartSong();
        break;
      case 32:
        ma_sound_get_cursor_in_pcm_frames(&sound, &currentTime);
        ma_sound_stop(&sound);
        break;
      case 's': 
        ma_data_source_seek_to_pcm_frame(&decoder, currentTime);
        ma_sound_start(&sound);
        break;
      default:
        wrefresh(bar);
    }
  }


  // -----
  dir_free(songArray, songArraySize);
  free(songPath);
  void cleanupMAA();
}
