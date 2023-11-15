/*                                 
▀███▀▀▀███ ██  ▀███                 
  ██    ▀█       ██                 
  ██   █ ▀███    ██   ▄▄█▀██ ▄██▀███
  ██▀▀██   ██    ██  ▄█▀   ████   ▀▀
  ██   █   ██    ██  ██▀▀▀▀▀▀▀█████▄
  ██       ██    ██  ██▄    ▄█▄   ██
▄████▄   ▄████▄▄████▄ ▀█████▀██████▀
*/

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include "./inc/giraffe.h"

/* Opens a directory and reads the files inside that dir, then
 * puts them into a list wich is the return value
 * 
 * When calling you have to add the path where you want to read 
 * and a variable where you will store the size of your fileList, 
 * it is necessary for the dir_free function. */
char** dir_read(char *dir_path, int *size){
  char** fileList;
  int i = 0;
  int size_in = 0;

  /* Open and read directory */
  DIR *d = opendir(dir_path);
  struct dirent *dir;
  if (d == NULL) printf("Error in reading of the file\n");

  /* Pre? allocating memory for the array */
  fileList = (char**) malloc(sizeof(char*) * 100); // HIBA!! 50 feletti számoknál mi van?
  if(fileList == NULL) printf("Memory allocation error\n");

  /* Files to the list */
  while ((dir = readdir(d)) != NULL){  
    if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
      fileList[i] = (char*) malloc(strlen(dir->d_name) + 1);
      strcpy(fileList[i], dir->d_name);
      size_in++;
      i++;
    }
  }

  /* Clean up and return the fileList and the size of fileList */
  closedir(d);
 
  *size = size_in;
  return fileList;
}


/* Free's the memory that is allocated by the dir_read function,
 * in pair with the dir_read*/
void dir_free(char** fileList, int size){
  for (int j = 0; j < size; j++) {
    free(fileList[j]);
  }
  free(fileList);
}




/* The input file is preferably the dir_read's list, this function can
 * return the song's artist. */
char* get_artist(char* fileName){
  int i = 0;
  int dashIndex = 0; // Index where the "-" symbol is stored 
  char* artist; 
  
  while(fileName[i] != '\0'){
    if (fileName[i] == '-'){
    dashIndex = i;
    }
    i++;
  }
  
  artist = (char*) malloc(sizeof(char) * (dashIndex));
  
  for(int i = 0; i < dashIndex-1; i++){
    artist[i] = fileName[i];
  }
  artist[dashIndex-1] = '\0';
  return artist;
}

/*https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c */
char* concat(char *string1, char *string2){
    char *result = malloc(strlen(string1) + strlen(string2) + 1); 
    strcpy(result, string1);
    strcat(result, string2);
    return result;
}

/* TEST 
int main(){
  int meret = 0;
  char** lista =  dir_read("./songs/", &meret);

  /*
  for(int i = 0; i < meret ;i++){
    printf("lista[%d] = %s\n",i, lista[i]);
  }
 

  char* a = get_artist(lista[1]);
  printf("Artist: %s\n", a);
  char* g = concat("fasz", lista[1]);
  printf("%s\n", g );

  dir_free(lista, meret);

}
*/

