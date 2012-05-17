target: main glx.o png.o

main: main.c main.h glx.o callback.c png.o
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -o main main.c `pkg-config --libs --cflags gtk+-2.0` png.o glx.o -lGL -lGLU -lX11 -lpng

glx.o: glx.c glx.h
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -Wno-error=unused-function -c glx.c `pkg-config --cflags gtk+-2.0`

png.o: png.c png.h botten.png box.png box_45.png
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -Wno-error=unused-function -c png.c

sphere.c: sphere.c.bz2
	bzip2 -dc sphere.c.bz2 > sphere.c

clean:
	rm -rf main *.o *~ sphere.c \#*\#

