trace: trace.c image.c vector.c
	gcc -o trace trace.c image.c vector.c -lm

run: trace
	./trace
	feh out.ppm