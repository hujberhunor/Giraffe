
#include "./inc/giraffe.h"
#include <curses.h>

int main() {
  char* dir = "./songs/";
  int songArraySize;
  char** songArray = dir_read(dir, &songArraySize);
  int selected = songSelect(songArray, songArraySize);
  char* songPath = concat(dir, songArray[selected]);
  char* songFile = songPath;


  ma_uint64 currentTime;

  setupMA();
  decodeSong(songFile);

  ma_sound_init_from_file(&engine, songFile, MA_SOUND_FLAG_STREAM, NULL, NULL, &sound);

  // Start playing the song
  ma_sound_start(&sound);
  
  initscr();  // Initialize ncurses
  cbreak();   // Enable character-by-character input
  noecho();   // Don't display characters on the screen
  timeout(0); // Set getch() to non-blocking mode

  printw("#---#---#---#---#");
  printw("\nCurrently playing: %s\n", songFile);

  while (songFinished() != 1) {

    printw("\r%i/%i ", lenInSec(), songCurrSec());
    refresh();

    int ch = getch();
    
    if (ch == 'e') {
       ma_sound_stop(&sound);
       break;
    }
    else if (ch == 'r') { 
      restartSong();
    }
    else if (ch == ' ') {
      ma_sound_get_cursor_in_pcm_frames(&sound, &currentTime);
      ma_sound_stop(&sound);
    }
    else if (ch == 's') {
      ma_data_source_seek_to_pcm_frame(&decoder, currentTime);
      ma_sound_start(&sound);
    }

  }

  endwin();  // Clean up ncurses

  dir_free(songArray, songArraySize);
  free(songPath);
  void cleanupMAA();
}
