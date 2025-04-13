CC := gcc

.PHONY: all pthreads_range stdthreads_range openmp_range clean

all: pthreads_range stdthreads_range openmp_range

pthreads_range: pthreads/pthreads_range.c
	$(CC) $< -o pthreads/$@ -lpthread

stdthreads_range: stdthreads/stdthreads_range.c
	$(CC) $< -o stdthreads/$@ -std=c11

openmp_range: openmp/openmp_range.c
	$(CC) $< -o openmp/$@ -fopenmp
