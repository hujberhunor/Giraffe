#ifndef fileMan_H  
#define fileMan_H

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>


/* */
char** dir_read(char *dir_path, int *size);


void dir_free(char** fileList, int size);


char* get_artist(char* fileName);


char* concat(char *string1, char *string2);


#endif 
