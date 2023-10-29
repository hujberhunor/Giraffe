 /*Lopva: https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
   Kiegészítve: https://stackoverflow.com/questions/10347689/how-can-i-check-whether-a-string-ends-with-csv-in-c*/ 
#include <stdio.h>
#include <dirent.h> // File kezelés
#include <string.h> // dirent.h dependenci
#include <portaudio.h>
#include <sndfile.h>
// #include "/usr/local/include/sndfile.h"

int listwav() {
    int i = 1;
     DIR *d;
    struct dirent *entry;
    d = opendir("."); // Megnyitom az éppenleges DIR-t.
    if (d) {
        while ((entry = readdir(d)) != NULL) {  // Ameddig van file + mp3 kiiratás. 
            if (strlen(entry->d_name) > 4 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".wav") == 0) {
              printf("\t%d %s\n",i, entry->d_name);
              i++; 
            }
        }
        closedir(d);
    }
    return (0);
}

void play(){ // play audio "ffplay -v 0 -nodisp -autoexit"
  printf("What to play? \n");
  listwav();
  // system("playerctl play");
}

void stop(){
  printf("Stopped\n");
  // system("playerctl stop");
}

int chose(){
  int chosen = 0;    
  
  printf("Choose what to do:\n 1.Play\n 2.Stop\n 3.Exit\n Chosen: "); scanf("%d", &chosen);
  while (chosen != 3){
    switch (chosen) {
      case 1: play(); break;
      case 2: stop(); break;
    }
    return 0;
  }
}

 /// -----
 int main(){
   // chose();
  FILE *file; // ide olvasom be a fájlt
  long int fsize, fmeret; 
   
  file = fopen("./Goran Bregović - Kalashnikov.wav", "rb");

  fseek(file, 0, SEEK_END); // seek to end of file
  // fseek(file, 0, SEEK_SET); // seek back to the begining. 
  fsize = ftell(file); // size in byte 
  printf("%d\n", fsize);
  
  rewind(file);
  fclose(file);



 }
