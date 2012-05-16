target: main glx.o

main: main.c main.h glx.o callback.c
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -o main main.c `pkg-config --libs --cflags gtk+-2.0` glx.o -lGL -lGLU -lX11 -lpng

glx.o: glx.c glx.h
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -Wno-error=unused-function -c glx.c `pkg-config --cflags gtk+-2.0`

sphere.c: sphere.c.bz2
	bzip2 -dc sphere.c.bz2 > sphere.c

clean:
	rm -rf main *.o *~ sphere.c
