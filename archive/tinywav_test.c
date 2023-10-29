#include "./tinywav/tinywav.h"
#include "./tinywav/tinywav.c"
#include <stdio.h>

TinyWav tw;
FILE *pf = "./Goran Bregović - Kalashnikov.wav";

tinywav_open_read(&tw, 
	"./kalasnikow.wav",
	TW_SPLIT);
  

tinywav_close_read(&tw);



