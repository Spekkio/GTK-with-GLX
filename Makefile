target: main obj/glx.o obj/png.o

main: main.c main.h obj/glx.o callback.c obj/png.o
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -o main main.c `pkg-config --libs --cflags gtk+-2.0` obj/png.o obj/glx.o -lGL -lGLU -lX11 -lpng

obj/glx.o: glx.c glx.h
	mkdir -p obj
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -Wno-error=unused-function -c glx.c `pkg-config --cflags gtk+-2.0`
	mv glx.o obj/

obj/png.o: png.c png.h botten.png box.png box_45.png
	mkdir -p obj
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -Wno-error=unused-function -c png.c
	mv png.o obj/

sphere.c: sphere.c.bz2
	bzip2 -dc sphere.c.bz2 > sphere.c

clean:
	rm -rf main *.o obj *~ sphere.c \#*\#

