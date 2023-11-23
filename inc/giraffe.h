#ifndef fileMan_H  
#define fileMan_H

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <ncurses.h>
#include "miniaudio.h"
#include "debugmalloc.h"


/* GLOBAL VARIABLES */
// extern char* dir = "/home/i3hunor/Giraffe/songs/"
// ############### TUI.C ###############
extern  WINDOW *song;
extern  WINDOW *hint;
extern  WINDOW *bar; 


// ########### AUDIO.C ############
// Decoder 
extern  ma_decoder decoder;
extern  ma_result resultDecoder;
extern  ma_result result;
  // Length
extern  ma_uint64 length;
extern  ma_result resultFrameSec; 
  // Resource manager
extern  ma_result resultRm;
extern  ma_resource_manager_config config;
extern  ma_resource_manager resourceManager;
 // Audio engine
extern  ma_uint64 cursor;
extern  ma_uint64 resultCursor;
extern  ma_engine engine;
extern  ma_result resultSound;
extern  ma_sound sound;
extern  char* dir;


/* #### FROM FILEMAN #### 
▀███▀▀▀███ ██  ▀███                 
  ██    ▀█       ██                 
  ██   █ ▀███    ██   ▄▄█▀██ ▄██▀███
  ██▀▀██   ██    ██  ▄█▀   ████   ▀▀
  ██   █   ██    ██  ██▀▀▀▀▀▀▀█████▄
  ██       ██    ██  ██▄    ▄█▄   ██
▄████▄   ▄████▄▄████▄ ▀█████▀██████▀
*/

char** dir_read(char *dir_path, int *size);


void dir_free(char** fileList, int size);


char* get_artist(char* fileName);


char* concat(char *string1, char *string2);



/* ### FROM AUDIO ###
      ██                      ▀███   ██           
     ▄██▄                       ██                
    ▄█▀██▄   ▀███  ▀███    ▄█▀▀███ ▀███   ▄██▀██▄ 
   ▄█  ▀██     ██    ██  ▄██    ██   ██  ██▀   ▀██
   ████████    ██    ██  ███    ██   ██  ██     ██
  █▀      ██   ██    ██  ▀██    ██   ██  ██▄   ▄██
▄███▄   ▄████▄ ▀████▀███▄ ▀████▀███▄████▄ ▀█████▀ 
*/

/* INPUT: ARRAY WHERE THE SONGS ARE STORED, THE SIZE OF THIS ARRAY
 * THE FUNCTION PRINTS THE SONG TO THE DISPLAY THEN
 * THE USER CAN CHOOSE A NUMBER WICH REPRESENTS THE INDEX
 * OF THE SONG*/
int songSelect(char** array, int sizeArray);


/* RETURNS THE SELECTED SONG'S LENGTH IN SEC */
int lenInSec();


/* RETURNS THE ELLAPSED TIME SINCE THE START OF THE SONG */
int songCurrSec();


void restartSong();


/* DECODES THE .WAV FILE, SO I CAN READ INFORMATION ABOUT IT 
 * FOR EXAMPLE LENGTH IN SEC ETC.*/
int decodeSong(char* filePath);


/* INITIALIZE THE RESOURCE MANAGER AND THE SOUND Enginer */
int setupMA();


void progressBar();


void playSong(char* songFile);

int songFinished();

int isPlaying();

/* MiniAudio CLEANUP, BASICALLY FREES THE ALLOCATED MEMORY BY THE
 * MA ENGINE AND DECODER*/
void cleaupMA();


/*
███▀▀██▀▀███            ██  
█▀   ██   ▀                
     ██    ███  ▀███ ▀███  
     ██      ██    ██   ██  
     ██      ██    ██   ██  
     ██      ██    ██   ██  
   ▄████▄    ▀████▀███▄████▄*/

void printSongs(char* dir);


void printHint();


void printBar(char* song, int len);


void selectSong(WINDOW *song, int *selected);


void initCurses();

/* ##### */
#endif 
