#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>

int main() {
    char** fileList;
    int i = 0;
    int size = 0;
    char *dir_path = "./songs/";

    /* Open and read directory */
    DIR *d = opendir(dir_path);
    struct dirent *dir;
    if (d == NULL) {
        printf("Error in reading the directory\n");
        return 1; // Exit with an error code
    }

    /* Allocate memory for fileList */
    fileList = (char**)malloc(sizeof(char*) * 100); // Assuming a maximum of 100 files
    if (fileList == NULL) {
        perror("Memory allocation failed");
        return 1; // Exit with an error code
    }

    /* Files to the list */
    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            fileList[i] = (char*)malloc(strlen(dir->d_name) + 1); // Allocate memory for each string
            if (fileList[i] == NULL) {
                perror("Memory allocation failed");
                return 1; // Exit with an error code
            }
            strcpy(fileList[i], dir->d_name);
            size++;
            i++;
        }
    }

    closedir(d);

    // Print the list
    for (int j = 0; j < size; j++) {
        printf("File %d: %s\n", j + 1, fileList[j]);
    }

    // Free allocated memory
    for (int j = 0; j < size; j++) {
        free(fileList[j]);
    }
    free(fileList);

    return 0; // Exit successfully
}

