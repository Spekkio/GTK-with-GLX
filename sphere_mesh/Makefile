target: sphere.inc generate_sphere scene.png

generate_sphere: generate_sphere.c
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -Wno-error=unused-function -o generate_sphere generate_sphere.c

sphere.inc: generate_sphere
	./generate_sphere | sed -e "s/0,/0./g" | sed -e "s/1,/1./g" > sphere.inc 
scene.png: scene.pov sphere.inc
	povray +H600 +W800 scene.pov

clean:
	rm -rf *~ generate_sphere sphere.inc *.png \#*\#

