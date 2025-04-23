CC := gcc

.PHONY: all pthreads_range stdthreads_range openmp_range pthreads_shared_var stdthreads_shared_var openmp_shared_var winthreads_range winthreads_shared_var openmp_shared_var_nosync semaphore_shared_var

# Windows examples are not included here because they are not cross-platform
all: pthreads_range stdthreads_range openmp_range pthreads_shared_var stdthreads_shared_var openmp_shared_var semaphore_shared_var

pthreads_range: pthreads/pthreads_range.c
	$(CC) $< -o pthreads/$@ -lpthread

stdthreads_range: stdthreads/stdthreads_range.c
	$(CC) $< -o stdthreads/$@ -std=c11

openmp_range: openmp/openmp_range.c
	$(CC) $< -o openmp/$@ -fopenmp

winthreads_range: winthreads/winthreads_range.c
	$(CC) $< -o winthreads/$@

openmp_shared_var_nosync: openmp/openmp_shared_var_nosync.c
	$(CC) $< -o openmp/$@ -fopenmp

pthreads_shared_var: pthreads/pthreads_shared_var.c
	$(CC) $< -o pthreads/$@ -lpthread

stdthreads_shared_var: stdthreads/stdthreads_shared_var.c
	$(CC) $< -o stdthreads/$@ -std=c11

openmp_shared_var: openmp/openmp_shared_var.c
	$(CC) $< -o openmp/$@ -fopenmp

winthreads_shared_var: winthreads/winthreads_shared_var.c
	$(CC) $< -o winthreads/$@

semaphore_shared_var: semaphore/semaphore_shared_var.c
	$(CC) $< -o semaphore/$@
