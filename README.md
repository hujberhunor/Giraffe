# Giraffe_v2

[Figma board](https://www.figma.com/file/EsgDA7eSZUrgqkofuwwLih/Giraffe_board?type=whiteboard&node-id=0%3A1&t=zbLixc6FVzcbymoX-1)

TUI .wav audio player written in C with miniaudio.  

### COMPILE AND RUN
CURRENTLY REPLACE MAIN WITH TEST.c | gcc main.c audio.c fileMan.c -o main -lm && ./main


### TODO

TEST/DEV branch
1. Multithreading (main + dal futtatás)
2. Nonblocking char megoldás

## FŐ FELADATOK
- restart
- Pause
- Ezekhez devBranch (Multithreading/Nonblocking)
- make file?

AUDIO.c
- Debugmalloc avagy memLeak ellenőrzés + hibaüzenetek írása
- audio.h hibaszűrés
- **Pause funct eltárolni a current framet majd ahhoz ugrani**
- **restart function rendberázás (induljon el a dal restart után)**

FILEMAN.c
  - fileMan line28 fix lista érték javítás? !! NE LEGYEN STATIKUS!! Láncolt lista
  - .wav-ra szűrés !! 

## Functions in giraffe.h

### Functions from fileMan.c
- dir_read
- dir_free !!
- get_artist
- concat
 
### Functions from audio.c
- songSelect
- lenInSec
- songCurrSec
- restartSong
- decodeSing
- setupMA
- cleanupMA
- ??progressBar??  

## Sources that I used or inspired by
[wax](https://github.com/znschaffer/wax/tree/main)

[Miniaudio documentation](https://miniaud.io/docs/manual/index.html)

## Dependecies
- ncurses?
