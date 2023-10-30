# Giraffe_v2

[Figma board](https://www.figma.com/file/EsgDA7eSZUrgqkofuwwLih/Giraffe_board?type=whiteboard&node-id=0%3A1&t=zbLixc6FVzcbymoX-1)

### COMPILE
gcc audio.c fileMan.c -o random -lm

### TODO

AUDIO.c
- Debugmalloc avagy memLeak ellenőrzés + hibaüzenetek írása
- audio.h hibaszűrés
- song dir path változtatható terminal argumentummal

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
- ??progressBar??  (not in header)

## Sources that I used or inspired by
[wax](https://github.com/znschaffer/wax/tree/main)

[Miniaudio documentation](https://miniaud.io/docs/manual/index.html)
