#include "./inc/giraffe.h"

char* dir = "./songs/";
//char* currPlaying ="Cseh Tamás - Budapest.wav";
char* currPlaying ="Kontroll Csoport - Eladom.wav";



/* write the file names into the txt from the read dir.*/
void fileNames(char* writeInto, char* readFrom){
  FILE* countOut;
  countOut = fopen(writeInto, "w");

  if(countOut == NULL){
    printf("This directory does not exist or something like that!\n");
    fclose(countOut);
  }
  
  int sizeArray; 
  char** fileList = dir_read(readFrom, &sizeArray);
  char line[100];
  int num;
  /* SONG NAMES INTO THE FILE */
  for(int i = 0; i < sizeArray; i++){
    fprintf(countOut, "%s", fileList[i]);
    fprintf(countOut, "@%d\n",0 );
  }
  dir_free(fileList ,sizeArray);
  fclose(countOut);
}


/* ---------------------------------------------------- */
/* RETURNS THE NUMBER A SONG HAS PLAYED  */
int timesPlayed(char* readFrom){
  FILE* text;
  text = fopen(readFrom, "r");
  if(text == NULL){printf("Error!\n"); return -1;}
 
  char buf[100];
  char *token;
  char split = '@';
  int count = 0; 
  fgets(buf, sizeof(buf), text);

  token = strtok(buf, &split);
  // Ki kell nullázni 
  while (token != NULL) {
      if (++count == 2) {
         break; // Stop after getting the second token
      }
      token = strtok(NULL, &split);
  }
  
  int num = atoi(token);

  fclose(text);
  return num;


}

int main(){
  //fileNames("./songCountOut.txt", "./songs/");
int a;
  for (int i = 0; i < 5; i++){
   a =  timesPlayed("./songCountOut.txt");
  printf("a = %d\n", a);
  }
  printf("------------------\n");
}
