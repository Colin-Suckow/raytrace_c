trace: trace.c image.c vector.c sphere.c scene.c
	gcc -Wall -o trace trace.c image.c vector.c sphere.c scene.c -lm -fopenmp

run: trace
	./trace
	feh out.ppm