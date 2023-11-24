#include "./inc/giraffe.h"


int main(){
  char* dir = "./songs/";
  int songArraySize;
  char** songArray = dir_read(dir, &songArraySize);
  int selectedSongIndex;
 
  /* Initalizes ncurses and the windows */
  initCurses();
  curs_set(2);
  // Print the text inside the windows. 
  printSongs(dir);
  printHint(0);
  printBar("Select a song", 0); 
  // Refreshing the window 
  wrefresh(song);
  wrefresh(hint);
  wrefresh(bar);


  /* USER SELECTS A SONG IN UI, THEN CONCAT THE DIR + THE SELECTED 
   * INDEXES SONG NAME */
  selectSong(song, &selectedSongIndex);
  char* songPath = concat(dir, songArray[selectedSongIndex]);
  printBar(songPath, lenInSec());


  /* initializes miniaudio, decodes the selected song and plays it */
  setupMA();
  decodeSong(songPath);
  ma_sound_init_from_file(&engine, songPath, MA_SOUND_FLAG_STREAM, NULL, NULL, &sound);
  ma_sound_start(&sound);


  int toDisplay;
  listenTimes("played.txt", songArray[selectedSongIndex], &toDisplay);
  /* The MAIN part */
  ma_uint64 currentTime;  // Stores the frame when paused
  int exit = 0;
  

  while (!(songFinished()) && !(exit)) {
    int ch = getch();

    int a = lenInSec();

    printBar(songPath, a); 
    wrefresh(bar);
    printHint(toDisplay);
    wrefresh(hint);
    
    switch (ch) {
      case 'e':   // EXIT
        ma_sound_stop(&sound);
        exit = 1;
        break;
      case 'r':   // RESTART
        restartSong();
        break;
      case 32:    // PAUSE
        ma_sound_get_cursor_in_pcm_frames(&sound, &currentTime);
        ma_sound_stop(&sound);
        break;
      case 's': // START AFTER PAUSE
        ma_data_source_seek_to_pcm_frame(&decoder, currentTime);
        ma_sound_start(&sound);
        break;
      case 'c':
        createFileOut("played.txt");
        break;
    }
  }

  // -----
  dir_free(songArray, songArraySize);
  free(songPath);
  void cleanupMAA();
}
