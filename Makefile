CC = gcc
#For older gcc, use -O3 or -O2 instead of -Ofast
CFLAGS = -lm -pthread -Ofast -march=native -funroll-loops -Wno-unused-result
BUILDDIR := build
SRCDIR := src

all: dir dynamic shuffle txttobin

dir :
	mkdir -p $(BUILDDIR)
dynamic : $(SRCDIR)/dynamic.c
	$(CC) $(SRCDIR)/dynamic.c -o $(BUILDDIR)/dynamic $(CFLAGS)
shuffle : $(SRCDIR)/shuffle.c
	$(CC) $(SRCDIR)/shuffle.c -o $(BUILDDIR)/shuffle $(CFLAGS)
txttobin : $(SRCDIR)/txttobin.c
	$(CC) $(SRCDIR)/txttobin.c -o $(BUILDDIR)/txttobin $(CFLAGS)

clean:
	rm -rf dynamic shuffle txttobin build
