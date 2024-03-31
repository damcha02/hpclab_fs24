CC     ?= gcc
CFLAGS  = -O3 $(shell pkg-config --cflags libpng)
###-I$(CPATH)
LDFLAGS = -O3 $(shell pkg-config --libs libpng)
# (shell pkg-config --libs libpng)
### $-L$(LIBRARY_PATH) -lpng

# $(shell pkg-config --cflags libpng) for CFLAGS


all: mandel_seq

mandel_seq: mandel_seq.o pngwriter.o walltime.o
	$(CC) $^ $(LDFLAGS) -o $@

mandel_seq.o: mandel_seq.c consts.h pngwriter.h walltime.h
	$(CC) -c $(CFLAGS) $<

pngwriter.o: pngwriter.c pngwriter.h
	$(CC) -c $(CFLAGS) $<

walltime.o: walltime.c walltime.h
	$(CC) -c $(CFLAGS) $<

.PHONY: clean
clean:
	$(RM) *.o mandel_seq
