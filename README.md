# Giraffe

TUI .wav player written in C. 
Uses miniaudio, only runs on linux. 

[Figma board](https://www.figma.com/file/EsgDA7eSZUrgqkofuwwLih/Giraffe_board?type=whiteboard&node-id=0%3A1&t=zbLixc6FVzcbymoX-1)

### COMPILE AND RUN

gcc main.c audio.c fileMan.c -o main -lm && ./main


### TODO
- restart           [x]
- Pause             [x] JAVÍTÁSOKRA SZORUL
- make file         [ ]

AUDIO.c
- Debugmalloc avagy memLeak ellenőrzés + hibaüzenetek írása 
- audio.h hibaszűrés    

FILEMAN.c
  - fileMan line28 fix lista érték javítás? !! NE LEGYEN STATIKUS!! Láncolt lista
  - .wav-ra szűrés !! 

## Sources that I used or inspired by
[wax](https://github.com/znschaffer/wax/tree/main)

[Miniaudio documentation](https://miniaud.io/docs/manual/index.html)

## Dependecies
- ncurses
