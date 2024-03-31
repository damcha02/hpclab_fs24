CC ?= gcc

all: recur_seq recur_omp

recur_seq: recur_seq.o walltime.o
	 $(CC) -O3 $^ -o $@ -lm   
###Added -lm here for linking against math library

recur_seq.o: recur_seq.c walltime.h
	$(CC) -c -O3 $<

recur_omp: recur_omp.c walltime.o
	$(CC) -O3 -fopenmp $^ -o $@ -lm
###Added -lm here

recur_omp.o: recur_omp.c walltime.h
	$(CC) -c -O3 -fopenmp $<

walltime.o: walltime.c walltime.h
	$(CC) -c $<

clean:
	$(RM) *.o recur_seq recur_omp
